#include "API_system.h"
#include "HTTP_server.h"

static const char *TAG = "api/system/wifi/scan";

/* TODO: version de test a remplacer */
esp_err_t       wifi_scan_get_handler(httpd_req_t *req)
{
    cJSON *root = cJSON_CreateArray();

    // Création des objets SSID et ajout au tableau
    cJSON *ssid1 = cJSON_CreateObject();
    cJSON_AddStringToObject(ssid1, "SSID", "ssid_name1");
    cJSON_AddItemToArray(root, ssid1);

    cJSON *ssid2 = cJSON_CreateObject();
    cJSON_AddStringToObject(ssid2, "SSID", "ssid_name2");
    cJSON_AddItemToArray(root, ssid2);

    // Ajout d'un troisième SSID si nécessaire
    cJSON *ssid3 = cJSON_CreateObject();
    cJSON_AddStringToObject(ssid3, "SSID", "ssid_name3");
    cJSON_AddItemToArray(root, ssid3);

    // Convertir le JSON en chaîne de caractères
    char *json_data = cJSON_Print(root);

    // Envoyer la réponse HTTP
    httpd_resp_send(req, json_data, strlen(json_data));

    // Libérer la mémoire utilisée par cJSON
    free(json_data);
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
