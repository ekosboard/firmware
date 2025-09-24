#include "esp_err.h"
#include "esp_wifi.h"
#include "esp_wifi_types_generic.h"
#include "wifi.h"

const static char *TAG = "WIFI_SCAN";

esp_err_t   wifi_scan_ap(uint16_t *ap_max, uint16_t *ap_count, wifi_ap_record_t *ap_info)
{
    esp_err_t err;

    err = esp_wifi_scan_start(NULL, true);
    if (err != ESP_OK)
        return err;

    err = esp_wifi_scan_get_ap_num(ap_count);
    if (err != ESP_OK)
        return err;

    err = esp_wifi_scan_get_ap_records(ap_max, ap_info);
    if (err != ESP_OK)
        return err;

    return ESP_OK;
}
