#include "API_ui.h"
#include "UI.h"
#include "screen_schedule.h"
#include "widget_schedule.h"
#include "cJSON.h"
#include "esp_log.h"
#include "esp_http_server.h"

static const char *TAG = "/api/ui/screens/schedule";

esp_err_t get_screen_schedule_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "GET");

    cJSON *array = cJSON_CreateArray();
    if (array == NULL)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, NULL);
        return ESP_FAIL;
    }

    for (int i = 0; i < MAX_SCREEN; i++)
    {
        screen_t *screen = &get_main_display()->screen[i];
        if (screen->schedule_end == SCREEN_SCHEDULE_DISABLED)
            continue;

        cJSON *item = cJSON_CreateObject();
        cJSON_AddNumberToObject(item, "screen_id", i);

        char start_str[6], end_str[6];
        widget_schedule_format_time(screen->schedule_start, start_str, sizeof(start_str));
        widget_schedule_format_time(screen->schedule_end,   end_str,   sizeof(end_str));

        cJSON_AddStringToObject(item, "start", start_str);
        cJSON_AddStringToObject(item, "end",   end_str);
        cJSON_AddItemToArray(array, item);
    }

    char *response_str = cJSON_Print(array);
    cJSON_Delete(array);
    if (response_str == NULL)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, NULL);
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, response_str, strlen(response_str));
    free(response_str);
    return ESP_OK;
}

esp_err_t post_screen_schedule_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "POST");

    char buf[256];
    int ret = httpd_req_recv(req, buf, sizeof(buf) - 1);
    if (ret <= 0)
    {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Empty body");
        return ESP_FAIL;
    }
    buf[ret] = '\0';

    cJSON *array = cJSON_Parse(buf);
    if (array == NULL || !cJSON_IsArray(array))
    {
        cJSON_Delete(array);
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid JSON");
        return ESP_FAIL;
    }

    // Reset tous les schedules en RAM avant d'appliquer
    for (int i = 0; i < MAX_SCREEN; i++)
    {
        screen_t *screen = &get_main_display()->screen[i];
        screen->schedule_start = SCREEN_SCHEDULE_DISABLED;
        screen->schedule_end = SCREEN_SCHEDULE_DISABLED;
    }

    cJSON *item = NULL;
    cJSON_ArrayForEach(item, array)
    {
        cJSON *id_json    = cJSON_GetObjectItem(item, "screen_id");
        cJSON *start_json = cJSON_GetObjectItem(item, "start");
        cJSON *end_json   = cJSON_GetObjectItem(item, "end");

        if (!cJSON_IsNumber(id_json) || !cJSON_IsString(start_json) || !cJSON_IsString(end_json))
        {
            ESP_LOGW(TAG, "Invalid entry, skipping");
            continue;
        }

        uint8_t screen_id = (uint8_t)id_json->valueint;
        if (screen_id >= MAX_SCREEN)
        {
            ESP_LOGW(TAG, "screen_id %d out of range, skipping", screen_id);
            continue;
        }

        screen_t *screen = &get_main_display()->screen[screen_id];
        uint16_t start, end;
        if (widget_schedule_parse_time(start_json->valuestring, &start) != ESP_OK ||
                widget_schedule_parse_time(end_json->valuestring,   &end)   != ESP_OK)
        {
            ESP_LOGW(TAG, "Failed to parse time for screen %d, skipping", screen_id);
            continue;
        }

        screen->schedule_start = start;
        screen->schedule_end   = end;
        ESP_LOGI(TAG, "Screen %d schedule updated: %s → %s",
                screen_id, start_json->valuestring, end_json->valuestring);
    }

    cJSON_Delete(array);

    // Persistance
    esp_err_t err = screen_schedule_save();
    if (err != ESP_OK)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to save schedule");
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, "{\"status\":\"ok\"}");
    return ESP_OK;
}
