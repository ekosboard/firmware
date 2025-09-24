#include "esp_log.h"
#include "main.h"
#include "state_manager.h"

void state_idle_handler(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data)
{
    TaskHandle_t *setup_task_handle = (TaskHandle_t*)handler_arg;

    switch (id)
    {
        case IDLE_ENTER:
            ESP_LOGI("IDLE: start lightsleep", "");
            break;

        case IDLE_WIFI_START:
            break;

        case IDLE_WIFI_STOP:
            break;

        case IDLE_EXIT:
            ESP_LOGI("IDLE: wakeup", "");
            break;

        case IDLE_WAKEUP:
            break;

        default:
            ESP_LOGW("IDLE", "Événement inconnu %ld\n", id);
            break;
    }
}
