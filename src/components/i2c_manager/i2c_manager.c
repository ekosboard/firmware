#include "i2c_manager.h"
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

static const char *TAG = "I2C_MANAGER";

static i2c_master_bus_handle_t s_bus    = NULL;
static SemaphoreHandle_t s_mutex  = NULL;


esp_err_t i2c_manager_init(void)
{
    // Création du mutex avant toute transaction
    s_mutex = xSemaphoreCreateMutex();
    if (s_mutex == NULL)
    {
        ESP_LOGE(TAG, "Failed to create mutex");
        return ESP_ERR_NO_MEM;
    }

    i2c_master_bus_config_t cfg = {
        .clk_source             = I2C_CLK_SRC_DEFAULT,
        .i2c_port               = I2C_NUM_0,
        .scl_io_num             = I2C_MANAGER_SCL_PIN,
        .sda_io_num             = I2C_MANAGER_SDA_PIN,
        .glitch_ignore_cnt      = 7,
        .flags.enable_internal_pullup = false,
    };

    esp_err_t err = i2c_new_master_bus(&cfg, &s_bus);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "i2c_new_master_bus failed: %s", esp_err_to_name(err));
        vSemaphoreDelete(s_mutex);
        s_mutex = NULL;
        return err;
    }

    ESP_LOGI(TAG, "I2C bus initialized (SCL=%d, SDA=%d)", I2C_MANAGER_SCL_PIN, I2C_MANAGER_SDA_PIN);
    return ESP_OK;
}


i2c_master_bus_handle_t i2c_manager_get_bus(void)
{
    if (s_bus == NULL)
        ESP_LOGE(TAG, "i2c_manager_get_bus called before i2c_manager_init");
    return s_bus;
}


esp_err_t i2c_manager_write_read(i2c_master_dev_handle_t dev,
        const uint8_t *tx, size_t tx_len,
        uint8_t *rx, size_t rx_len)
{
    if (s_mutex == NULL || dev == NULL)
        return ESP_ERR_INVALID_STATE;

    if (xSemaphoreTake(s_mutex, portMAX_DELAY) != pdTRUE)
        return ESP_ERR_TIMEOUT;

    esp_err_t ret = i2c_master_transmit(dev, tx, tx_len, -1);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "write_read TX failed: %s", esp_err_to_name(ret));
        xSemaphoreGive(s_mutex);
        return ret;
    }

    ret = i2c_master_receive(dev, rx, rx_len, -1);
    if (ret != ESP_OK)
        ESP_LOGE(TAG, "write_read RX failed: %s", esp_err_to_name(ret));

    xSemaphoreGive(s_mutex);
    return ret;
}


esp_err_t i2c_manager_write(i2c_master_dev_handle_t dev,
        const uint8_t *tx, size_t tx_len)
{
    if (s_mutex == NULL || dev == NULL)
        return ESP_ERR_INVALID_STATE;

    if (xSemaphoreTake(s_mutex, portMAX_DELAY) != pdTRUE)
        return ESP_ERR_TIMEOUT;

    esp_err_t ret = i2c_master_transmit(dev, tx, tx_len, -1);
    if (ret != ESP_OK)
        ESP_LOGE(TAG, "write failed: %s", esp_err_to_name(ret));

    xSemaphoreGive(s_mutex);
    return ret;
}
