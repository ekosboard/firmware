#include "API_system.h"
#include "HTTP_server.h"

//FIXME: check len of ssid/password
static const char *TAG = "/api/system/wifi/credentials";


/* Handles an HTTP POST request to store Wi-Fi credentials (SSID and password) in the NVS data partition. */
/* @Return Values: */
/* - ESP_OK if the credentials are stored successfully. */
/* - ESP_FAIL in case of any error during the process. */
esp_err_t wifi_credentials_post_handler(httpd_req_t *req)
{
    char buf[BUF_SIZE];
    int ret, remaining = req->content_len;
    cJSON *root = NULL;
    cJSON *ssid_json = NULL;
    cJSON *password_json = NULL;
    esp_err_t err;

    while (remaining > 0) {
        /* Read the data for the request */
        if ((ret = httpd_req_recv(req, buf, MIN(remaining, sizeof(buf)))) <= 0)
        {
            if (ret == HTTPD_SOCK_ERR_TIMEOUT)
            {
                /* Retry receiving if timeout occurred */
                continue;
            }
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, esp_err_to_name(ret));
            return ESP_FAIL;
        }

        /* Parse the JSON data */
        root = cJSON_Parse(buf);
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
        remaining -= ret;
    }

    httpd_resp_send(req, NULL, 0);
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
