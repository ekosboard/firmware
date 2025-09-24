#include "HTTP_server.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "freertos/idf_additions.h"
#include "main.h"
#include "state_manager.h"

void state_config_handler(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data)
{
    TaskHandle_t *setup_task_handle = (TaskHandle_t*)handler_arg;

    switch (id)
    {
        case CONFIG_BEGIN:
            xTaskCreate(http_server,
                    "http_server",
                    4096,
                    NULL,
                    4,
                    NULL
                    );

            xTaskNotify(setup_task_handle[SETUP_TIMEOUT_TASK], DEFAULT_TIMEOUT_MS, eSetValueWithOverwrite);
            //FIXME: long timeout ici! maybe infinite!
            break;

        case CONFIG_SAVE:
            break;

        case CONFIG_BEGIN_ISR:
            ESP_LOGI("CONFIG", "ISR");

            ESP_ERROR_CHECK(esp_wifi_start());
            xTaskCreate(http_server,
                    "http_server",
                    4096,
                    NULL,
                    4,
                    NULL
                    );

            xTaskNotify(setup_task_handle[SETUP_TIMEOUT_TASK], DEFAULT_TIMEOUT_MS, eSetValueWithOverwrite);
            break;

        case CONFIG_EXIT:
            if (get_server_handler() != NULL) 
            {
                stop_webserver();
            }

            display_t *display = get_main_display();
            notify_screen_manager(SCREEN_ACTION_DRAW_WITH_DRIVER, display->active_screen);
            xEventGroupWaitBits(get_epd_event_group(),
                    EPD_EVENT_FLUSH_COMPLETE,
                    pdTRUE,
                    pdFALSE,
                    portMAX_DELAY
                    );


            xTaskNotifyGive(setup_task_handle[UPDATE_MANAGER_TASK]);
            break;

        default:
            ESP_LOGW("CONFIG", "Événement inconnu %ld\n", id);
            break;
    }

}

