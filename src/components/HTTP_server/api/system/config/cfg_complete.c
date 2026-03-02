#include "API_system.h"
#include "freertos/idf_additions.h"

static const char *TAG = "api/system/config/complete";

esp_err_t config_complete_post_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Received request: POST /system/config/complete");

    TaskHandle_t setup_timeout_task_handle = xTaskGetHandle("setup_timeout");
    if (setup_timeout_task_handle == NULL)
    {
        return httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Task not running");
    }

    xTaskNotify(setup_timeout_task_handle, 0, eSetValueWithOverwrite);

    cJSON *resp_json = cJSON_CreateObject();
    if (!resp_json)
    {
        return httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to allocate JSON");
    }

    cJSON_AddStringToObject(resp_json, "status", "idle");
    cJSON_AddStringToObject(resp_json, "message", "Configuration phase completed.");

    char *resp_str = cJSON_PrintUnformatted(resp_json);
    cJSON_Delete(resp_json);
    if (!resp_str)
    {
        return httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to encode JSON");
    }

    httpd_resp_set_type(req, "application/json");
    esp_err_t ret = httpd_resp_sendstr(req, resp_str);

    free(resp_str);
    return ret;
}

