#ifndef API_SYSTEM_H
#define API_SYSTEM_H

#include "HTTP_server.h"
#include "esp_http_server.h"

#define BUF_SIZE        1024

#ifdef __cplusplus
extern "C" {
#endif

    ////////////////////////////////////////////////////////////////////////////////
    //  CONFIG
    ////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////
    //
    //  /api/system/config/*
    //
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t config_dispatcher;
    void            register_config_dispatcher_uri(httpd_handle_t server);
    void            unregister_config_dispatcher_uri(httpd_handle_t server);
    esp_err_t       config_dispatcher_handler(httpd_req_t *req);

    esp_err_t       config_complete_post_handler(httpd_req_t *req);

    ////////////////////////////////////////////////////////////////////////////////
    //  WIFI
    ////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////
    //
    //  /api/system/wifi/*
    //
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t wifi_dispatcher;
    void            register_wifi_dispatcher_uri(httpd_handle_t server);
    void            unregister_wifi_dispatcher_uri(httpd_handle_t server);
    esp_err_t       wifi_dispatcher_handler(httpd_req_t *req);

    ////////////////////////////////////////////////////////////////////////////////
    //
    //  /api/system/wifi/credentials
    //
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t wifi_credentials;
    void            register_wifi_credentials_uri(httpd_handle_t server);
    void            unregister_wifi_credentials_uri(httpd_handle_t server);
    esp_err_t       wifi_credentials_post_handler(httpd_req_t *req);

    ////////////////////////////////////////////////////////////////////////////////
    //
    //  /api/system/wifi/credentials/delete
    //
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t wifi_credentials_delete;
    void            register_wifi_credentials_delete_uri(httpd_handle_t server);
    void            unregister_wifi_credentials_delete_uri(httpd_handle_t server);
    esp_err_t       wifi_credentials_delete_handler(httpd_req_t *req);

    ////////////////////////////////////////////////////////////////////////////////
    //
    //  /api/system/wifi/connect
    //
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t wifi_connect;
    void            register_wifi_connect_uri(httpd_handle_t server);
    void            unregister_wifi_connect_uri(httpd_handle_t server);
    esp_err_t       wifi_connect_put_handler(httpd_req_t *req);

    ////////////////////////////////////////////////////////////////////////////////
    //
    //  /api/system/wifi/scan
    //
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t wifi_scan;
    void            register_wifi_scan_uri(httpd_handle_t server);
    void            unregister_wifi_scan_uri(httpd_handle_t server);
    esp_err_t       wifi_scan_get_handler(httpd_req_t *req);

    ////////////////////////////////////////////////////////////////////////////////
    //
    //  /api/system/wifi/status
    //
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t wifi_status;
    void            register_wifi_status_uri(httpd_handle_t server);
    void            unregister_wifi_status_uri(httpd_handle_t server);
    esp_err_t       wifi_status_get_handler(httpd_req_t *req);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
