#include "API_ui.h"

static const char *TAG = "/api/ui/widgets/{name}";

esp_err_t get_widget_template_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "GET");

    esp_err_t err = mount_lfs();
    if (err != ESP_OK)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, NULL);
        return ESP_FAIL;
    }

    char name[128];
    sscanf(req->uri, "/api/ui/widgets/%127s", name);

    char full_path[256];
    snprintf(full_path, sizeof(full_path),"%s/%s/%s", LFS_BASE_PATH, LFS_TEMPLATE_DIR, name);

    cJSON *widget_template_json = read_json_file(full_path, READ_LFS);
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
