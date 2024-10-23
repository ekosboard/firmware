#include "wifi.h"
#include "EPD.h"
#include "filesystem_interface.h"

static const char *TAG = "WiFi";

esp_netif_t *esp_netif_ap;
esp_netif_t *esp_netif_sta;


/* Initializes the networking interfaces for both Access Point (AP) and Station (STA) modes. */
static void init_network_interface(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    esp_netif_ap = esp_netif_create_default_wifi_ap();
    esp_netif_sta = esp_netif_create_default_wifi_sta();
    esp_netif_set_default_netif(esp_netif_sta);
}

/* Initializes the Wi-Fi configuration structure. */
static void init_wifi_config(void)
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
}

/* Starts the Wi-Fi in either APSTA (Access Point + Station) or STA (Station) 
 * mode depending on the network connection status. */
void start_wifi(void)
{
    ESP_LOGI(TAG, "Start WiFi");
    ESP_ERROR_CHECK(nvs_init_interface());
    init_network_interface();
    init_wifi_config();
    init_wifi_event_group();

    if (wifi_init_sta() != ESP_OK)
    {
        wifi_init_ap();
        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));

        char wifi_data[128];
        snprintf(wifi_data, sizeof(wifi_data), "WIFI:T:WPA;S:%s;P:%s;;", WIFI_AP_SSID, WIFI_AP_PASS);
        if (lvgl_lock(-1))
        {
            draw_screen_wifi_config(wifi_data);
            lvgl_unlock();
        }
    }
    else
    {
        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    }

    ESP_ERROR_CHECK(esp_wifi_start());
    start_mdns_service();
}
