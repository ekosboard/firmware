#include "API_ui.h"

static const char *TAG = "api/ui/widgets/available";

esp_err_t get_available_widgets_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG,);

    esp_err_t err = mount_lfs();
    if (err != ESP_OK)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, NULL);
        return ESP_FAIL;
    }

    char full_path[128];
    snprintf(full_path, sizeof(full_path),"%s/%s", LFS_BASE_PATH, WIDGET_TEMPLATE_INDEX);
    cJSON *available_widgets_json = read_json_file(full_path, READ_LFS);

    err = unmount_lfs();
    if (err != ESP_OK)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, NULL);
        return ESP_FAIL;
    }

    // Créer la réponse JSON
    char *response_str = cJSON_Print(available_widgets_json);
    if (response_str == NULL)
    {
        cJSON_Delete(available_widgets_json);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, NULL);
        return ESP_FAIL;
    }

    // Envoi de la réponse
    httpd_resp_send(req, response_str, strlen(response_str));
    free(response_str);
    cJSON_Delete(available_widgets_json);

    return ESP_OK;
}

const httpd_uri_t available_widgets = {
    .uri        = "/api/ui/widgets/available",
    .method     = HTTP_GET,
    .handler    = get_available_widgets_handler,
    .user_ctx   = NULL
};

void register_available_widgets_uri(httpd_handle_t server)
{
    httpd_register_uri_handler(server, &available_widgets);
}

void unregister_available_widgets_uri(httpd_handle_t server)
{
    httpd_unregister_uri_handler(server, available_widgets.uri, HTTP_GET);
}

