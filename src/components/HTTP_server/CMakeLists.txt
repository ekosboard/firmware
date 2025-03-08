idf_component_register(
    SRCS 
    "HTTP_server.c"
    "api/system/wifi_dispatcher.c"
    "api/system/wifi/credentials.c"
    "api/system/wifi/connect.c"
    "api/system/wifi/scan.c"
    "api/ui/widgets.c"
    "api/ui/widgets/available.c"
    "api/ui/widgets/{name}.c"
    "api/ui/widgets/widgets_dispatcher.c"
    "queue/widget_update.c"
    "utils/json.c"
    "utils/read_http_request_content.c"

    INCLUDE_DIRS 
    "include"

    REQUIRES
    wifi
    filesystem_interface
    esp-tls 
    esp_http_server 
    esp_wifi
    json
    UI
)
