idf_component_register(
    SRCS 
    "wifi.c"
    "mDNS.c"
    "STA_mode.c"
    "AP_mode.c"
    "event.c"
    "SNTP.c"
    "scan.c"
    "wifi_switch_task.c"
    "queue/wifi_switch_queue.c"

    INCLUDE_DIRS 
    "include"

    REQUIRES
    esp_wifi
    nvs_flash
    mdns
    filesystem_interface
    UI
)
