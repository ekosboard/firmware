#include "driver/i2c_master.h"
#include "driver/i2c_types.h"
#include "esp_err.h"

static i2c_master_bus_handle_t i2c_bus;

esp_err_t setup_i2c_bus(void)
{
    i2c_master_bus_config_t cfg = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0,
        .scl_io_num = GPIO_NUM_14,
        .sda_io_num = GPIO_NUM_21,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = false,
    };
    return i2c_new_master_bus(&cfg, &i2c_bus);
}

i2c_master_bus_handle_t get_i2c_bus(void)
{
    return i2c_bus;
}
