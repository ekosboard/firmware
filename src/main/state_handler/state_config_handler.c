#include "HTTP_server.h"
#include "EPD.h"
#include "UI.h"
#include "config_timeout_ctx.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "input_manager.h"
#include "main.h"
#include "state_manager.h"
#include "wifi.h"
#include "screen_manager.h"

#ifdef CONFIG_USE_GT911
#include "gt911.h"
#endif

void state_config_handler(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data)
{
    TaskHandle_t *setup_task_handle = (TaskHandle_t*)handler_arg;
    display_t *display = get_main_display();

    switch (id)
    {
        case CONFIG_BEGIN:
            ESP_LOGI("CONFIG_BEGIN", "");
            xTaskCreate(http_server,
                    "http_server",
                    4096,
                    NULL,
                    4,
                    NULL
                    );

            config_timeout_ctx_set_timeout(DEFAULT_TIMEOUT_MS);
            xTaskNotify(setup_task_handle[SETUP_TIMEOUT_TASK], DEFAULT_TIMEOUT_MS, eSetValueWithOverwrite);

            EventBits_t wifi_event_bits = xEventGroupWaitBits(
                    s_wifi_event_group,
                    WIFI_STA_CONNECTED_BIT | WIFI_STA_FAIL_BIT,
                    pdFALSE,
                    pdFALSE,
                    portMAX_DELAY);

            if (wifi_event_bits & WIFI_STA_CONNECTED_BIT)
            {
                if (lvgl_lock(-1))
                {
                    wifi_ap_record_t ap_info;
                    if (esp_wifi_sta_get_ap_info(&ap_info) == ESP_OK)
                    {
                        draw_screen_wifi_success((char*)ap_info.ssid);
                    }
                    lvgl_unlock();
                }
            }
            break;

        case CONFIG_SAVE:
            break;

        case CONFIG_BEGIN_ISR:
            ESP_LOGI("CONFIG_BEGIN_ISR", "");
            xEventGroupWaitBits(
                    s_wifi_event_group,
                    WIFI_STA_CONNECTED_BIT,
                    pdFALSE,
                    pdTRUE,
                    pdMS_TO_TICKS(10000));

            xTaskCreate(http_server,
                    "http_server",
                    4096,
                    NULL,
                    4,
                    NULL
                    );

            config_timeout_ctx_set_timeout(DEFAULT_TIMEOUT_MS);
            xTaskNotify(setup_task_handle[SETUP_TIMEOUT_TASK], DEFAULT_TIMEOUT_MS, eSetValueWithOverwrite);
            resume_input_manager_task();
#ifdef CONFIG_USE_GT911
            gt911_exit_sleep(gt911_get());
#endif
            break;

        case CONFIG_EXIT:
            ESP_LOGI("CONFIG_EXIT", "ENTER");
            if (get_server_handler() != NULL) 
            {
                stop_webserver();
                ESP_LOGI("CONFIG_EXIT", "Stop webserver");
            }

            xEventGroupClearBits(get_epd_event_group(), EPD_EVENT_FLUSH_COMPLETE);
            notify_screen_manager(SCREEN_ACTION_DRAW_ONLY, display->active_screen);
            epd_wait_flush_complete(pdMS_TO_TICKS(5000));

            xEventGroupClearBits(get_epd_event_group(), EPD_EVENT_FLUSH_COMPLETE);
            notify_screen_manager(SCREEN_ACTION_FORCE_REFRESH, display->active_screen);
            epd_wait_flush_complete(pdMS_TO_TICKS(12000));

            suspend_input_manager_task();
#ifdef CONFIG_USE_GT911
            gt911_enter_sleep(gt911_get());
#endif

            xTaskNotifyGive(setup_task_handle[UPDATE_MANAGER_TASK]);
            ESP_LOGI("CONFIG_EXIT", "EXIT");
            break;

        default:
            ESP_LOGW("CONFIG", "Événement inconnu %ld\n", id);
            break;
    }

}

