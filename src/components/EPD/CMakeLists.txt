idf_component_register(
    SRCS 
    "EPD.c"
    "driver/epd_GDEY042T81.c"
    "driver/epd_GDEY075T7.c"

    INCLUDE_DIRS 
    "include"

    REQUIRES
    esp_driver_gpio
    esp_driver_spi
)
