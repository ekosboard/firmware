#include <stdio.h>
#include "esp_http_server.h"
#include "esp_log.h"
#include "cJSON.h"
#include "ota_context.h"

static const char *TAG = "/api/system/ota/commit";

esp_err_t ota_commit_post_handler(httpd_req_t *req)
{
    ESP_LOGV(TAG, "POST");

    cJSON *root = cJSON_CreateObject();
    esp_err_t err = ota_context_commit();
    if (err == ESP_OK)
    {
        cJSON_AddStringToObject(root, "status", "verifying");
    }
    else
    {
        cJSON_AddStringToObject(root, "status", "error");
        cJSON_AddStringToObject(root, "error", esp_err_to_name(err));
    }

    char *s = cJSON_PrintUnformatted(root);
    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, s);

    free(s);
    cJSON_Delete(root);

    return ESP_OK;
}
