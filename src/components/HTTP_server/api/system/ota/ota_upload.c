#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "ota_context.h"
#include "cJSON.h"

static const char *TAG = "/api/system/ota/upload";

#define CHUNK_BUF_SIZE 4096

esp_err_t ota_upload_post_handler(httpd_req_t *req)
{
    ESP_LOGV(TAG, "POST");

    // Check header X-OTA-Offset
    char offset_hdr[32] = {0};
    size_t offset = 0;
    if (httpd_req_get_hdr_value_str(req, "X-OTA-Offset", offset_hdr, sizeof(offset_hdr)) == ESP_OK)
    {
        offset = strtoul(offset_hdr, NULL, 10);
    }
    else
    {
        // fallback: allow sending sequentially (server will check current offset)
        offset = 0;
    }

    // content length may be unknown for chunked; use content_len
    int remaining = req->content_len;
    if (remaining <= 0)
        remaining = 0;

    uint8_t *buf = malloc(CHUNK_BUF_SIZE);
    if (!buf)
        return ESP_ERR_NO_MEM;

    size_t total_written = 0;
    esp_err_t err = ESP_OK;

    // If server doesn't provide content_len, read until 0 or until recv returns <=0
    while (remaining > 0)
    {
        int to_read = remaining > CHUNK_BUF_SIZE ? CHUNK_BUF_SIZE : remaining;
        int r = httpd_req_recv(req, (char*)buf, to_read);
        if (r <= 0)
        {
            if (r == HTTPD_SOCK_ERR_TIMEOUT) continue;
            ESP_LOGW(TAG, "recv returned %d", r);
            break;
        }

        size_t written = 0;
        err = ota_context_write(offset + total_written, buf, r, &written);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "ota_context_write failed: %s", esp_err_to_name(err));
            break;
        }
        total_written += written;
        remaining -= r;
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    free(buf);

    cJSON *root = cJSON_CreateObject();
    if (err == ESP_OK)
    {
        cJSON_AddStringToObject(root, "status", "ok");
        cJSON_AddNumberToObject(root, "written", total_written);
        size_t new_offset = 0;
        bool in_progress = false;
        ota_context_get_status(&new_offset, NULL, &in_progress);
        cJSON_AddNumberToObject(root, "next_offset", new_offset);
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
