#include "API_system.h"
#include "cJSON.h"
#include "esp_mac.h"
#include "esp_timer.h"

static const char *TAG = "/api/system/config/diagnotic";

esp_err_t diagnostic_get_handler(httpd_req_t *req)
{
    ESP_LOGV(TAG, "Method: GET");

    uint64_t uptime_s = esp_timer_get_time() / 1000000ULL;

    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);

    char mac_str[18];
    snprintf(mac_str, sizeof(mac_str),
            "%02X:%02X:%02X:%02X:%02X:%02X",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);


    // Build JSON
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "mac_address", mac_str);
    cJSON_AddNumberToObject(root, "uptime_s", uptime_s);
    cJSON_AddStringToObject(root, "sdk_version", esp_get_idf_version());
    cJSON_AddNumberToObject(root, "reset_reason", esp_reset_reason());

    cJSON_AddNumberToObject(root, "heap_free", esp_get_free_heap_size());
    cJSON_AddNumberToObject(root, "heap_free_internal", esp_get_free_internal_heap_size());
    cJSON_AddNumberToObject(root, "heap_min_free", esp_get_minimum_free_heap_size());

    cJSON_AddNumberToObject(root, "heap_internal_free", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    cJSON_AddNumberToObject(root, "heap_spiram_free", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
    cJSON_AddNumberToObject(root, "heap_dma_free", heap_caps_get_free_size(MALLOC_CAP_DMA));


    cJSON_AddNumberToObject(root, "spiram_total", heap_caps_get_total_size(MALLOC_CAP_SPIRAM));
    cJSON_AddNumberToObject(root, "spiram_free", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
    cJSON_AddNumberToObject(root, "spiram_min_free", heap_caps_get_minimum_free_size(MALLOC_CAP_SPIRAM));

    cJSON_AddNumberToObject(root, "largest_free_block_internal", heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL));
    cJSON_AddNumberToObject(root, "largest_free_block_spiram", heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM));

    char *json = cJSON_PrintUnformatted(root);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_sendstr(req, json);

    free(json);
    cJSON_Delete(root);

    return ESP_OK;
}

