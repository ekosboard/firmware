#include "API_ui.h"
#include "UI.h"

static const char *TAG = "/api/ui/screens";

esp_err_t get_screens_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "GET");

    uint8_t active_screen = get_main_display()->active_screen;

    cJSON *response = cJSON_CreateObject();
    cJSON *screens_array = cJSON_CreateArray();
    if (response == NULL || screens_array == NULL)
    {
        cJSON_Delete(response);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, NULL);
        return ESP_FAIL;
    }

    for (int i = 0; i < MAX_SCREEN; i++)
    {
        cJSON *screen_json = cJSON_CreateObject();
        cJSON_AddNumberToObject(screen_json, "screen_id", i);
        cJSON_AddBoolToObject(screen_json, "active", i == active_screen);

        cJSON *widget_ids = cJSON_CreateArray();
        screen_t *screen = &get_main_display()->screen[i];
        widget_node_t *current = screen->widget_display_list;
        while (current != NULL)
        {
            cJSON_AddItemToArray(widget_ids, cJSON_CreateNumber(current->widget->type));
            current = current->next;
        }
        cJSON_AddItemToObject(screen_json, "widget_ids", widget_ids);
        cJSON_AddItemToArray(screens_array, screen_json);
    }
    cJSON_AddItemToObject(response, "screens", screens_array);

    char *response_str = cJSON_Print(response);
    if (response_str == NULL)
    {
        cJSON_Delete(response);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, NULL);
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, response_str, strlen(response_str));
    free(response_str);
    cJSON_Delete(response);
    return ESP_OK;
}
