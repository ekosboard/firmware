#ifndef WIFI_AP_H
#define WIFI_AP_H

#include <string.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_event.h"
#include "esp_event_base.h"
#include "esp_wifi.h"
#include "esp_wifi_types_generic.h"
#include "esp_netif_sntp.h"
#include "esp_sntp.h"
#include "esp_mac.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "UI.h"
#include "filesystem_interface.h"


#define WIFI_AP_SSID                "SmartPaper"
#define WIFI_AP_PASS                "smartpaper"
#define WIFI_AP_CHANNEL             1
#define WIFI_AP_MAX_STA_CONN        4

#define WIFI_STA_SSID_MAX_LEN       33
#define WIFI_STA_PWD_MAX_LEN        100
#define WIFI_STA_CONNECTED_BIT      BIT0
#define WIFI_STA_FAIL_BIT           BIT1
#define WIFI_STA_MAX_RETRY          5

#define MDNS_HOSTNAME               "smart-paper"
#define MDNS_INSTANCE               "SmartPaper Web Server"

#define STA_CONNECTED               0
#define STA_DISCONNECTED            1

extern esp_netif_t                  *esp_netif_ap;
extern esp_netif_t                  *esp_netif_sta;
extern EventGroupHandle_t           s_wifi_event_group;


#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Performs the initial Wi-Fi subsystem setup at application startup.
     *
     * This function must be called once during system initialization
     * (typically at boot) to set up the foundational Wi-Fi components.
     * Unlike clean_start_wifi(), this function does not start the Wi-Fi driver,
     * but prepares the required infrastructure so that Wi-Fi can be started later.
     *
     * Operations performed:
     * - Initializes the default network interface (init_network_interface()).
     * - Loads Wi-Fi configuration from storage (init_wifi_config()).
     * - Creates and initializes the FreeRTOS event group used for Wi-Fi events (init_wifi_event_group()).
     *
     * @note This function should only be called once during startup.
     * Subsequent Wi-Fi lifecycle operations (start/stop/restart) should use
     * clean_start_wifi() and clean_stop_wifi().
     */
    void init_wifi(void);

    /**
     * @brief Cleanly stops and deinitializes the Wi-Fi subsystem.
     *
     * This function shuts down the Wi-Fi interface and releases all related
     * resources to ensure a consistent state before reinitialization.
     *
     * Operations performed:
     * - Stops the mDNS service (mdns_free()).
     * - Stops the Wi-Fi driver (esp_wifi_stop()).
     * - Deinitializes the Wi-Fi driver (esp_wifi_deinit()).
     * - Clears the default Wi-Fi driver and event handlers (esp_wifi_clear_default_wifi_driver_and_handlers()).
     * - Destroys the default Wi-Fi station interface (esp_netif_destroy_default_wifi()).
     *
     * This function should be called before reinitializing or restarting Wi-Fi
     * using clean_start_wifi(), for example after a deep/light sleep cycle
     * or when network connectivity must be fully reset.
     */
    void clean_stop_wifi(void);

    /**
     * @brief Initializes and starts the Wi-Fi subsystem in station mode.
     *
     * This function sets up the default Wi-Fi station interface, initializes
     * the Wi-Fi driver, and connects to the configured network.
     * It also restarts the mDNS service after Wi-Fi has been started.
     *
     * Operations performed:
     * - Loads Wi-Fi configuration via init_wifi_config().
     * - Creates the default Wi-Fi station interface (esp_netif_create_default_wifi_sta()).
     * - Sets the created interface as the default network interface.
     * - Initializes the Wi-Fi stack and configures it as station mode (wifi_init_sta()).
     * - Applies power-save mode (esp_wifi_set_ps(WIFI_PS_MIN_MODEM)).
     * - Starts the Wi-Fi driver (esp_wifi_start()).
     * - Restarts the mDNS service (start_mdns_service()).
     *
     * This function should be called after clean_stop_wifi() when resuming
     * connectivity, for example after waking up from sleep.
     */
    void clean_start_wifi(void);

    ////////////////////////////////////////////////////////////////////////////////
    //  AP MODE
    ////////////////////////////////////////////////////////////////////////////////
    void        wifi_init_ap(void);
    void        wifi_start_ap(void);

    ////////////////////////////////////////////////////////////////////////////////
    //  STA MODE
    ////////////////////////////////////////////////////////////////////////////////
    esp_err_t   wifi_init_sta(void);
    esp_err_t   wifi_start_sta(void);
    esp_err_t   wifi_connected_to(char *ssid);

    ////////////////////////////////////////////////////////////////////////////////
    //  WIFI EVENT
    ////////////////////////////////////////////////////////////////////////////////
    void        init_wifi_event_group(void);
    void        wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

    ////////////////////////////////////////////////////////////////////////////////
    //  UTILS
    ////////////////////////////////////////////////////////////////////////////////
    void        start_mdns_service(void);
    esp_err_t   init_sntp(char *timezone);
    esp_err_t   wifi_scan_ap(uint16_t *ap_max, uint16_t *ap_count, wifi_ap_record_t *ap_info);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
