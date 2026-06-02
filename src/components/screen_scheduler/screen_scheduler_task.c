#include "screen_scheduler_task.h"
#include "EPD.h"
#include "screen_schedule.h"
#include "screen_manager.h"
#include "wake_coordinator.h"
#include "widget_schedule.h"
#include "UI.h"
#include "esp_log.h"
#include "freertos/task.h"

static const char *TAG = "screen_scheduler";

void screen_scheduler_task(void *pvParameters)
{
    TaskHandle_t *update_manager_task_handle = (TaskHandle_t*)pvParameters;

    screen_schedule_load();
    while (42)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        ESP_LOGI(TAG, "wake");

        uint16_t now = widget_schedule_minutes_now();
        if (now == 0)
        {
            // SNTP pas encore sync — on notifie le coordinator avec UINT32_MAX
            // pour ne pas bloquer l'autre source
            ESP_LOGW(TAG, "Time not synced");
            wake_coordinator_set(WAKE_SOURCE_SCREEN_SCHEDULER, UINT32_MAX);
            continue;
        }

        // 1. Trouver le slot actif (screen_id le plus bas = priorité la plus haute)
        screen_t *active_slot = NULL;
        for (int i = 0; i < MAX_SCREEN; i++)
        {
            screen_t *screen = &get_main_display()->screen[i];
            if (screen->schedule_end == SCREEN_SCHEDULE_DISABLED)
                continue;
            if (screen_schedule_is_in_window(screen))
            {
                active_slot = screen;
                break;
            }
        }

        // 2. Switch si nécessaire
        uint8_t current_screen = get_main_display()->active_screen;
        if (active_slot != NULL && active_slot->id != current_screen)
        {
            ESP_LOGI(TAG, "Switching to screen %d", active_slot->id);
            set_active_screen(active_slot->id);

            //FIXME: soucis de basemap autrement ?
            xEventGroupClearBits(get_epd_event_group(), EPD_EVENT_FLUSH_COMPLETE);
            notify_screen_manager(SCREEN_ACTION_DRAW_ONLY, active_slot->id);
            epd_wait_flush_complete(pdMS_TO_TICKS(5000));

            xEventGroupClearBits(get_epd_event_group(), EPD_EVENT_FLUSH_COMPLETE);
            notify_screen_manager(SCREEN_ACTION_FORCE_REFRESH, active_slot->id);
            epd_wait_flush_complete(pdMS_TO_TICKS(12000));

        }

        // 3. Calculer next_wake
        uint32_t next_wake_ms = UINT32_MAX;

        if (active_slot != NULL)
        {
            // Réveil à la fin du slot actif
            next_wake_ms = screen_schedule_ms_until_next_event(active_slot);
        }
        else
        {
            // Trouver le début du prochain slot parmi tous les screens
            for (int i = 0; i < MAX_SCREEN; i++)
            {
                screen_t *screen = &get_main_display()->screen[i];
                if (screen->schedule_end == SCREEN_SCHEDULE_DISABLED)
                    continue;
                uint32_t ms = screen_schedule_ms_until_next_event(screen);
                if (ms < next_wake_ms)
                    next_wake_ms = ms;
            }
        }

        ESP_LOGI(TAG, "Next wake in %" PRIu32 " ms", next_wake_ms);

        // 4. Notifier le wake_coordinator (sans flag WIFI)
        xTaskNotifyGive(*update_manager_task_handle);
        wake_coordinator_set(WAKE_SOURCE_SCREEN_SCHEDULER, next_wake_ms);
    }
}
