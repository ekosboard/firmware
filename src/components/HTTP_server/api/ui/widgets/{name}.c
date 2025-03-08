#include "API_ui.h"

static const char *TAG = "api/ui/widgets/{name}";

esp_err_t get_widget_template_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG,);


    esp_err_t err = mount_lfs();
    if (err != ESP_OK)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, NULL);
        return ESP_FAIL;
    }

    char name[128];
    sscanf(req->uri, "/api/ui/widgets/%127s", name);
    cJSON *widget_template_json = read_json_file(name, READ_LFS);
    if (widget_template_json == NULL) {
        httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Widget not found");
        unmount_lfs();
        return ESP_FAIL;
    }

    err = unmount_lfs();
    if (err != ESP_OK)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, NULL);
        return ESP_FAIL;
    }

    // Créer la réponse JSON
    char *response_str = cJSON_Print(widget_template_json);
    if (response_str == NULL)
    {
        cJSON_Delete(widget_template_json);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, NULL);
        return ESP_FAIL;
    }

    httpd_resp_send(req, response_str, strlen(response_str));
    free(response_str);
    cJSON_Delete(widget_template_json);

    return ESP_OK;
}

const httpd_uri_t widget_template = {
    .uri        = "/api/ui/widgets/*",
    .method     = HTTP_GET,
    .handler    = get_widget_template_handler,
    .user_ctx   = NULL
};

void register_widget_template_uri(httpd_handle_t server)
{
    httpd_register_uri_handler(server, &widget_template);
}

void unregister_widget_template_uri(httpd_handle_t server)
{
    httpd_unregister_uri_handler(server, widget_template.uri, HTTP_GET);
}
