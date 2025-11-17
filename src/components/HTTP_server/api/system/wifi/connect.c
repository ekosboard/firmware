#include "API_system.h"
#include "HTTP_server.h"
#include "http_parser.h"

static const char *TAG = "/api/system/wifi/connect";

/* Handles an HTTP GET request to start the Wi-Fi connection process in Station mode (STA). */
/* @Return Values: */
/* - ESP_OK if the connection attempt is successful. */
/* - ESP_FAIL if the connection attempt fails. */
esp_err_t       wifi_connect_put_handler(httpd_req_t *req)
{
    ESP_LOGV(TAG, "PUT");

    esp_err_t err;
    err = wifi_start_sta();
    if (err != ESP_OK)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, NULL);
        return ESP_FAIL;
    }
    httpd_resp_send(req, NULL, 0);
    return ESP_OK;
}

const httpd_uri_t wifi_connect = {
    .uri        = "/api/system/wifi/connect",
    .method     = HTTP_PUT,
    .handler    = wifi_connect_put_handler,
    .user_ctx   = NULL
};

void            register_wifi_connect_uri(httpd_handle_t server)
{
    httpd_register_uri_handler(server, &wifi_connect);
}

void            unregister_wifi_connect_uri(httpd_handle_t server)
{
    httpd_unregister_uri_handler(server, wifi_connect.uri, HTTP_PUT);
}
