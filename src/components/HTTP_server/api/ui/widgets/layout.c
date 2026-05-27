#include "API_ui.h"
#include "widget.h"
#include "widget_config_list.h"
#include "widget_schedule.h"
#include "widget_template_interval.h"
#include "cJSON.h"

static const char *TAG = "api/ui/widgets/layout";

esp_err_t get_widgets_layout_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "GET /api/ui/widgets/layout");

    //IF QUERRY
    /* char screen_param[16] = {0}; */
    /* bool all_screens = false; */
    /* if (httpd_query_key_value(req->uri, "screen", screen_param, sizeof(screen_param)) == ESP_OK) { */
    /*     all_screens = (strcmp(screen_param, "all") == 0); */
    /* } */

    screen_t *screen = get_active_screen();
    if (screen == NULL)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "No active screen");
        return ESP_FAIL;
    }

    cJSON *root = cJSON_CreateArray();
    if (root == NULL)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "JSON alloc failed");
        return ESP_FAIL;
    }

    widget_node_t *current = NULL;
    current = screen->widget_display_list;
    while (current != NULL)
    {
        widget_t *widget = current->widget;
        cJSON *item = cJSON_CreateObject();

        /* Nom du type  */
        const char *type_str = get_widget_type_to_string(widget->type);
        cJSON_AddStringToObject(item, "id", type_str ? type_str : "unknown");

        /* Position */
        cJSON *pos = cJSON_CreateObject();
        cJSON_AddNumberToObject(pos, "x", widget->pos_x);
        cJSON_AddNumberToObject(pos, "y", widget->pos_y);
        cJSON_AddItemToObject(item, "pos", pos);

        /* Taille */
        cJSON *size = cJSON_CreateObject();
        cJSON_AddNumberToObject(size, "width",  widget->width);
        cJSON_AddNumberToObject(size, "height", widget->height);
        cJSON_AddItemToObject(item, "size", size);

        /* Config (liste chaînée key/value) */
        cJSON *cfg = cJSON_CreateObject();
        widget_config_t *kv = widget->config;
        while (kv != NULL)
        {
            if (kv->key && kv->value)
            {
                cJSON_AddStringToObject(cfg, kv->key, kv->value);
            }
            kv = kv->next;
        }
        cJSON_AddItemToObject(item, "config", cfg);

        /* Intervalle de mise à jour (ms → string "1h30m") */
        char interval_str[32] = {0};
        widget_template_format_interval_ms(widget->update_data_interval_ms,interval_str, sizeof(interval_str));
        cJSON_AddStringToObject(item, "update_interval", interval_str);

        /* Fenêtre de mise à jour */
        char schedule_start[6] = {0};
        widget_schedule_format_time(widget->update_schedule_start, schedule_start, sizeof(schedule_start));
        char schedule_end[6] = {0};
        widget_schedule_format_time(widget->update_schedule_end, schedule_end, sizeof(schedule_end));

        cJSON *update_schedule = cJSON_CreateObject();
        cJSON_AddStringToObject(update_schedule, "start", schedule_start);
        cJSON_AddStringToObject(update_schedule, "end", schedule_end);
        cJSON_AddItemToObject(item, "update_schedule", update_schedule);


        cJSON_AddItemToArray(root, item);
        current = current->next;
    }

    char *json_str = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);

    if (json_str == NULL)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "JSON render failed");
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, json_str);
    free(json_str);

    return ESP_OK;
}

const httpd_uri_t widgets_layout = {
    .uri        = "/api/ui/widgets/layout",
    .method     = HTTP_GET,
    .handler    = get_widgets_layout_handler,
    .user_ctx   = NULL
};

void register_widgets_layout_uri(httpd_handle_t server)
{
    httpd_register_uri_handler(server, &widgets_layout);
}

void unregister_widgets_layout_uri(httpd_handle_t server)
{
    httpd_unregister_uri_handler(server, widgets_layout.uri, HTTP_GET);
}
