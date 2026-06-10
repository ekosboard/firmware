#include "bme280_provider.h"
#include "bme280.h"
#include "data_provider.h"
#include "i2c_manager.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include <string.h>

static const char *TAG = "PROVIDER_BME280";

// ─────────────────────────────────────────────────────────────────────────────
//  Buffer de données en PSRAM (BSS — zero-init, pas d'initialiseurs)
// ─────────────────────────────────────────────────────────────────────────────

static EXT_RAM_BSS_ATTR provider_data_t s_bme280_data;

// ─────────────────────────────────────────────────────────────────────────────
//  État interne du provider
// ─────────────────────────────────────────────────────────────────────────────

static struct bme280_dev        s_bme280_dev;
static struct bme280_settings   s_bme280_settings;
static i2c_master_dev_handle_t  s_i2c_dev = NULL;

// ─────────────────────────────────────────────────────────────────────────────
//  Callbacks Bosch → i2c_manager
// ─────────────────────────────────────────────────────────────────────────────

static BME280_INTF_RET_TYPE bme280_i2c_read(uint8_t reg_addr,
        uint8_t *reg_data,
        uint32_t len,
        void *intf_ptr)
{
    i2c_master_dev_handle_t dev = (i2c_master_dev_handle_t)intf_ptr;
    esp_err_t err = i2c_manager_write_read(dev, &reg_addr, 1, reg_data, len);
    return (err == ESP_OK) ? BME280_INTF_RET_SUCCESS : BME280_E_COMM_FAIL;
}

static BME280_INTF_RET_TYPE bme280_i2c_write(uint8_t reg_addr,
        const uint8_t *reg_data,
        uint32_t len,
        void *intf_ptr)
{
    i2c_master_dev_handle_t dev = (i2c_master_dev_handle_t)intf_ptr;

    uint8_t buf[1 + len];
    buf[0] = reg_addr;
    memcpy(&buf[1], reg_data, len);

    esp_err_t err = i2c_manager_write(dev, buf, sizeof(buf));
    return (err == ESP_OK) ? BME280_INTF_RET_SUCCESS : BME280_E_COMM_FAIL;
}

static void bme280_delay_us(uint32_t period, void *intf_ptr)
{
    (void)intf_ptr;
    esp_rom_delay_us(period);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Provider functions
// ─────────────────────────────────────────────────────────────────────────────

static esp_err_t bme280_provider_init(void)
{
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address  = BME280_I2C_ADDR_PRIM,
        .scl_speed_hz    = 100000,
    };
    esp_err_t err = i2c_master_bus_add_device(i2c_manager_get_bus(), &dev_cfg, &s_i2c_dev);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "i2c_master_bus_add_device failed: %s", esp_err_to_name(err));
        return err;
    }

    s_bme280_dev.intf     = BME280_I2C_INTF;
    s_bme280_dev.intf_ptr = (void *)s_i2c_dev;
    s_bme280_dev.read     = bme280_i2c_read;
    s_bme280_dev.write    = bme280_i2c_write;
    s_bme280_dev.delay_us = bme280_delay_us;

    int8_t rslt = bme280_init(&s_bme280_dev);
    if (rslt != BME280_OK)
    {
        ESP_LOGE(TAG, "bme280_init failed (rslt=%d)", rslt);
        return ESP_FAIL;
    }

    // Configuration forced mode — oversampling x1, pas de filtre
    s_bme280_settings.osr_t  = BME280_OVERSAMPLING_1X;
    s_bme280_settings.osr_p  = BME280_OVERSAMPLING_1X;
    s_bme280_settings.osr_h  = BME280_OVERSAMPLING_1X;
    s_bme280_settings.filter = BME280_FILTER_COEFF_OFF;

    uint8_t settings_sel = BME280_SEL_OSR_PRESS | BME280_SEL_OSR_TEMP |
        BME280_SEL_OSR_HUM   | BME280_SEL_FILTER;

    rslt = bme280_set_sensor_settings(settings_sel, &s_bme280_settings, &s_bme280_dev);
    if (rslt != BME280_OK)
    {
        ESP_LOGE(TAG, "bme280_set_sensor_settings failed (rslt=%d)", rslt);
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "BME280 init OK (chip_id=0x%02x)", s_bme280_dev.chip_id);
    return ESP_OK;
}

