#include "HTTP_server.h"
#include "esp_http_server.h"
#include "freertos/idf_additions.h"
#include "wifi_switch.h"

static QueueHandle_t wifi_switch_queue;

esp_err_t wifi_switch_post_handler(httpd_req_t *req)
{
    char *content = NULL;
    if (read_http_request_content(req, &content) != ESP_OK)
        return ESP_FAIL;

    cJSON *root = cJSON_Parse(content);
    if (!root)
    {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "invalid json");
        return ESP_FAIL;
    }

    cJSON *ssid_json = cJSON_GetObjectItem(root, "ssid");
    cJSON *pass_json = cJSON_GetObjectItem(root, "password");
    if (!ssid_json || !pass_json)
    {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "missing ssid/password");
        cJSON_Delete(root);
        return ESP_FAIL;
    }

    wifi_switch_request_t req_data = {0};
    strncpy(req_data.ssid, ssid_json->valuestring, sizeof(req_data.ssid)-1);
    strncpy(req_data.pass, pass_json->valuestring, sizeof(req_data.pass)-1);

    cJSON_Delete(root);

    httpd_resp_set_status(req, "202 Accepted");
    /* httpd_resp_send(req, NULL, 0); */
    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, "{\"status\":\"switching\"}");

    push_wifi_switch_queue(req_data);

    return ESP_OK;
}
