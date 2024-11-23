idf_component_register(
    SRCS 
    "HTTP_server.c"
    "api/system/wifi/credentials.c"
    "api/system/wifi/connect.c"
    "api/ui/widgets.c"
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
