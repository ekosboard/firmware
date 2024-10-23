#ifndef API_SYSTEM_H
#define API_SYSTEM_H

#include "HTTP_server.h"
#include "esp_http_server.h"

#define BUF_SIZE        1024

#ifdef __cplusplus
extern "C" {
#endif

    ////////////////////////////////////////////////////////////////////////////////
    //  WIFI
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t wifi_credentials;
    void            register_wifi_credentials_uri(httpd_handle_t server);
    void            unregister_wifi_credentials_uri(httpd_handle_t server);
    esp_err_t       wifi_credentials_post_handler(httpd_req_t *req);

    extern const    httpd_uri_t wifi_connect;
    void            register_wifi_connect_uri(httpd_handle_t server);
    void            unregister_wifi_connect_uri(httpd_handle_t server);
    esp_err_t       wifi_connect_get_handler(httpd_req_t *req);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
