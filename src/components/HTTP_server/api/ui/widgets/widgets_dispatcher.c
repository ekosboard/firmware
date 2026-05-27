#include "API_ui.h"
#include "esp_err.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "http_parser.h"
#include <string.h>

static const char *TAG = "api/ui/widgets/*";

esp_err_t widgets_dispatcher_handler(httpd_req_t *req)
{
    // Vérifier la méthode HTTP et router en interne
    if (req->method == HTTP_GET)
    {
        if (strcmp(req->uri, "/api/ui/widgets/available") == 0)
        {
            return get_available_widgets_handler(req);
        }
        else if (strcmp(req->uri, "/api/ui/widgets/layout") == 0)
        {
            return get_widgets_layout_handler(req);
        }
        else if (strcmp(req->uri, "/api/ui/widgets/shown") == 0)
        {
            return get_available_widgets_handler(req); //XXX
        }
        else 
        {
            return get_widget_template_handler(req);
        }
    }
    else if (req->method == HTTP_DELETE)
    {
        ESP_LOGI(TAG, "DELETE METHODE HANDLER");
        return ESP_OK;
    }
    else
    {
        // Si aucune route ne correspond
        httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Endpoint not found");
        return ESP_FAIL;
    }
}

const httpd_uri_t widgets_dispatcher = {
    .uri        = "/api/ui/widgets/*",
    .method     = HTTP_ANY,
    .handler    = widgets_dispatcher_handler,
    .user_ctx   = NULL
};

void register_widgets_dispatcher_uri(httpd_handle_t server)
{
    httpd_register_uri_handler(server, &widgets_dispatcher);
}

void unregister_widgets_dispatcher_uri(httpd_handle_t server)
{
    httpd_unregister_uri_handler(server, widgets_dispatcher.uri, HTTP_ANY);
}

