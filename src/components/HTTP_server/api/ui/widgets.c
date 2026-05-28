#include "API_ui.h"
#include "cJSON.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "widget.h"
#include "widget_config_list.h"
#include "widget_schedule.h"
#include "widget_template_interval.h"

static const char *TAG = "api/ui/widgets";

/* Handles HTTP PUT requests to update widget */
/* @Parameters: */
/*     - req: Pointer to the HTTP request containing JSON payload with widget update information. */
/* @Return: */
/*     - ESP_OK: Request processed successfully, widget updated. */
/*     - ESP_FAIL: Failed to parse JSON or handle the request properly. */
/*     - HTTPD_400_BAD_REQUEST: Invalid data or widget ID in the request. */
/*     - HTTPD_500_INTERNAL_SERVER_ERROR: Internal server error encountered. */
esp_err_t widgets_put_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Handling widgets PUT request");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");

    char query[64] = {0};
    char screen_param[16] = {0};
    uint8_t screen_id = 0;
    if (httpd_req_get_url_query_str(req, query, sizeof(query)) == ESP_OK)
    {
        if (httpd_query_key_value(query, "screen", screen_param, sizeof(screen_param)) == ESP_OK)
        {
            ESP_LOGI(TAG, "?screen=%s", screen_param);

            char *end = NULL;
            screen_id = (uint8_t)strtoul(screen_param, &end, 10);
            if (end == screen_param || errno == ERANGE || *end != '\0')
            {
                httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid screen query");
                return ESP_FAIL;
            }

            if (screen_id >= MAX_SCREEN)
            {
                char buff[50];
                snprintf(buff, sizeof(buff), "Invalid screen query, device MAX_SCREEN: %d", MAX_SCREEN);
                httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, buff);
                return ESP_FAIL;
            }
        }
    }

    char *content = NULL;
    if (read_http_request_content(req, &content) != ESP_OK)
    {
        return ESP_FAIL;
    }

    cJSON *root = NULL;
    root = cJSON_Parse(content);
    free(content);
    if (root == NULL)
    {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "api/ui/widgets invalid data");
        return ESP_FAIL;
    }

    int array_size = cJSON_GetArraySize(root);
    ESP_LOGI(TAG, "Received %d widget updates", array_size);

    cJSON *failed_updates = cJSON_CreateArray(); // Stocke les erreurs
    int processed_count = 0;

    for (int i = 0; i < array_size; i++)
    {
        cJSON *item = cJSON_GetArrayItem(root, i);
        if (!item)
        {
            continue;
        }
        cJSON *id_json = NULL;
        cJSON *action_json = NULL;
        cJSON *pos_json = NULL, *pos_x_json = NULL, *pos_y_json = NULL;
        cJSON *size_json = NULL, *height_json = NULL, *width_json = NULL;
        const char *id = NULL;
        int action = 0, pos_x = 0, pos_y = 0, height = 0, width = 0;

        if (get_json_string_item(item, "id", &id_json, &id) != ESP_OK \
                || get_json_number_item(item, "action", &action_json, &action) != ESP_OK \
                || get_json_object_item(item, "pos", &pos_json) != ESP_OK \
                || get_json_number_item(pos_json, "x", &pos_x_json, &pos_x) != ESP_OK \
                || get_json_number_item(pos_json, "y", &pos_y_json, &pos_y) != ESP_OK \
                || get_json_object_item(item, "size", &size_json) != ESP_OK \
                || get_json_number_item(size_json, "height", &height_json, &height) != ESP_OK \
                || get_json_number_item(size_json, "width", &width_json, &width) != ESP_OK)
        {
            ESP_LOGW(TAG, "Invalid widget data at index %d", i);
            // Ajouter l'erreur à la liste
            cJSON *error_obj = cJSON_CreateObject();
            cJSON_AddStringToObject(error_obj, "id", id ? id : "unknown");
            cJSON_AddStringToObject(error_obj, "reason", "Invalid data format");
            cJSON_AddItemToArray(failed_updates, error_obj);
            continue;
        }

        const widget_t *widget_info;
        esp_err_t err = get_widget_by_id(id, &widget_info);
        if (err != ESP_OK)
        {
            ESP_LOGW(TAG, "Invalid widget ID: %s", id);

            // Ajouter l'erreur à la liste
            cJSON *error_obj = cJSON_CreateObject();
            cJSON_AddStringToObject(error_obj, "id", id);
            cJSON_AddStringToObject(error_obj, "reason", "Widget ID not found");
            cJSON_AddItemToArray(failed_updates, error_obj);

            continue;
        }

        ESP_LOGI("HTTP/Widget", "\nPos_x: %d\n Pos_y: %d", pos_x, pos_y);
        ESP_LOGI("HTTP/Widget", "\nWidth: %d\n Height: %d", width, height);
        ESP_LOGI("HTTP/Widget", "\nAction: %d", action);
        widget_update_t widget = {
            .screen_id = screen_id,
            .type = widget_info->type,
            .action = action,
            .pos_x = pos_x,
            .pos_y = pos_y,
            .height = height,
            .width = width,
            .flag = widget_info->flag,
            .update_data_interval_ms = widget_info->update_data_interval_ms,
            .update_schedule_end = widget_info->update_schedule_end,
            .update_schedule_start = widget_info->update_schedule_start,
            .config = NULL
        };

        // Update interval
        cJSON *update_interval = cJSON_GetObjectItem(item, "update_interval");
        if (cJSON_IsString(update_interval))
        {
            widget.update_data_interval_ms = widget_template_parse_interval_ms(update_interval->valuestring);
        }

        // Champs dynamiques: config
        cJSON *config = cJSON_GetObjectItem(item, "config");
        if (cJSON_IsObject(config))
        {
            cJSON *entry = NULL;
            cJSON_ArrayForEach(entry, config)
            {
                if (cJSON_IsString(entry))
                {
                    widget.config = widget_config_list_create_node(widget.config, entry->string, entry->valuestring);
                    ESP_LOGI("HTTP/Widget", "key: %s\n value: %s", widget.config->key, widget.config->value);
                }
            }
        }

        cJSON *schedule = cJSON_GetObjectItem(item, "update_schedule");
        if (cJSON_IsObject(schedule))
        {
            cJSON *start = cJSON_GetObjectItem(schedule, "start");
            cJSON *end = cJSON_GetObjectItem(schedule, "end");
            if (cJSON_IsString(start) && cJSON_IsString(end))
            {
                uint16_t s = 0, e = 0;
                if (widget_schedule_parse_time(start->valuestring, &s) == ESP_OK &&
                        widget_schedule_parse_time(end->valuestring,   &e) == ESP_OK)
                {
                    widget.update_schedule_start = s;
                    widget.update_schedule_end = e;
                }
            }
        }

        //FIXME: Vérifier si la queue est pleine avant d'envoyer
        //maybe add delay or change queue managment for handle batch widget updates
        push_widget_update_queue(&widget);
    }

    // Construire la réponse JSON
    cJSON *response = cJSON_CreateObject();
    cJSON_AddNumberToObject(response, "success_count", processed_count);
    cJSON_AddItemToObject(response, "failed_updates", failed_updates);

    char *response_str = cJSON_PrintUnformatted(response);
    cJSON_Delete(response);

    // Envoyer la réponse HTTP
    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, response_str, strlen(response_str));

    free(response_str);

    cJSON_Delete(root);

    /* httpd_resp_send(req, NULL, 0); */
    return ESP_OK;
}

const httpd_uri_t widgets_uri = {
    .uri        = "/api/ui/widgets*",
    .method     = HTTP_PUT,
    .handler    = widgets_put_handler,
    .user_ctx   = NULL
};

void register_widgets(httpd_handle_t server)
{
    httpd_register_uri_handler(server, &widgets_uri);
}

void unregister_widgets(httpd_handle_t server)
{
    httpd_unregister_uri_handler(server, widgets_uri.uri, HTTP_PUT);
}
