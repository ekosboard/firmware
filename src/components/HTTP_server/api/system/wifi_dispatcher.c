#include "API_system.h"
#include "http_parser.h"

static const char *TAG = "api/system/wifi/*";

esp_err_t wifi_dispatcher_handler(httpd_req_t *req)
{
    // Vérifier la méthode HTTP et router en interne
    if (req->method == HTTP_GET)
    {
        if (strcmp(req->uri, "/api/system/wifi/scan") == 0)
        {
            return wifi_scan_get_handler(req);
        }
        else 
        {
            httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Endpoint not found");
            return ESP_FAIL;
        }
    }
    else if (req->method == HTTP_POST)
    {
        if (strcmp(req->uri, "/api/system/wifi/credentials") == 0)
        {
            return wifi_credentials_post_handler(req);
        }
        else
        {
            httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Endpoint not found");
            return ESP_FAIL;
        }
    }
    else if (req->method == HTTP_PUT)
    {
        if (strcmp(req->uri, "/api/system/wifi/connect") == 0)
        {
            return wifi_connect_get_handler(req);
        }
        else
        {
            httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Endpoint not found");
            return ESP_FAIL;
        }
    }
    else
    {
        // Si aucune route ne correspond
        httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Endpoint not found");
        return ESP_FAIL;
    }
}

const httpd_uri_t wifi_dispatcher = {
    .uri        = "/api/system/wifi/*",
    .method     = HTTP_ANY,
    .handler    = wifi_dispatcher_handler,
    .user_ctx   = NULL
};

void register_wifi_dispatcher_uri(httpd_handle_t server)
{
    httpd_register_uri_handler(server, &wifi_dispatcher);
}

void unregister_wifi_dispatcher_uri(httpd_handle_t server)
{
    httpd_unregister_uri_handler(server, wifi_dispatcher.uri, HTTP_ANY);
}

