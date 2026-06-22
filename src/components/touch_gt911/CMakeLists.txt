idf_component_register(
    SRCS
    "gt911.c"

    INCLUDE_DIRS
    "include"

    REQUIRES
    esp_driver_gpio
    esp_timer
    i2c_manager
)
