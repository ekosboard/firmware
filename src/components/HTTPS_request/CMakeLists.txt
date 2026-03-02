idf_component_register(
    SRCS
    "HTTPS_request.c"

    INCLUDE_DIRS
    "include"

    REQUIRES
    filesystem_interface
    esp_http_client
    esp-tls
)
