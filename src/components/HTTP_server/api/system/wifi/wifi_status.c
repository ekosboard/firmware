#include "API_system.h"
#include "HTTP_server.h"
#include "http_parser.h"

static const char *TAG = "api/system/wifi/status";

//TODO!
esp_err_t       wifi_status_get_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "GET");

    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, "{\"status\":\"ok\"}");
    return ESP_OK;
}

const httpd_uri_t wifi_status = {
    .uri        = "/api/system/wifi/status",
    .method     = HTTP_GET,
    .handler    = wifi_status_get_handler,
    .user_ctx   = NULL
};

void            register_wifi_status_uri(httpd_handle_t server)
{
    httpd_register_uri_handler(server, &wifi_status);
}

void            unregister_wifi_status_uri(httpd_handle_t server)
{
    httpd_unregister_uri_handler(server, wifi_status.uri, HTTP_GET);
}
