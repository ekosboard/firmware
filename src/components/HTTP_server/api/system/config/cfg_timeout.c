#include "HTTP_server.h"
#include "cJSON.h"
#include "config_timeout_ctx.h"
#include "esp_timer.h"

static const char *TAG = "/api/system/config/timeout";


esp_err_t config_timeout_get_handler(httpd_req_t *req)
{
    ESP_LOGV(TAG, "Method: GET");

    config_timeout_ctx_t *ctx = config_timeout_ctx_get();
    if (!ctx)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Context unavailable");
        return ESP_FAIL;
    }

    uint32_t timeout_ms;
    uint64_t start_us;

    // Récupération protégée
    xSemaphoreTake(ctx->lock, portMAX_DELAY);
    timeout_ms = ctx->timeout_ms;
    start_us = ctx->timeout_start_us;
    xSemaphoreGive(ctx->lock);

    uint64_t now_us = esp_timer_get_time();
    uint64_t elapsed_us = now_us - start_us;

    uint32_t remaining_ms = 0;
    if (timeout_ms != portMAX_DELAY)
    {
        uint64_t timeout_us = (uint64_t)timeout_ms * 1000ULL;
        if (elapsed_us < timeout_us)
        {
            remaining_ms = (timeout_us - elapsed_us) / 1000ULL;
        }
        else
        {
            remaining_ms = 0;
        }
    }

    // JSON
    cJSON *root = cJSON_CreateObject();
    if (!root)
        return httpd_resp_send_500(req);

    cJSON_AddNumberToObject(root, "timeout_ms", timeout_ms);
    cJSON_AddNumberToObject(root, "started_at_us", start_us);
    cJSON_AddNumberToObject(root, "remaining_ms", remaining_ms);

    char *json_str = cJSON_PrintUnformatted(root);
    if (!json_str)
    {
        cJSON_Delete(root);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "JSON encoding failed");
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, json_str);

    free(json_str);
    cJSON_Delete(root);

    return ESP_OK;
}


esp_err_t config_timeout_post_handler(httpd_req_t *req)
{
    ESP_LOGV(TAG, "Method: POST");

    config_timeout_ctx_t *ctx = config_timeout_ctx_get();
    if (!ctx)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Context unavailable");
        return ESP_FAIL;
    }

    uint32_t timeout_ms;

    // Copie locale du timeout
    xSemaphoreTake(ctx->lock, portMAX_DELAY);
    timeout_ms = ctx->timeout_ms;
    ctx->timeout_start_us = esp_timer_get_time();
    xSemaphoreGive(ctx->lock);

    // Notify la task
    xTaskNotify(ctx->timeout_task_handle, timeout_ms, eSetValueWithOverwrite);

    // Réponse JSON
    cJSON *root = cJSON_CreateObject();
    if (!root)
        return httpd_resp_send_500(req);

    cJSON_AddStringToObject(root, "status", "extended");
    cJSON_AddNumberToObject(root, "timeout_ms", timeout_ms);

    char *json_str = cJSON_PrintUnformatted(root);
    if (!json_str)
    {
        cJSON_Delete(root);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "JSON encoding failed");
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, json_str);

    free(json_str);
    cJSON_Delete(root);

    return ESP_OK;
}
