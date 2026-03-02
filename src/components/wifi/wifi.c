#include "wifi.h"
#include "esp_err.h"
#include "esp_netif_types.h"
#include "esp_wifi.h"
#include "esp_wifi_default.h"
#include "esp_wifi_types_generic.h"
#include "mdns.h"
#include <stdbool.h>

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

void init_wifi(void)
{
    init_network_interface();
    init_wifi_config();
    init_wifi_event_group();
}

void clean_stop_wifi(void)
{
    mdns_free();
    esp_wifi_stop();
    esp_wifi_deinit();
    esp_wifi_clear_default_wifi_driver_and_handlers(esp_netif_sta);
    esp_netif_destroy_default_wifi(esp_netif_sta);
}

void clean_start_wifi(void)
{
    init_wifi_config();
    esp_netif_sta = esp_netif_create_default_wifi_sta();
    esp_netif_set_default_netif(esp_netif_sta);

    wifi_init_sta();
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    esp_wifi_set_ps(WIFI_PS_MIN_MODEM);
    ESP_ERROR_CHECK(esp_wifi_start());
    start_mdns_service();
}
