#include "esp_err.h"
#include "esp_http_server.h"
#include "esp_log.h"

static const char *TAG = "/api/system/config/reboot";

esp_err_t reboot_post_handler(httpd_req_t *req)
{
    ESP_LOGW(TAG, "Reboot requested via API");

    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, "{\"status\":\"rebooting\"}");

    vTaskDelay(pdMS_TO_TICKS(200));
    esp_restart();

    return ESP_OK; // jamais atteint
}

