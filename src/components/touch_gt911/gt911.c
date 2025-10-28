#include "driver/gpio.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "gt911.h"
#include "esp_check.h"
#include "esp_log.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include <string.h>
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "hal/gpio_types.h"

#ifdef CONFIG_USE_GT911

static const char *TAG = "GT911";

static void         gt911_task(void *arg);
static void         gt911_timer_callback(void *arg);
static esp_err_t    gt911_hw_reset(gt911_t *dev);
static esp_err_t    gt911_read_cfg(gt911_t *dev);
static esp_err_t    gt911_i2c_write(gt911_t *dev, uint16_t reg, const uint8_t *data, size_t len);
static esp_err_t    gt911_i2c_read(gt911_t *dev, uint16_t reg, uint8_t *data, size_t len);
static esp_err_t    gt911_reset(gt911_t *gt911);

static gt911_t              gt911_ctx;
static esp_timer_handle_t   gt911_timer;
static TaskHandle_t         gt911_task_handle;

/* Registers */
#define GT911_REG_STATUS       0x814E
#define GT911_REG_PRODUCT_ID   0x8140
#define GT911_REG_CONFIG_VER   0x8047
#define GT911_REG_STATUS       0x814E
#define GT911_REG_POINTS_START 0x814F
#define GT911_REG_SLEEP        0x8040


gt911_t *gt911_get(void)
{
    return &gt911_ctx;
}


esp_err_t gt911_init(i2c_master_bus_handle_t bus)
{
    gt911_ctx.bus = bus;
    gt911_ctx.rst_pin = GT911_RESET_PIN;
    gt911_ctx.int_pin = GT911_INT_PIN;
    gt911_ctx.lock = (portMUX_TYPE)portMUX_INITIALIZER_UNLOCKED;

    i2c_device_config_t cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = GT911_I2C_ADDR,
        .scl_speed_hz = 100000,
    };
    ESP_RETURN_ON_ERROR(i2c_master_bus_add_device(bus, &cfg, &gt911_ctx.dev), TAG, "Failed to add GT911 to bus");

    xTaskCreate(gt911_task, "gt911_task", 4096, NULL, 5, &gt911_task_handle);

    const esp_timer_create_args_t timer_args = {
        .callback = gt911_timer_callback,
        .name = "gt911_timer",
    };
    ESP_RETURN_ON_ERROR(esp_timer_create(&timer_args, &gt911_timer), TAG, "Failed to create ISR timer");

    ESP_RETURN_ON_ERROR(gt911_hw_reset(&gt911_ctx), TAG, "Failed to reset GT911");
    return ESP_OK;
}


/**
 * @brief  Timer callback — appelé 10 ms après une interruption
 */
static void gt911_timer_callback(void *arg)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(gt911_task_handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


/**
 * @brief  ISR GPIO of GT911
 */
static void IRAM_ATTR gt911_isr_handler(void *arg)
{
    esp_timer_stop(gt911_timer);
    esp_timer_start_once(gt911_timer, 10 * 1000); // µs
}


/**
 * @brief  Task principale de lecture GT911
 */
static void gt911_task(void *arg)
{
    while (42)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        gt911_read_touch_data(&gt911_ctx);
    }
}

/**
 * @brief  Reset sequence (datasheet compliant)
 */
static esp_err_t gt911_hw_reset(gt911_t *gt911)
{
    esp_err_t ret = ESP_OK;

    /* Prepare pin for controller reset */
    if (gt911->rst_pin != GPIO_NUM_NC)
    {
        const gpio_config_t rst_gpio_config = {
            .mode = GPIO_MODE_OUTPUT,
            .pin_bit_mask = BIT64(gt911->rst_pin)
        };
        ret = gpio_config(&rst_gpio_config);
        ESP_GOTO_ON_ERROR(ret, err, TAG, "GPIO config failed");
    }

    /* Prepare pin for touch controller int */
    if (gt911->rst_pin != GPIO_NUM_NC && gt911->int_pin != GPIO_NUM_NC)
    {
        const gpio_config_t int_gpio_config = {
            .mode = GPIO_MODE_OUTPUT,
            .intr_type = GPIO_INTR_DISABLE,
            .pull_down_en = 0,
            .pull_up_en = 1,
            .pin_bit_mask = BIT64(gt911->int_pin),
        };
        ret = gpio_config(&int_gpio_config);
        ESP_GOTO_ON_ERROR(ret, err, TAG, "GPIO config failed");

        gpio_set_level(gt911->rst_pin, 0);
        gpio_set_level(gt911->int_pin, 0);
        vTaskDelay(pdMS_TO_TICKS(10));

        /* Select I2C addr */
        gpio_set_level(gt911->int_pin, 0);
        vTaskDelay(pdMS_TO_TICKS(1));

        gpio_set_level(gt911->rst_pin, 1);
        vTaskDelay(pdMS_TO_TICKS(60));
    } 
    else 
    {
        ESP_LOGW(TAG, "Unable to initialize the I2C address");
        ret = gt911_reset(&gt911_ctx);
        ESP_GOTO_ON_ERROR(ret, err, TAG, "GT911 reset failed");
    }

    /* Prepare pin for touch interrupt */
    if (gt911->int_pin != GPIO_NUM_NC)
    {
        const gpio_config_t int_gpio_config = {
            .mode = GPIO_MODE_INPUT,
            .intr_type = GPIO_INTR_POSEDGE,
            .pin_bit_mask = BIT64(gt911->int_pin)
        };
        ret = gpio_config(&int_gpio_config);
        ESP_GOTO_ON_ERROR(ret, err, TAG, "GPIO config failed");

        ESP_ERROR_CHECK(gpio_isr_handler_add(gt911->int_pin, gt911_isr_handler, NULL));
        ESP_LOGI(TAG, "GT911 interrupt configured on GPIO %d", gt911->int_pin);
    }

    /* Read status and config info */
    ret = gt911_read_cfg(gt911);
    ESP_GOTO_ON_ERROR(ret, err, TAG, "GT911 init failed");

err:
    if (ret != ESP_OK)
        ESP_LOGE(TAG, "Error (0x%x)! Touch controller GT911 initialization failed!", ret);

    return ret;
}


