#include "API_system.h"
#include "HTTP_server.h"
#include "http_parser.h"

//FIXME: check len of ssid/password
static const char *TAG = "/api/system/wifi/credentials";


/* Handles an HTTP POST request to store Wi-Fi credentials (SSID and password) in the NVS data partition. */
/* @Return Values: */
/* - ESP_OK if the credentials are stored successfully. */
/* - ESP_FAIL in case of any error during the process. */
esp_err_t wifi_credentials_post_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "POST");

    char *content = NULL;
    if (read_http_request_content(req, &content) != ESP_OK)
    {
        return ESP_FAIL;
    }

    esp_err_t err;
    cJSON *root = NULL;
    cJSON *ssid_json = NULL;
    cJSON *password_json = NULL;
    root = cJSON_Parse(content);
    if (root == NULL)
    {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "/api/system/wifi/credentials invalid data");
        return ESP_FAIL;
    }
    ssid_json = cJSON_GetObjectItem(root, "ssid");
    password_json = cJSON_GetObjectItem(root, "password");
    if (ssid_json == NULL || password_json == NULL)
    {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "/api/system/wifi/credentials invalid data");
        cJSON_Delete(root);
        return ESP_FAIL;
    }

    /* Write wifi credentials in nvs data partition */
    err = nvs_wifi_write_credential(ssid_json->valuestring, password_json->valuestring);
    cJSON_Delete(root);
    if (err != ESP_OK)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, esp_err_to_name(err));
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, "{\"status\":\"ok\"}");

    return ESP_OK;
}

const httpd_uri_t wifi_credentials = {
    .uri       = "/api/system/wifi/credentials",
    .method    = HTTP_POST,
    .handler   = wifi_credentials_post_handler,
    .user_ctx  = NULL
};

void register_wifi_credentials_uri(httpd_handle_t server) 
{
    httpd_register_uri_handler(server, &wifi_credentials);
}

void unregister_wifi_credentials_uri(httpd_handle_t server) 
{
    httpd_unregister_uri_handler(server, wifi_credentials.uri, HTTP_POST);
}



esp_err_t wifi_credentials_delete_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "DELETE");
    httpd_resp_send(req, NULL, 0);
    return ESP_OK;
}

const httpd_uri_t wifi_credentials_delete = {
    .uri       = "/api/system/wifi/credentials/delete",
    .method    = HTTP_DELETE,
    .handler   = wifi_credentials_delete_handler,
    .user_ctx  = NULL
};

void register_wifi_credentials_delete_uri(httpd_handle_t server) 
{
    httpd_register_uri_handler(server, &wifi_credentials_delete);
}

void unregister_wifi_credentials_delete_uri(httpd_handle_t server) 
{
    httpd_unregister_uri_handler(server, wifi_credentials_delete.uri, HTTP_DELETE);
}
