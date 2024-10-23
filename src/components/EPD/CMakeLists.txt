idf_component_register(
    SRCS 
    "EPD.c"
    "draw/qrcode.c"
    "draw/btn_bottom_left.c"
    "draw/btn_bottom_right.c"
    "draw/screen/wifi_config.c"
    "draw/screen/wifi_success.c"
    "driver/epd_GDEY042T81.c"
    "init_lvgl.c"

    INCLUDE_DIRS 
    "include"

    REQUIRES
    esp_driver_gpio
    esp_driver_spi
    lvgl
)
