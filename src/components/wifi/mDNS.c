#include "wifi.h"
#include "mdns.h"

static const char *TAG = "mDNS";


void start_mdns_service() {
    // Initialiser le service mDNS
    esp_err_t err = mdns_init();
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "mDNS init failed: %d", err);
        return;
    }

    // Définir le nom de l'appareil (hostname)
    mdns_hostname_set(MDNS_HOSTNAME);
    ESP_LOGI(TAG, "mDNS hostname set to: %s.local", MDNS_HOSTNAME);

    // Définir un nom pour le service
    mdns_instance_name_set(MDNS_INSTANCE);

    // Annoncer un service HTTP sur le port 80
    mdns_service_add(MDNS_INSTANCE, "_http", "_tcp", 80, NULL, 0);
    ESP_LOGI(TAG, "mDNS service added: _http._tcp.local");
}
