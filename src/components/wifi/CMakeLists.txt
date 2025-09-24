idf_component_register(
    SRCS 
    "wifi.c"
    "mDNS.c"
    "STA_mode.c"
    "AP_mode.c"
    "event.c"
    "SNTP.c"
    "scan.c"

    INCLUDE_DIRS 
    "include"

    REQUIRES
    esp_wifi
    nvs_flash
    mdns
    filesystem_interface
    UI
)
