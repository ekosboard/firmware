#ifndef GT911_H
#define GT911_H

#include "driver/i2c_types.h"
#include "esp_err.h"
#include "portmacro.h"
#include "soc/gpio_num.h"


#define GT911_I2C_ADDR      0x5D
#define GT911_SCL_PIN       GPIO_NUM_14
#define GT911_SDA_PIN       GPIO_NUM_21
#define GT911_RESET_PIN     GPIO_NUM_45
#define GT911_INT_PIN       GPIO_NUM_48

#define GT911_MAX_POINTS    5


typedef struct gt911_s {
    i2c_master_bus_handle_t bus;
    i2c_master_dev_handle_t dev;
    gpio_num_t rst_pin;
    gpio_num_t int_pin;
    portMUX_TYPE lock;
    struct {
        uint8_t points;
        struct {
            uint16_t x;
            uint16_t y;
            uint16_t strength;
        } coords[GT911_MAX_POINTS];
    } data;
} gt911_t;

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Initialize the GT911 touch controller.
     *
     * This function configures the GT911 device, performs a reset sequence,
     * initializes the I2C communication, and prepares the internal context
     * for subsequent data reads.
     *
     * @param[in] bus Handle to the initialized I2C master bus.
     * @return
     *  - ESP_OK on success
     *  - ESP_FAIL if initialization fails
     *  - ESP_ERR_INVALID_ARG if the bus handle is invalid
     */
    esp_err_t   gt911_init(i2c_master_bus_handle_t bus);

    /**
     * @brief Read touch data from the GT911 device.
     *
     * This function reads the latest touch points from the GT911 controller
     * over I2C and updates the internal data structure (`gt911_t`).
     * Access to the shared data is protected by a spinlock to prevent
     * concurrent read/write collisions.
     *
     * @param[in,out] gt911 Pointer to the GT911 context.
     * @return
     *  - ESP_OK on success
     *  - ESP_FAIL if I2C read or data decoding fails
     */
    esp_err_t   gt911_read_touch_data(gt911_t *gt911);

    /**
     * @brief Put the GT911 device into sleep mode.
     *
     * Sends the GT911 sleep command over I2C to reduce power consumption.
     * The device will stop generating interrupts until it is explicitly
     * woken up using `gt911_exit_sleep()`.
     *
     * @param[in] gt911 Pointer to the GT911 context.
     * @return ESP_OK on success, or an I2C error code otherwise.
     */
    esp_err_t   gt911_enter_sleep(gt911_t *gt911);

    /**
     * @brief Wake up the GT911 device from sleep mode.
     *
     * Toggles the INT line as required by the GT911 wake-up sequence.
     * This function should be called after the ESP32 exits light sleep
     * or before reinitializing touch readings.
     *
     * @param[in] gt911 Pointer to the GT911 context.
     * @return ESP_OK on success.
     */
    esp_err_t   gt911_exit_sleep(gt911_t *gt911);

    /**
     * @brief Get a pointer to the internal GT911 context.
     *
     * Provides access to the internal static instance of the GT911 driver.
     * This allows other modules (e.g., LVGL input driver) to read the latest
     * touch data without maintaining their own copy.
     *
     * @return Pointer to the internal GT911 context (`gt911_t *`).
     */
    gt911_t     *gt911_get(void);

#ifdef __cplusplus
}
#endif

#endif
