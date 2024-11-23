#include "API_ui.h"
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

    cJSON *id_json = NULL;
    cJSON *action_json = NULL;
    cJSON *pos_json = NULL, *pos_x_json = NULL, *pos_y_json = NULL;
    cJSON *size_json = NULL, *height_json = NULL, *width_json = NULL;
    const char *id = NULL;
    int action = 0, pos_x = 0, pos_y = 0, height = 0, width = 0;

    if (get_json_string_item(root, "id", &id_json, &id) != ESP_OK \
            || get_json_number_item(root, "action", &action_json, &action) != ESP_OK \
            || get_json_object_item(root, "pos", &pos_json) != ESP_OK \
            || get_json_number_item(pos_json, "x", &pos_x_json, &pos_x) != ESP_OK \
            || get_json_number_item(pos_json, "y", &pos_y_json, &pos_y) != ESP_OK \
            || get_json_object_item(root, "size", &size_json) != ESP_OK \
            || get_json_number_item(size_json, "height", &height_json, &height) != ESP_OK \
            || get_json_number_item(size_json, "width", &width_json, &width) != ESP_OK)
    {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "api/ui/widgets invalid data");
        cJSON_Delete(root);
        return ESP_FAIL;
    }

    const widget_t *widget_info;
    esp_err_t err = get_widget_by_id(id, &widget_info);
    if (err != ESP_OK)
    {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "api/ui/widgets invalid widget");
        cJSON_Delete(root);
        return ESP_FAIL;
    }

    widget_update_t widget = {
        .type = widget_info->type,
        .action = action,
        .pos_x = pos_x,
        .pos_y = pos_y,
        .height = height,
        .width = width,
        .flag = 0,
    };

    push_widget_update_queue(&widget);
    cJSON_Delete(root);

    httpd_resp_send(req, NULL, 0);
    return ESP_OK;
}

const httpd_uri_t widgets_uri = {
    .uri        = "/api/ui/widgets",
    .method     = HTTP_PUT,
    .handler    = widgets_put_handler,
    .user_ctx   = NULL
};

void            register_widgets(httpd_handle_t server)
{
    httpd_register_uri_handler(server, &widgets_uri);
}

void            unregister_widgets(httpd_handle_t server)
{
    httpd_unregister_uri_handler(server, widgets_uri.uri, HTTP_PUT);
}
