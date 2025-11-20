#include <stdio.h>
#include "HTTP_server.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include "ota_context.h"
#include "cJSON.h"

static const char *TAG = "/api/system/ota/start";

esp_err_t ota_start_post_handler(httpd_req_t *req)
{
    ESP_LOGV(TAG, "POST");

    char *content = NULL;
    if (read_http_request_content(req, &content) != ESP_OK)
    {
        return ESP_FAIL;
    }

    size_t total_size = 0;
    char session_id[33] = {0};

    if (content != NULL)
    {
        cJSON *json = cJSON_Parse(content);
        if (json != NULL)
        {
            cJSON *jsize = cJSON_GetObjectItem(json, "size");
            if (jsize && cJSON_IsNumber(jsize))
            {
                total_size = (size_t)jsize->valuedouble;
            }

            cJSON *jsession = cJSON_GetObjectItem(json, "session_id");
            if (jsession != NULL && cJSON_IsString(jsession))
            {
                strncpy(session_id, jsession->valuestring, sizeof(session_id)-1);
            }

            cJSON_Delete(json);
        }
        free(content);
    }

    esp_err_t err = ota_context_start(total_size, session_id[0] ? session_id : NULL);
    cJSON *root = cJSON_CreateObject();
    if (err == ESP_OK)
    {
        cJSON_AddStringToObject(root, "status", "ready");
        cJSON_AddStringToObject(root, "session", session_id[0] ? session_id : "auto");
        cJSON_AddNumberToObject(root, "offset", 0);
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
