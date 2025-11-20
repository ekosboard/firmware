#include <stdio.h>
#include "esp_app_desc.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include "cJSON.h"
#include "esp_ota_ops.h"
#include "esp_partition.h"

static const char *TAG = "/api/system/ota/info";

esp_err_t ota_info_get_handler(httpd_req_t *req)
{
    ESP_LOGV("TAG", "GET");

    const esp_partition_t *running = esp_ota_get_running_partition();
    const esp_app_desc_t *app_desc = esp_app_get_description();

    if (app_desc == NULL)
    {
        memset(&app_desc, 0, sizeof(*app_desc));
        strncpy((char*)app_desc->version, "unknown", sizeof(app_desc->version) -1);
    }

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "device_id", "esp32-s3"); // customize if you have unique id
    cJSON_AddStringToObject(root, "current_version", app_desc->version);
    cJSON_AddStringToObject(root, "active_partition", running ? running->label : "unknown");

    const esp_partition_t *next = esp_ota_get_next_update_partition(NULL);
    cJSON_AddStringToObject(root, "next_partition", next ? next->label : "unknown");
    cJSON_AddNumberToObject(root, "max_payload", 4096);

    char *s = cJSON_PrintUnformatted(root);
    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, s);

    free(s);
    cJSON_Delete(root);

    return ESP_OK;
}
