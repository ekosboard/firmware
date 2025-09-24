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

    ////////////////////////////////////////////////////////////////////////////////
    //  WIFI MAIN
    ////////////////////////////////////////////////////////////////////////////////
    void        start_wifi(void);

    ////////////////////////////////////////////////////////////////////////////////
    //  AP MODE
    ////////////////////////////////////////////////////////////////////////////////
    void        wifi_init_ap(void);

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
