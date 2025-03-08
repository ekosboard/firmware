#include "HTTP_server.h"
#include "API_system.h"
#include "API_ui.h"
#include "esp_http_server.h"
#include "esp_log.h"

static const char *TAG = "HTTP Server";

// Handler pour gérer les requêtes preflight (CORS)
static esp_err_t cors_options_handler(httpd_req_t *req)
{
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Headers", "Content-Type, Authorization");
    httpd_resp_send(req, NULL, 0);
    return ESP_OK;
}

static const httpd_uri_t options_uri = {
    .uri       = "*",
    .method    = HTTP_OPTIONS,
    .handler   = cors_options_handler,
    .user_ctx  = NULL
};

static httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.uri_match_fn = httpd_uri_match_wildcard;
    config.lru_purge_enable = true;

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK)
    {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &options_uri);
        register_wifi_dispatcher_uri(server);
        register_widgets(server);
        register_widgets_dispatcher_uri(server);
        return server;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}

static esp_err_t stop_webserver(httpd_handle_t server)
{
    // Stop the httpd server
    return httpd_stop(server);
}

static void disconnect_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server) 
    {
        ESP_LOGI(TAG, "Stopping webserver");
        if (stop_webserver(*server) == ESP_OK) 
        {
            *server = NULL;
        } 
        else 
        {
            ESP_LOGE(TAG, "Failed to stop http server");
        }
    }
}

static void connect_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server == NULL) 
    {
        ESP_LOGI(TAG, "Starting webserver");
        *server = start_webserver();
    }
}

void http_server(void *pvParameters)
{
    static httpd_handle_t server = NULL;
    esp_err_t err;

    err = init_widget_update_queue();
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "init_widget_update_queue failed!");
        vTaskDelete(NULL);
    }

    server = start_webserver();
    while (server)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    vTaskDelete(NULL);
}
