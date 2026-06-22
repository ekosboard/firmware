#ifndef I2C_MANAGER_H
#define I2C_MANAGER_H

#include "driver/i2c_master.h"
#include "esp_err.h"
#include <stdint.h>
#include <stddef.h>

// Pins du bus I2C — à migrer vers Kconfig si évolution hardware
#define I2C_MANAGER_SCL_PIN     GPIO_NUM_14
#define I2C_MANAGER_SDA_PIN     GPIO_NUM_21

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Initialize the I2C master bus and its protection mutex.
     *        Must be called once at boot, before any i2c_manager_get_bus() call.
     *
     * @return ESP_OK on success.
     */
    esp_err_t i2c_manager_init(void);

    /**
     * @brief Return the bus handle, used by components to register their device
     *        via i2c_master_bus_add_device().
     *
     * @return Bus handle, or NULL if not initialized.
     */
    i2c_master_bus_handle_t i2c_manager_get_bus(void);

    /**
     * @brief Atomic write-then-read transaction (register address + read).
     *        The mutex is held for the entire sequence.
     *
     * @param dev     Device handle (obtained via i2c_master_bus_add_device)
     * @param tx      Write buffer (e.g. register address)
     * @param tx_len  Write buffer length
     * @param rx      Read buffer
     * @param rx_len  Read buffer length
     *
     * @return ESP_OK on success.
     */
    esp_err_t i2c_manager_write_read(i2c_master_dev_handle_t dev,
            const uint8_t *tx, size_t tx_len,
            uint8_t *rx, size_t rx_len);

    /**
     * @brief Atomic write-only transaction.
     *        The mutex is held for the entire operation.
     *
     * @param dev     Device handle
     * @param tx      Write buffer
     * @param tx_len  Write buffer length
     *
     * @return ESP_OK on success.
     */
    esp_err_t i2c_manager_write(i2c_master_dev_handle_t dev,
            const uint8_t *tx, size_t tx_len);

#ifdef __cplusplus
}
#endif

#endif /* I2C_MANAGER_H */
