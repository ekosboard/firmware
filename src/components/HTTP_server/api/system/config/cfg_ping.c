#include "API_system.h"
#include "esp_log.h"

static const char *TAG = "/api/system/config/ping";

esp_err_t ping_get_handler(httpd_req_t *req)
{
    ESP_LOGV(TAG, "Method: GET");
    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, "{\"status\":\"pong\"}");
    return ESP_OK;
}
