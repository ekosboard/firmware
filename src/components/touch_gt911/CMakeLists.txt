idf_component_register(
    SRCS
    "gt911.c"

    INCLUDE_DIRS
    "include"

    REQUIRES
    driver
    esp_timer
    i2c_manager
)
