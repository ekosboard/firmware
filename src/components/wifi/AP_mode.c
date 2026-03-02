#include "wifi.h"

static const char *TAG = "wifi AP_mode";

void wifi_init_ap(void)
{
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = WIFI_AP_SSID,
            .ssid_len = strlen(WIFI_AP_SSID),
            .channel = WIFI_AP_CHANNEL,
            .password = WIFI_AP_PASS,
            .max_connection = WIFI_AP_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA2_PSK,
            .pmf_cfg = {
                    .required = true,
            },
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s channel:%d", WIFI_AP_SSID, WIFI_AP_PASS, WIFI_AP_CHANNEL);
}


//FIXME: return esp_err_t
void wifi_start_ap()
{
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    wifi_init_ap();

    char wifi_data[128];
    snprintf(wifi_data, sizeof(wifi_data), "WIFI:T:WPA;S:%s;P:%s;;", WIFI_AP_SSID, WIFI_AP_PASS);
    if (lvgl_lock(-1))
    {
        draw_screen_wifi_config(wifi_data);
        lvgl_unlock();
    }

    ESP_ERROR_CHECK(esp_wifi_start());
    start_mdns_service();
}
