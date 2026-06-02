#include "API_ui.h"
#include "esp_err.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "http_parser.h"
#include <string.h>

static const char *TAG = "api/ui/screens*";

esp_err_t screens_dispatcher_handler(httpd_req_t *req)
{
    if (req->method == HTTP_GET)
    {
        if (strcmp(req->uri, "/api/ui/screens") == 0)
        {
            return get_screens_handler(req);
        }
        else if (strncmp(req->uri, "/api/ui/screens/layout", strlen("/api/ui/screens/layout")) == 0)
        {
            return get_screens_layout_handler(req);
        }
        else if (strcmp(req->uri, "/api/ui/screens/active") == 0)
        {
            return get_active_screen_handler(req);
        }
        else if (strcmp(req->uri, "/api/ui/screens/schedule") == 0)
        {
            return get_screen_schedule_handler(req);
        }
        else
        {
            httpd_resp_send_err(req, HTTPD_501_METHOD_NOT_IMPLEMENTED, NULL);
            return ESP_FAIL;
        }
    }
    else if (req->method == HTTP_POST)
    {
        if (strcmp(req->uri, "/api/ui/screens/active") == 0)
        {
            return post_active_screen_handler(req);
        }
        else if (strcmp(req->uri, "/api/ui/screens/refresh") == 0)
        {
            return post_refresh_screen_handler(req);
        }
        else if (strcmp(req->uri, "/api/ui/screens/create") == 0)
        {
            httpd_resp_send_err(req, HTTPD_501_METHOD_NOT_IMPLEMENTED, NULL);
            return ESP_FAIL;
        }
        else if (strcmp(req->uri, "/api/ui/screens/schedule") == 0)
        {
            return post_screen_schedule_handler(req);
        }
        else
        {
            httpd_resp_send_err(req, HTTPD_501_METHOD_NOT_IMPLEMENTED, NULL);
            return ESP_FAIL;
        }
    }
    else if (req->method == HTTP_DELETE)
    {
        if (strcmp(req->uri, "/api/ui/screens/delete") == 0)
        {
            httpd_resp_send_err(req, HTTPD_501_METHOD_NOT_IMPLEMENTED, NULL);
            return ESP_FAIL;
        }
        else
        {
            httpd_resp_send_err(req, HTTPD_501_METHOD_NOT_IMPLEMENTED, NULL);
            return ESP_FAIL;
        }
    }
    else
    {
        // Si aucune route ne correspond
        httpd_resp_send_err(req, HTTPD_501_METHOD_NOT_IMPLEMENTED, NULL);
        return ESP_FAIL;
    }
}

const httpd_uri_t screens_dispatcher = {
    .uri        = "/api/ui/screens*",
    .method     = HTTP_ANY,
    .handler    = screens_dispatcher_handler,
    .user_ctx   = NULL
};

void register_screens_dispatcher_uri(httpd_handle_t server)
{
    httpd_register_uri_handler(server, &screens_dispatcher);
}

void unregister_screens_dispatcher_uri(httpd_handle_t server)
{
    httpd_unregister_uri_handler(server, screens_dispatcher.uri, HTTP_ANY);
}

