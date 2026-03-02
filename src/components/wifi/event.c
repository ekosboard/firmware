#include "EPD.h"
#include "filesystem_interface.h"
#include "freertos/idf_additions.h"
#include "wifi.h"
#include "wifi_switch.h"

static const char *TAG_AP = "WiFi event AP";
static const char *TAG_STA = "WiFi event STA";

EventGroupHandle_t s_wifi_event_group;


/* Handles various Wi-Fi and IP events for both Access Point (AP) and Station (STA) modes. */
/* @Parameters: */
/* - Optional argument passed to the handler (used for network interface pointer or other context). */
/* - The event base (e.g., WIFI_EVENT, IP_EVENT) that indicates the event source. */
/* - The specific event ID (e.g., WIFI_EVENT_AP_STACONNECTED, WIFI_EVENT_STA_DISCONNECTED). */
/* - Data related to the event, typically containing event-specific information. */
/* @Event Handling: */
/* - WIFI_EVENT_AP_STACONNECTED: Logs when a station (client) connects to the Access Point. */
/* - WIFI_EVENT_AP_STADISCONNECTED: Logs when a station disconnects from the Access Point, including the reason. */
/* - WIFI_EVENT_STA_START: Initiates the connection process in STA mode by calling esp_wifi_connect(). */
/* - WIFI_EVENT_STA_DISCONNECTED: Handles failed connection attempts. Retries to connect up to a maximum defined by WIFI_STA_MAX_RETRY. If the maximum retries are reached, the connection is considered failed. */
/* - IP_EVENT_STA_GOT_IP: Logs the IP address obtained by the station and sets the event group bit indicating the connection was successful. */
void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    static int s_retry_num = 0;

    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED)
    {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *) event_data;
        ESP_LOGI(TAG_AP, "Station "MACSTR" joined, AID=%d", MAC2STR(event->mac), event->aid);
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STADISCONNECTED)
    {
        wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *) event_data;
        ESP_LOGI(TAG_AP, "Station "MACSTR" left, AID=%d, reason:%d", MAC2STR(event->mac), event->aid, event->reason);
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        if (wifi_init_sta() == ESP_OK)
        {
            esp_wifi_connect();
            ESP_LOGI(TAG_STA, "Station started");
        }
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        if (check_wifi_is_switching() == true)
        {
            ESP_LOGI(TAG_STA, "Switching WiFi: skip auto-reconnect");
            s_retry_num = 0;
            return;
        }

        if (s_retry_num < WIFI_STA_MAX_RETRY)
        {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG_STA, "retry to connect to the AP");
        }
        else
        {
            s_retry_num = 0;
            xEventGroupSetBits(s_wifi_event_group, WIFI_STA_FAIL_BIT);
        }
        ESP_LOGI(TAG_STA,"connect to the AP fail");
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        s_retry_num = 0;
        ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
        ESP_LOGI(TAG_STA, "Got IP:" IPSTR, IP2STR(&event->ip_info.ip));
        xEventGroupSetBits(s_wifi_event_group, WIFI_STA_CONNECTED_BIT);

        // Set timezone to Europe/Paris
        init_sntp("CET-1CEST,M3.5.0,M10.5.0/3");

        /* TODO a faire a la fermeture de l'app ou deco client */
        /* esp_netif_t *esp_netif_ap = (esp_netif_t *) arg; */
        /* esp_wifi_deauth_sta(1); */
        /* esp_netif_dhcpc_stop(esp_netif_ap); */
        /* ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA)); */
    }
}

/* Initializes the event group for managing Wi-Fi connection events and registers the wifi_event_handler function to handle events. */
void init_wifi_event_group()
{
    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                    ESP_EVENT_ANY_ID,
                    &wifi_event_handler,
                    NULL,
                    NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                    IP_EVENT_STA_GOT_IP,
                    &wifi_event_handler,
                    esp_netif_ap,
                    NULL));
}
