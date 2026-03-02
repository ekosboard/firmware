#include <stdio.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "esp_system.h"

static const char *TAG = "/api/system/ota/reboot";

esp_err_t ota_reboot_post_handler(httpd_req_t *req)
{
    ESP_LOGV(TAG, "POST");

    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, "{\"status\":\"rebooting\"}");

    vTaskDelay(pdMS_TO_TICKS(200));
    esp_restart();

    return ESP_OK;
}
