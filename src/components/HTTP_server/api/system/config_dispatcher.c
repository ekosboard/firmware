#include "API_system.h"
#include "http_parser.h"

static const char *TAG = "api/system/config/*";

esp_err_t config_dispatcher_handler(httpd_req_t *req)
{
    if (req->method == HTTP_GET)
    {
        if (strcmp(req->uri, "/api/system/config/device-info") == 0)
        {
            return device_info_get_handler(req);
        }
        else if (strcmp(req->uri, "/api/system/config/ping") == 0)
        {
            return ping_get_handler(req);
        }
        else if (strcmp(req->uri, "/api/system/config/diagnostic") == 0)
        {
            return diagnostic_get_handler(req);
        }
        else if (strcmp(req->uri, "/api/system/config/timeout") == 0)
        {
            return config_timeout_get_handler(req);
        }
        else
        {
            httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Endpoint not found");
            return ESP_FAIL;
        }
    }
    else if (req->method == HTTP_POST)
    {
        if (strcmp(req->uri, "/api/system/config/complete") == 0)
        {
            return config_complete_post_handler(req);
        }
        else if (strcmp(req->uri, "/api/system/config/reboot") == 0)
        {
            return reboot_post_handler(req);
        }
        else if (strcmp(req->uri, "/api/system/config/timeout/extend") == 0)
        {
            return config_timeout_post_handler(req);
        }
        else
        {
            httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Endpoint not found");
            return ESP_FAIL;
        }
    }
    else if (req->method == HTTP_PATCH)
    {
        if (strcmp(req->uri, "/api/system/config/device-info") == 0)
        {
            return device_info_patch_handler(req);
        }
        else
        {
            httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Endpoint not found");
            return ESP_FAIL;
        }
    }
    else if (req->method == HTTP_PUT)
    {
        httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Endpoint not found");
        return ESP_FAIL;
    }
    else if (req->method == HTTP_DELETE)
    {
        httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Endpoint not found");
        return ESP_FAIL;
    }
    else
    {
        // Si aucune route ne correspond
        httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Endpoint not found");
        return ESP_FAIL;
    }
}

const httpd_uri_t config_dispatcher = {
    .uri = "/api/system/config/*",
    .method = HTTP_ANY,
    .handler = config_dispatcher_handler,
    .user_ctx = NULL
};

void register_config_dispatcher_uri(httpd_handle_t server)
{
    httpd_register_uri_handler(server, &config_dispatcher);
}

void unregister_config_dispatcher_uri(httpd_handle_t server)
{
    httpd_unregister_uri_handler(server, config_dispatcher.uri, HTTP_ANY);
}

