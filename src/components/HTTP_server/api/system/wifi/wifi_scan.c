#include "API_system.h"
#include "HTTP_server.h"
#include "esp_err.h"
#include "esp_wifi_types_generic.h"
#include "wifi.h"

static const char *TAG = "/api/system/wifi/scan";

esp_err_t       wifi_scan_get_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "GET");

    esp_err_t err;
    uint16_t ap_max = 10;
    uint16_t ap_count = 0;
    wifi_ap_record_t ap_info[ap_max];
    memset(ap_info, 0, sizeof(ap_info));

    err = wifi_scan_ap(&ap_max, &ap_count, ap_info);
    if (err != ESP_OK)
    {
        ESP_LOGI(TAG, "ERREUR: %s", esp_err_to_name(err));
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Scan failed");
        return err;
    }


    if (ap_count == 0)
    {
        httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "No AP found");
        return ESP_OK;
    }

    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < ap_count; i++)
    {
        cJSON *ap = cJSON_CreateObject();
        cJSON_AddStringToObject(ap, "ssid", (const char *)ap_info[i].ssid);
        cJSON_AddNumberToObject(ap, "rssi", ap_info[i].rssi);
        cJSON_AddNumberToObject(ap, "channel", ap_info[i].primary);
        cJSON_AddItemToArray(root, ap);
    }

    char *response_str = cJSON_PrintUnformatted(root);
    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, response_str, strlen(response_str));

    free(response_str);
    cJSON_Delete(root);
    return ESP_OK;
}

const httpd_uri_t wifi_scan = {
    .uri        = "/api/system/wifi/scan",
    .method     = HTTP_GET,
    .handler    = wifi_scan_get_handler,
    .user_ctx   = NULL
};

void            register_wifi_scan_uri(httpd_handle_t server)
{
    httpd_register_uri_handler(server, &wifi_scan);
}

void            unregister_wifi_scan_uri(httpd_handle_t server)
{
    httpd_unregister_uri_handler(server, wifi_scan.uri, HTTP_GET);
}
