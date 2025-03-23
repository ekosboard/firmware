#include "EPD.h"
#include "UI.h"
#include "esp_event.h"
#include "esp_log.h"
#include "filesystem_interface.h"
#include "freertos/projdefs.h"
#include "main.h"
#include "portmacro.h"
#include "state_manager.h"
#include "wifi.h"
#include <stdbool.h>

/* This function handles the initialization state of the system.
 * It is triggered by events posted to the state_manager_loop
 * and ensures that all required components (hardware, UI, and network)
 * are properly set up before transitioning to the next phase. */
void state_init_handler(void *handler_arg, esp_event_base_t base, int32_t id, void *event_data)
{
    TaskHandle_t *setup_task_handle = (TaskHandle_t*)handler_arg;
    static bool need_config = false;

    switch (id)
    {
        case INIT_BEGIN:
            esp_event_post_to(state_manager_loop,
                    INIT_EVENT,
                    INIT_SETUP_HW,
                    NULL,
                    0,
                    portMAX_DELAY
                    );
            break;


        case INIT_SETUP_HW:
            if (setup_persistent_state() == ESP_OK)
            {
                esp_event_post_to(state_manager_loop,
                        INIT_EVENT,
                        INIT_SETUP_UI,
                        NULL,
                        0,
                        portMAX_DELAY
                        );
            }
            break;


        case INIT_SETUP_UI:
            if (init_ui() == ESP_OK)
            {
                xEventGroupClearBits(get_epd_event_group(), EPD_EVENT_FLUSH_COMPLETE);
                draw_splash_screen();
                xEventGroupWaitBits(get_epd_event_group(),
                        EPD_EVENT_FLUSH_COMPLETE,
                        pdTRUE,
                        pdFALSE,
                        portMAX_DELAY
                        );

                xTaskNotifyGive(setup_task_handle[SETUP_UI_TASK]);
                esp_event_post_to(state_manager_loop,
                        INIT_EVENT,
                        INIT_SETUP_NET,
                        NULL,
                        0,
                        portMAX_DELAY
                        );
            }
            break;

        case INIT_SETUP_NET:
            //FIXME: gestion erreur
            init_wifi();
            esp_event_post_to(state_manager_loop,
                    INIT_EVENT,
                    INIT_WIFI_CHECK,
                    NULL,
                    0,
                    portMAX_DELAY
                    );
            break;

        case INIT_WIFI_CHECK:
            if (nvs_setup_state_read_network_status() != STA_CONNECTED)
            {
                need_config = true;

                //TODO: make wifi scan (STA mode) before!
                wifi_start_ap();

                esp_event_post_to(state_manager_loop,
                        INIT_EVENT,
                        INIT_END,
                        NULL,
                        0,
                        portMAX_DELAY
                        );
            }
            else
            {
                //TODO: mettre ca dans une/plusieurs task
                wifi_init_sta();
                ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
                esp_wifi_set_ps(WIFI_PS_MIN_MODEM);
                ESP_ERROR_CHECK(esp_wifi_start());
                start_mdns_service();

                EventBits_t wifi_event_bits = xEventGroupWaitBits(s_wifi_event_group,
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

                    xEventGroupWaitBits(get_epd_event_group(),
                            EPD_EVENT_FLUSH_COMPLETE,
                            pdTRUE,
                            pdFALSE,
                            portMAX_DELAY
                            );
                    vTaskDelay(pdMS_TO_TICKS(1000)); //FIXME: temporaire

                    esp_event_post_to(state_manager_loop,
                            INIT_EVENT,
                            INIT_END,
                            NULL,
                            0, portMAX_DELAY
                            );
                }
                else if (wifi_event_bits & WIFI_STA_FAIL_BIT)
                {
                    //display message d'erreur
                    //Comment gerer le manque de connection ?
                    ESP_LOGW("INIT_WIFI_CHECK", "STA FAIL");
                }
            }
            break;

        case INIT_END:
            if (need_config)
            {
                esp_event_post_to(state_manager_loop,
                        CONFIG_EVENT,
                        CONFIG_BEGIN,
                        NULL,
                        0,
                        portMAX_DELAY
                        );
            }
            else 
            {
                esp_event_post_to(state_manager_loop,
                        CONFIG_EVENT,
                        CONFIG_EXIT,
                        NULL,
                        0,
                        portMAX_DELAY
                        );
            }
            break;

        default:
            ESP_LOGW("INIT", "Événement inconnu %ld", id);
            break;
    }
}
