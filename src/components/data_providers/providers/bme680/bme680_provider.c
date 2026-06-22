#include "bme680_provider.h"
#include "bme68x.h"
#include "bme68x_defs.h"
#include "data_provider.h"
#include "i2c_manager.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include <string.h>

static const char *TAG = "PROVIDER_BME680";

// ─────────────────────────────────────────────────────────────────────────────
//  Buffer de données en PSRAM (BSS — zero-init, pas d'initialiseurs)
// ─────────────────────────────────────────────────────────────────────────────

static EXT_RAM_BSS_ATTR provider_data_t s_bme680_data;

// ─────────────────────────────────────────────────────────────────────────────
//  État interne du provider
// ─────────────────────────────────────────────────────────────────────────────

static struct bme68x_dev        s_bme680_dev;
static struct bme68x_conf       s_bme680_conf;
static struct bme68x_heatr_conf s_bme680_heatr_conf;
static i2c_master_dev_handle_t  s_i2c_dev = NULL;

// ─────────────────────────────────────────────────────────────────────────────
//  Callbacks Bosch → i2c_manager
// ─────────────────────────────────────────────────────────────────────────────

static BME68X_INTF_RET_TYPE bme680_i2c_read(uint8_t reg_addr,
        uint8_t *reg_data,
        uint32_t len,
        void *intf_ptr)
{
    i2c_master_dev_handle_t dev = (i2c_master_dev_handle_t)intf_ptr;
    esp_err_t err = i2c_manager_write_read(dev, &reg_addr, 1, reg_data, len);
    return (err == ESP_OK) ? BME68X_INTF_RET_SUCCESS : BME68X_E_COM_FAIL;
}

static BME68X_INTF_RET_TYPE bme680_i2c_write(uint8_t reg_addr,
        const uint8_t *reg_data,
        uint32_t len,
        void *intf_ptr)
{
    i2c_master_dev_handle_t dev = (i2c_master_dev_handle_t)intf_ptr;

    uint8_t buf[1 + len];
    buf[0] = reg_addr;
    memcpy(&buf[1], reg_data, len);

    esp_err_t err = i2c_manager_write(dev, buf, sizeof(buf));
    return (err == ESP_OK) ? BME68X_INTF_RET_SUCCESS : BME68X_E_COM_FAIL;
}

static void bme680_delay_us(uint32_t period, void *intf_ptr)
{
    (void)intf_ptr;
    esp_rom_delay_us(period);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Provider functions
// ─────────────────────────────────────────────────────────────────────────────

static esp_err_t bme680_provider_init(void)
{
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address  = BME68X_I2C_ADDR_LOW, //HIGH for test module
        .scl_speed_hz    = 100000,
    };
    esp_err_t err = i2c_master_bus_add_device(i2c_manager_get_bus(), &dev_cfg, &s_i2c_dev);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "i2c_master_bus_add_device failed: %s", esp_err_to_name(err));
        return err;
    }

    s_bme680_dev.intf     = BME68X_I2C_INTF;
    s_bme680_dev.intf_ptr = (void *)s_i2c_dev;
    s_bme680_dev.read     = bme680_i2c_read;
    s_bme680_dev.write    = bme680_i2c_write;
    s_bme680_dev.delay_us = bme680_delay_us;
    s_bme680_dev.amb_temp = 25;  // température ambiante de référence pour le calcul heater

    int8_t rslt = bme68x_init(&s_bme680_dev);
    if (rslt != BME68X_OK)
    {
        ESP_LOGE(TAG, "bme68x_init failed (rslt=%d)", rslt);
        return ESP_FAIL;
    }

    // Configuration T/P/H — OSR x1, pas de filtre, pas de standby
    s_bme680_conf.os_hum  = BME68X_OS_1X;
    s_bme680_conf.os_temp = BME68X_OS_1X;
    s_bme680_conf.os_pres = BME68X_OS_1X;
    s_bme680_conf.filter  = BME68X_FILTER_OFF;
    s_bme680_conf.odr     = BME68X_ODR_NONE;

    rslt = bme68x_set_conf(&s_bme680_conf, &s_bme680_dev);
    if (rslt != BME68X_OK)
    {
        ESP_LOGE(TAG, "bme68x_set_conf failed (rslt=%d)", rslt);
        return ESP_FAIL;
    }

    // Configuration heater — valeurs depuis Kconfig
    s_bme680_heatr_conf.enable    = BME68X_ENABLE;
    s_bme680_heatr_conf.heatr_temp = CONFIG_PROVIDER_BME680_HEATER_TEMP;
    s_bme680_heatr_conf.heatr_dur  = CONFIG_PROVIDER_BME680_HEATER_DUR;

    rslt = bme68x_set_heatr_conf(BME68X_FORCED_MODE, &s_bme680_heatr_conf, &s_bme680_dev);
    if (rslt != BME68X_OK)
    {
        ESP_LOGE(TAG, "bme68x_set_heatr_conf failed (rslt=%d)", rslt);
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "BME680 init OK (chip_id=0x%02x, heater=%d°C/%dms)",
            s_bme680_dev.chip_id,
            CONFIG_PROVIDER_BME680_HEATER_TEMP,
            CONFIG_PROVIDER_BME680_HEATER_DUR);
    return ESP_OK;
}

