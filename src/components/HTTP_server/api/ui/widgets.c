#include "API_ui.h"
#include "esp_log.h"
#include "widget.h"

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
        widget_update_t widget = {
            .type = widget_info->type,
            .action = action,
            .pos_x = pos_x,
            .pos_y = pos_y,
            .height = height,
            .width = width,
            .flag = 0,
        };

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
    .uri        = "/api/ui/widgets",
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
