#ifndef SETUP_I2C_BUS_H
#define SETUP_I2C_BUS_H

#include "driver/i2c_types.h"
#include "esp_err.h"

esp_err_t               setup_i2c_bus(void);
i2c_master_bus_handle_t get_i2c_bus(void);

#endif