esp_err_t gt911_enter_sleep(gt911_t *gt911)
{
    uint8_t cmd = 0x05;

    gpio_isr_handler_remove(gt911->int_pin);
    const gpio_config_t int_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = BIT64(gt911->int_pin)
    };
    gpio_config(&int_gpio_config);

    gpio_set_level(gt911->int_pin, 0);
    vTaskDelay(pdMS_TO_TICKS(50));

    return gt911_i2c_write(gt911, GT911_REG_SLEEP, &cmd, sizeof(cmd));
}


esp_err_t gt911_exit_sleep(gt911_t *gt911)
{
    return gt911_hw_reset(gt911);
}


esp_err_t gt911_read_touch_data(gt911_t *dev)
{
    esp_err_t err;
    uint8_t status = 0;
    uint8_t clear = 0;

    // Lecture du registre de statut
    err = gt911_i2c_read(dev, GT911_REG_STATUS, &status, 1);

    // Pas de nouveau point
    if ((status & 0x80) == 0)
        return ESP_OK;

    uint8_t touch_cnt = status & 0x0F;
    if (touch_cnt == 0 || touch_cnt > GT911_MAX_POINTS)
    {
        // Clear le flag de statut
        gt911_i2c_write(dev, GT911_REG_STATUS, &clear, 1);
        return ESP_OK;
    }

    // Lire les points
    uint8_t buf[(8 * GT911_MAX_POINTS) + 1] = {0};
    err = gt911_i2c_read(dev, GT911_REG_POINTS_START, buf, touch_cnt * 8);
    if (err != ESP_OK)
        return err;

    // Effacer le flag "data ready"
    gt911_i2c_write(dev, GT911_REG_STATUS, &clear, 1);

    portENTER_CRITICAL(&dev->lock);
    dev->data.points = touch_cnt;

    for (uint8_t i = 0; i < touch_cnt; i++) {
        uint8_t *p = &buf[i * 8];
        dev->data.coords[i].x = ((uint16_t)p[2] << 8) | p[1];
        dev->data.coords[i].y = ((uint16_t)p[4] << 8) | p[3];
        dev->data.coords[i].strength = ((uint16_t)p[6] << 8) | p[5];
    }
    portEXIT_CRITICAL(&dev->lock);

    return ESP_OK;
}


static esp_err_t gt911_i2c_read(gt911_t *dev, uint16_t reg, uint8_t *data, size_t len)
{
    uint8_t addr_buf[2] = {
        (uint8_t)(reg >> 8),
        (uint8_t)(reg & 0xFF),
    };

    esp_err_t ret = i2c_master_transmit(dev->dev, addr_buf, 2, -1);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "I2C TX failed: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = i2c_master_receive(dev->dev, data, len, -1);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "I2C RX failed: %s", esp_err_to_name(ret));
        return ret;
    }

    return ESP_OK;
}


static esp_err_t gt911_i2c_write(gt911_t *dev, uint16_t reg, const uint8_t *data, size_t len)
{
    uint8_t buf[2 + len];
    buf[0] = (uint8_t)(reg >> 8);
    buf[1] = (uint8_t)(reg & 0xFF);
    memcpy(&buf[2], data, len);

    esp_err_t ret = i2c_master_transmit(dev->dev, buf, sizeof(buf), -1);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "I2C write failed: %s", esp_err_to_name(ret));
    }

    return ret;
}


static esp_err_t gt911_read_cfg(gt911_t *dev)
{
    uint8_t buf[4];

    // Lire le Product ID (3 octets)
    ESP_RETURN_ON_ERROR(
            gt911_i2c_read(dev, 0x8140, buf, 3),
            TAG, "GT911 read product ID failed!"
            );

    // Lire la version de configuration (1 octet)
    ESP_RETURN_ON_ERROR(
            gt911_i2c_read(dev, 0x8047, buf + 3, 1),
            TAG, "GT911 read config version failed!"
            );

    ESP_LOGI(TAG, "TouchPad_ID: 0x%02x 0x%02x 0x%02x", buf[0], buf[1], buf[2]);
    ESP_LOGI(TAG, "TouchPad_Config_Version: 0x%02x", buf[3]);

    return ESP_OK;
}


static esp_err_t gt911_reset(gt911_t *gt911)
{
    if (gt911->rst_pin != GPIO_NUM_NC)
    {
        ESP_RETURN_ON_ERROR(gpio_set_level(gt911->rst_pin, 0), TAG, "GPIO set level error!");
        vTaskDelay(pdMS_TO_TICKS(10));
        ESP_RETURN_ON_ERROR(gpio_set_level(gt911->rst_pin, 1), TAG, "GPIO set level error!");
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    return ESP_OK;
}

#endif
