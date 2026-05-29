#include "wake_coordinator.h"
#include "esp_log.h"
#include "widget.h"

static const char *TAG = "wake_coordinator";

static TaskHandle_t     *s_power_manager_handle = NULL;
static uint32_t          s_delays[WAKE_SOURCE_COUNT];
static bool              s_ready[WAKE_SOURCE_COUNT];
static SemaphoreHandle_t s_mutex = NULL;

void wake_coordinator_init(TaskHandle_t *power_manager_handle)
{
    s_power_manager_handle = power_manager_handle;
    s_mutex = xSemaphoreCreateMutex();

    for (int i = 0; i < WAKE_SOURCE_COUNT; i++)
    {
        s_delays[i] = UINT32_MAX;
        s_ready[i]  = false;
    }
}

void wake_coordinator_set(wake_source_t source, uint32_t delay_ms)
{
    ESP_LOGI(TAG, "wake_source: %d", source);

    xSemaphoreTake(s_mutex, portMAX_DELAY);

    s_delays[source] = delay_ms;
    s_ready[source]  = true;

    bool all_ready = true;
    for (int i = 0; i < WAKE_SOURCE_COUNT; i++)
    {
        if (!s_ready[i])
        {
            all_ready = false;
            break;
        }
    }

    if (all_ready)
    {
        uint32_t wifi_flag = s_delays[WAKE_SOURCE_UPDATE_MANAGER] & WIFI_REQUIRED;
        uint32_t um_delay  = s_delays[WAKE_SOURCE_UPDATE_MANAGER] & TIMER_MASK;
        uint32_t ss_delay  = s_delays[WAKE_SOURCE_SCREEN_SCHEDULER] & TIMER_MASK;

        uint32_t min_delay    = (um_delay < ss_delay) ? um_delay : ss_delay;
        uint32_t notify_value = min_delay | wifi_flag;

        ESP_LOGI(TAG, "um: %" PRIu32 " | ss: %" PRIu32 " | min: %" PRIu32 " | wifi: %d",
                um_delay, ss_delay, min_delay, wifi_flag != 0);

        for (int i = 0; i < WAKE_SOURCE_COUNT; i++)
        {
            s_delays[i] = UINT32_MAX;
            s_ready[i]  = false;
        }

        xSemaphoreGive(s_mutex);
        xTaskNotify(*s_power_manager_handle, notify_value, eSetValueWithOverwrite);
        return;
    }

    xSemaphoreGive(s_mutex);
}
