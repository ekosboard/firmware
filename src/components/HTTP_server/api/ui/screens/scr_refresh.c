#include "API_ui.h"
#include "UI.h"
#include "screen_manager.h"

static const char *TAG = "/api/ui/screen/refresh";

esp_err_t post_refresh_screen_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "POST");

    // Lecture du payload
    char buf[64];
    int ret = httpd_req_recv(req, buf, sizeof(buf) - 1);
    if (ret <= 0)
    {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Empty body");
        return ESP_FAIL;
    }
    buf[ret] = '\0';

    // Parse JSON
    cJSON *body = cJSON_Parse(buf);
    if (body == NULL)
    {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid JSON");
        return ESP_FAIL;
    }

    cJSON *screen_id_json = cJSON_GetObjectItem(body, "screen_id");
    if (!cJSON_IsNumber(screen_id_json))
    {
        cJSON_Delete(body);
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Missing or invalid screen_id");
        return ESP_FAIL;
    }

    uint8_t screen_id = (uint8_t)screen_id_json->valueint;
    cJSON_Delete(body);

    // Validation
    if (screen_id >= MAX_SCREEN)
    {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "screen_id out of range");
        return ESP_FAIL;
    }

    // Déjà actif
    if (screen_id != get_main_display()->active_screen)
    {
        httpd_resp_set_type(req, "application/json");
        httpd_resp_sendstr(req, "{\"status\":\"inactive\"}");
        return ESP_OK;
    }

    // Force refresh
    notify_screen_manager(SCREEN_ACTION_FORCE_REFRESH, screen_id);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, "{\"status\":\"ok\"}");
    return ESP_OK;
}
