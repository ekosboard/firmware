idf_component_register(
    SRCS
    "i2c_manager.c"

    INCLUDE_DIRS
    "include"

    REQUIRES
    esp_driver_i2c
    freertos
)
