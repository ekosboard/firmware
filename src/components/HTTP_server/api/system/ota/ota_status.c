#include <stdio.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "ota_context.h"
#include "cJSON.h"

static const char *TAG = "/api/system/ota/status";

esp_err_t ota_status_get_handler(httpd_req_t *req)
{
    ESP_LOGV(TAG, "GET");

    size_t offset = 0;
    size_t total = 0;
    bool in_progress = false;

    ota_context_get_status(&offset, &total, &in_progress);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "state", in_progress ? "writing" : "idle");
    cJSON_AddNumberToObject(root, "offset", offset);
    cJSON_AddNumberToObject(root, "total", total);

    int progress = 0;
    if (total > 0)
        progress = (int)((offset * 100) / total);

    cJSON_AddNumberToObject(root, "progress", progress);

    char *s = cJSON_PrintUnformatted(root);
    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, s);

    free(s);
    cJSON_Delete(root);

    return ESP_OK;
}
