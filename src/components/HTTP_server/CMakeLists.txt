idf_component_register(
    SRCS 
    "HTTP_server.c"
    "api/system/wifi/credentials.c"
    "api/system/wifi/connect.c"

    INCLUDE_DIRS 
    "include"

    REQUIRES
    wifi
    filesystem_interface
    esp-tls 
    esp_http_server 
    esp_wifi
    json
)
