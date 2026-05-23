#include "EPD.h"
#include "HTTP_server.h"
#include "UI.h"
#include "esp_err.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_wifi_types_generic.h"
#include "filesystem_interface.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "input_manager.h"
#include "main.h"
#include "ota_context.h"
#include "portmacro.h"
#include "state_manager.h"
#include "wifi.h"
#include <stdbool.h>
#include "setup_i2c_bus.h"
#include "screen_manager.h"
#include "wifi_switch.h"

#ifdef CONFIG_USE_GT911
#include "gt911.h"
#endif

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
                    portMAX_DELAY);

            ota_context_init();
            break;


        case INIT_SETUP_HW:
            if (setup_persistent_state() == ESP_OK)
            {
#ifdef CONFIG_USE_GT911
                gpio_install_isr_service(0);
                if (setup_i2c_bus() == ESP_OK && gt911_init(get_i2c_bus()) == ESP_OK)
#endif
                    esp_event_post_to(state_manager_loop,
                            INIT_EVENT,
                            INIT_SETUP_UI,
                            NULL,
                        0,
                        portMAX_DELAY);
            }
            break;


        case INIT_SETUP_UI:
            ESP_LOGI("INIT_SETUP_UI", "");
            if (init_ui() == ESP_OK)
            {
                draw_splash_screen();
                epd_wait_flush_complete(pdMS_TO_TICKS(10000));
                xTaskNotifyGive(setup_task_handle[SETUP_UI_TASK]);
                esp_event_post_to(state_manager_loop,
                        INIT_EVENT,
                        INIT_SETUP_NET,
                        NULL,
                        0,
                        portMAX_DELAY);
            }
            break;

        case INIT_SETUP_NET:
            //FIXME: gestion erreur
            init_input_manager_task();
            init_wifi();

            if (init_wifi_switch_queue() != ESP_OK)
            {
                ESP_LOGE("INIT_SETUP_NET", "init_wifi_switch_queue failed!");
            }

            if (init_widget_update_queue() != ESP_OK)
            {
                ESP_LOGE("INIT_SETUP_NET", "init_widget_update_queue failed!");
            }

            esp_event_post_to(state_manager_loop,
                    INIT_EVENT,
                    INIT_WIFI_CHECK,
                    NULL,
                    0,
                    portMAX_DELAY);
            break;

        case INIT_WIFI_CHECK:
            if (nvs_setup_state_read_network_status() != STA_CONNECTED)
            {
                ESP_LOGI("INIT_WIFI_CHECK", "STA_CONNECTED = NOT!");
                need_config = true;
                wifi_start_ap();
                esp_event_post_to(state_manager_loop,
                        INIT_EVENT,
                        INIT_END,
                        NULL,
                        0,
                        portMAX_DELAY);
            }
            else
            {
                ESP_LOGI("INIT_WIFI_CHECK", "STA_CONNECTED = OK");
                //TODO: mettre ca dans une/plusieurs task
                wifi_init_sta();
                ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
                esp_wifi_set_ps(WIFI_PS_MIN_MODEM);
                ESP_ERROR_CHECK(esp_wifi_start());
                start_mdns_service();

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
                            splash_screen_set_wifi_state((char*)ap_info.ssid);
                        }
                        lvgl_unlock();
                    }


                    epd_wait_flush_complete(pdMS_TO_TICKS(10000));
                    esp_event_post_to(state_manager_loop,
                            INIT_EVENT,
                            INIT_END,
                            NULL,
                            0, portMAX_DELAY);
                }
                else if (wifi_event_bits & WIFI_STA_FAIL_BIT)
                {
                    //display message d'erreur
                    //Comment gerer le manque de connection ?
                    display_t *display = get_main_display();
                    notify_screen_manager(SCREEN_ACTION_CLEAR_WITH_DRIVER, display->active_screen);
                    ESP_LOGW("INIT_WIFI_CHECK", "STA FAIL");
                }
            }
            break;

        case INIT_END:
            if (need_config)
            {
                ESP_LOGI("INIT_END", "Need config = yes");
                esp_event_post_to(state_manager_loop,
                        CONFIG_EVENT,
                        CONFIG_BEGIN,
                        NULL,
                        0,
                        portMAX_DELAY);
            }
            else 
            {
                ESP_LOGI("INIT_END", "Need config = no");
                esp_event_post_to(state_manager_loop,
                        CONFIG_EVENT,
                        CONFIG_EXIT,
                        NULL,
                        0,
                        portMAX_DELAY);
            }
            break;

        default:
            ESP_LOGW("INIT", "Événement inconnu %ld", id);
            break;
    }
}
