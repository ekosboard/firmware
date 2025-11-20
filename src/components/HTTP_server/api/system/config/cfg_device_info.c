#include "device_info.h"
#include "HTTP_server.h"
#include "cJSON.h"
#include "esp_http_server.h"
#include "esp_timer.h"
#include "esp_netif.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "/api/system/config/device_info";

// Helper pour récupérer l’IP locale en string
static void get_local_ip(char *buffer, size_t len)
{
    esp_netif_ip_info_t ip_info;
    esp_netif_t *netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");

    if (netif && esp_netif_get_ip_info(netif, &ip_info) == ESP_OK)
    {
        snprintf(buffer, len, IPSTR, IP2STR(&ip_info.ip));
    }
    else
    {
        strncpy(buffer, "0.0.0.0", len);
    }
}

esp_err_t device_info_get_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Method: GET");

    device_info_t device_info;
    device_info_load(&device_info);

    char ip[16];
    get_local_ip(ip, sizeof(ip));

    uint64_t uptime_s = esp_timer_get_time() / 1000000ULL;

    cJSON *root = cJSON_CreateObject();
    if (!root) return httpd_resp_send_500(req);

    cJSON_AddStringToObject(root, "device_name", device_info.device_name);
    cJSON_AddStringToObject(root, "hostname", device_info.hostname);
    cJSON_AddStringToObject(root, "firmware_version", device_info.firmware_version);
    cJSON_AddStringToObject(root, "serial", device_info.serial);

    cJSON_AddStringToObject(root, "ip", ip);
    cJSON_AddNumberToObject(root, "uptime", uptime_s);
    cJSON_AddNumberToObject(root, "battery", 100); // placeholder

    /* cJSON_AddNumberToObject(root, "screen_width", lv_disp_get_hor_res(NULL)); */
    /* cJSON_AddNumberToObject(root, "screen_height", lv_disp_get_ver_res(NULL)); */

    char *json = cJSON_PrintUnformatted(root);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, json, strlen(json));

    cJSON_Delete(root);
    free(json);

    return ESP_OK;
}


esp_err_t device_info_patch_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Method: PATCH");

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
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid JSON");
        return ESP_FAIL;
    }

    esp_err_t err = ESP_OK;

    // device_name
    cJSON *device_name = cJSON_GetObjectItem(root, "device_name");
    if (cJSON_IsString(device_name)) {
        err = device_info_set_name(device_name->valuestring);
        if (err != ESP_OK) 
            goto fail;
    }

    // hostname
    cJSON *hostname = cJSON_GetObjectItem(root, "hostname");
    if (cJSON_IsString(hostname)) {
        err = device_info_set_hostname(hostname->valuestring);
        if (err != ESP_OK) 
            goto fail;
    }

    cJSON_Delete(root);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, "{\"status\":\"ok\"}");
    return ESP_OK;

fail:
    cJSON_Delete(root);
    httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "NVS error");
    return err;
}