static esp_err_t bme280_provider_read(provider_data_t *out)
{
    if (s_i2c_dev == NULL)
    {
        out->status = PROVIDER_STATUS_ERROR_INIT;
        out->count  = 0;
        return ESP_FAIL;
    }

    int8_t rslt = bme280_set_sensor_mode(BME280_POWERMODE_FORCED, &s_bme280_dev);
    if (rslt != BME280_OK)
    {
        ESP_LOGE(TAG, "bme280_set_sensor_mode failed (rslt=%d)", rslt);
        out->status = PROVIDER_STATUS_ERROR_READ;
        out->count  = 0;
        return ESP_FAIL;
    }

    // Attente fin de mesure — délai calculé par l'API Bosch
    uint32_t delay_us = 0;
    bme280_cal_meas_delay(&delay_us, &s_bme280_settings);
    s_bme280_dev.delay_us(delay_us, s_bme280_dev.intf_ptr);

    struct bme280_data data;
    rslt = bme280_get_sensor_data(BME280_ALL, &data, &s_bme280_dev);
    if (rslt != BME280_OK)
    {
        ESP_LOGE(TAG, "bme280_get_sensor_data failed (rslt=%d)", rslt);
        out->status = PROVIDER_STATUS_ERROR_READ;
        out->count  = 0;
        return ESP_FAIL;
    }

    ESP_LOGD(TAG, "temp=%.2f°C | hum=%.2f%% | press=%.2fhPa",
            data.temperature, data.humidity, data.pressure / 100.0);

    out->count  = 3;
    out->status = PROVIDER_STATUS_OK;

    strncpy(out->values[0].key, "temperature", PROVIDER_NAME_MAX_LEN - 1);
    out->values[0].key[PROVIDER_NAME_MAX_LEN - 1] = '\0';
    out->values[0].type  = PROVIDER_VAL_FLOAT;
    out->values[0].val.f = (float)data.temperature;

    strncpy(out->values[1].key, "humidity", PROVIDER_NAME_MAX_LEN - 1);
    out->values[1].key[PROVIDER_NAME_MAX_LEN - 1] = '\0';
    out->values[1].type  = PROVIDER_VAL_FLOAT;
    out->values[1].val.f = (float)data.humidity;

    strncpy(out->values[2].key, "pressure", PROVIDER_NAME_MAX_LEN - 1);
    out->values[2].key[PROVIDER_NAME_MAX_LEN - 1] = '\0';
    out->values[2].type  = PROVIDER_VAL_FLOAT;
    // BME280_DOUBLE_ENABLE → pressure en Pa, conversion en hPa
    out->values[2].val.f = (float)(data.pressure / 100.0);

    return ESP_OK;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Struct de définition du provider — en DRAM interne (pas EXT_RAM_BSS_ATTR)
// ─────────────────────────────────────────────────────────────────────────────

static data_provider_t s_bme280_provider = {
    .name           = "bme280",
    .state          = PROVIDER_STATUS_UNAVAILABLE,
    .cache_ttl_ms   = BME280_CACHE_TTL_MS,
    .last_read_ms   = 0,
    .cached_data    = &s_bme280_data,
    .init           = bme280_provider_init,
    .read           = bme280_provider_read,
    .on_data        = NULL,
};

// ─────────────────────────────────────────────────────────────────────────────
//  Public entry point
// ─────────────────────────────────────────────────────────────────────────────

data_provider_t *bme280_get_provider(void)
{
    return &s_bme280_provider;
}