static esp_err_t bme680_provider_read(provider_data_t *out)
{
    if (s_i2c_dev == NULL)
    {
        out->status = PROVIDER_STATUS_ERROR_INIT;
        out->count  = 0;
        return ESP_FAIL;
    }

    // Déclenche une mesure en forced mode
    int8_t rslt = bme68x_set_op_mode(BME68X_FORCED_MODE, &s_bme680_dev);
    if (rslt != BME68X_OK)
    {
        ESP_LOGE(TAG, "bme68x_set_op_mode failed (rslt=%d)", rslt);
        out->status = PROVIDER_STATUS_ERROR_READ;
        out->count  = 0;
        return ESP_FAIL;
    }

    // Attente fin de mesure — délai calculé par l'API Bosch (T/P/H + heater)
    uint32_t delay_us = bme68x_get_meas_dur(BME68X_FORCED_MODE, &s_bme680_conf, &s_bme680_dev)
        + ((uint32_t)s_bme680_heatr_conf.heatr_dur * 1000);
    s_bme680_dev.delay_us(delay_us, s_bme680_dev.intf_ptr);

    // Lecture des données
    struct bme68x_data data;
    uint8_t n_data = 0;
    rslt = bme68x_get_data(BME68X_FORCED_MODE, &data, &n_data, &s_bme680_dev);
    if (rslt != BME68X_OK || n_data == 0)
    {
        ESP_LOGE(TAG, "bme68x_get_data failed (rslt=%d, n=%d)", rslt, n_data);
        out->status = PROVIDER_STATUS_ERROR_READ;
        out->count  = 0;
        return ESP_FAIL;
    }

    // Vérification new data
    if (!(data.status & BME68X_NEW_DATA_MSK))
    {
        ESP_LOGW(TAG, "No new data available");
        out->status = PROVIDER_STATUS_STALE;
        out->count  = 0;
        return ESP_FAIL;
    }

    bool gas_valid = (data.status & BME68X_GASM_VALID_MSK) &&
        (data.status & BME68X_HEAT_STAB_MSK);

    ESP_LOGD(TAG, "temp=%.2f°C | hum=%.2f%% | press=%.2fhPa | gas=%.0f Ohm (valid=%d)",
            data.temperature, data.humidity, data.pressure / 100.0f,
            data.gas_resistance, gas_valid);

    out->status = PROVIDER_STATUS_OK;
    out->count  = 4;

    strncpy(out->values[0].key, "temperature", PROVIDER_NAME_MAX_LEN - 1);
    out->values[0].key[PROVIDER_NAME_MAX_LEN - 1] = '\0';
    out->values[0].type  = PROVIDER_VAL_FLOAT;
    out->values[0].val.f = data.temperature;

    strncpy(out->values[1].key, "humidity", PROVIDER_NAME_MAX_LEN - 1);
    out->values[1].key[PROVIDER_NAME_MAX_LEN - 1] = '\0';
    out->values[1].type  = PROVIDER_VAL_FLOAT;
    out->values[1].val.f = data.humidity;

    strncpy(out->values[2].key, "pressure", PROVIDER_NAME_MAX_LEN - 1);
    out->values[2].key[PROVIDER_NAME_MAX_LEN - 1] = '\0';
    out->values[2].type  = PROVIDER_VAL_FLOAT;
    // BME68X_USE_FPU → pressure en Pa, conversion en hPa
    out->values[2].val.f = data.pressure / 100.0f;

    strncpy(out->values[3].key, "gas_resistance", PROVIDER_NAME_MAX_LEN - 1);
    out->values[3].key[PROVIDER_NAME_MAX_LEN - 1] = '\0';
    out->values[3].type  = PROVIDER_VAL_FLOAT;
    // Si heater instable ou mesure invalide — on expose 0.0 comme sentinelle
    out->values[3].val.f = gas_valid ? data.gas_resistance : 0.0f;

    return ESP_OK;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Struct de définition du provider — en DRAM interne (pas EXT_RAM_BSS_ATTR)
// ─────────────────────────────────────────────────────────────────────────────

static data_provider_t s_bme680_provider = {
    .name           = "bme680",
    .state          = PROVIDER_STATUS_UNAVAILABLE,
    .cache_ttl_ms   = BME680_CACHE_TTL_MS,
    .last_read_ms   = 0,
    .cached_data    = &s_bme680_data,
    .init           = bme680_provider_init,
    .read           = bme680_provider_read,
    .on_data        = NULL,
};

// ─────────────────────────────────────────────────────────────────────────────
//  Public entry point
// ─────────────────────────────────────────────────────────────────────────────

data_provider_t *bme680_get_provider(void)
{
    return &s_bme680_provider;
}
