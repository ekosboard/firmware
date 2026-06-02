#include "EPD.h"
#include "UI.h"
#include "display/lv_display.h"
#include "esp_log.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "lv_api_map_v8.h"
#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include "esp_timer.h"
#include "screen_manager.h"
#include "wake_coordinator.h"
#include "widget.h"
#include "widget_schedule.h"

#define MERGE_THRESHOLD_MS 5000  // Regroupe les updates ayant moins de 1s d'écart

static void do_update(widget_t *widget, bool *wifi_required);
static void do_wifi_update(uint64_t current_time, uint32_t *next_update_delay, bool *wifi_required);

/**
 * @brief Task responsible for managing widget updates.
 *
 * This task listens for notifications and updates widgets based on their scheduled
 * update intervals. If multiple widgets have updates scheduled within a short time
 * window, their updates are merged to minimize wake-ups and optimize power consumption.
 *
 * Behavior:
 * - If the elapsed time since the last update exceeds the interval, the widget is updated.
 * - If a widget update is scheduled within `MERGE_THRESHOLD_MS`, it is updated immediately.
 * - Widgets requiring WiFi wait for a connection before updating.
 * - Notifies `power_manager_handle` with the next update delay.
 *
 * @param pvParameters Pointer to the power manager task handle.
 */
void update_manager_task(void *pvParameters)
{
    TaskHandle_t *power_manager_handle = (TaskHandle_t*)pvParameters;
    bool wifi_required_for_update = true;
    bool wifi_required_next_update = false;
    uint32_t next_update_delay = UINT32_MAX;
    uint64_t current_time;
    uint64_t time_until_next_update;
    screen_t *screen = NULL;
    widget_node_t *current = NULL;
    display_t *display = get_main_display();

    while (42)
    {
        if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != 0)
        {
            ESP_LOGI("UPDATE MANAGER", "GET NOTIF");

            next_update_delay = UINT32_MAX;
            current_time = esp_timer_get_time() / 1000;
            screen = get_active_screen();
            current = screen->widget_display_list;

            while (current != NULL)
            {
                widget_t *widget = current->widget;

                bool interval_expired = (widget->update_data_timestamp == 0) ||
                    ((current_time - widget->update_data_timestamp) >= widget->update_data_interval_ms);

                bool first_boot = (widget->update_data_timestamp == 0);

                if (first_boot || (interval_expired && widget_schedule_is_in_window(widget)))
                {
                    // Interval expiré + dans la fenêtre → update normale
                    do_update(widget, &wifi_required_for_update);
                    widget->update_data_timestamp = current_time;
                }

                // Calcul du prochain réveil — délégué à widget_schedule qui combine
                // interval ET contrainte horaire. Toujours calculé, même hors fenêtre,
                // pour que le power_manager se réveille au bon moment.
                time_until_next_update = widget_schedule_ms_until_next_update(widget, current_time);

                ESP_LOGI("UPDATE MANAGER",
                        "Current time: %" PRIu64
                        " | Widget: %s"
                        " | ts: %" PRIu32
                        " | interval: %" PRIu32
                        " | next in: %" PRIu64,
                        current_time,
                        get_widget_type_to_string(widget->type),
                        widget->update_data_timestamp,
                        widget->update_data_interval_ms,
                        time_until_next_update);

                // Merge : uniquement si dans la fenêtre ET pas WIFI_REQUIRED
                if (time_until_next_update < MERGE_THRESHOLD_MS &&
                        !(widget->flag & WIFI_REQUIRED) &&
                        widget_schedule_is_in_window(widget))
                {
                    ESP_LOGI("UPDATE MANAGER", "Merging update for widget scheduled in %" PRIu64 " ms",
                            time_until_next_update);
                    if (lvgl_lock(-1))
                    {
                        widget->update_data_function();
                        lvgl_unlock();
                    }
                    widget->update_data_timestamp = current_time;
                    // Recalcul après merge pour que next_update_delay soit correct
                    time_until_next_update = widget_schedule_ms_until_next_update(widget, current_time);
                }

                if (time_until_next_update < next_update_delay)
                {
                    next_update_delay = (uint32_t)time_until_next_update;
                    wifi_required_next_update = (widget->flag & WIFI_REQUIRED) != 0;
                }

                current = current->next;
            }

            if (wifi_required_for_update)
            {
                do_wifi_update(current_time, &next_update_delay, &wifi_required_for_update);
            }

            if (wifi_required_next_update)
            {
                next_update_delay |= WIFI_REQUIRED;
                wifi_required_next_update = false;
            }

            // Attendre la fin du flush EPD (signalé par disp_flush_monochrome is_last)
            xEventGroupClearBits(get_epd_event_group(), EPD_EVENT_FLUSH_COMPLETE);
            esp_err_t err = epd_wait_flush_complete(pdMS_TO_TICKS(10000));
            if (err != ESP_OK)
            {
                ESP_LOGW("UPDATE MANAGER", "Flush timeout — continuing");
                vTaskDelay(pdMS_TO_TICKS(5000));
            }

            // Full refresh périodique
            if (epd_full_refresh_needed())
            {
                ESP_LOGI("UPDATE MANAGER", "Triggering periodic full refresh");
                notify_screen_manager(SCREEN_ACTION_FORCE_REFRESH, display->active_screen);
                err = epd_wait_flush_complete(pdMS_TO_TICKS(15000));
                if (err != ESP_OK)
                    ESP_LOGE("UPDATE MANAGER", "Full refresh flush timeout");
            }

            display->display_driver->sleep();

            ESP_LOGI("UPDATE MANAGER",
                    "Send notif: %" PRIu32
                    " | wifi asked: %d",
                    next_update_delay & TIMER_MASK,
                    (next_update_delay & WIFI_REQUIRED) != 0);

            wake_coordinator_set(WAKE_SOURCE_UPDATE_MANAGER, next_update_delay);
        }
    }
}

static void do_update(widget_t *widget, bool *wifi_required_for_update)
{
    if (widget->flag & WIFI_REQUIRED)
    {
        *wifi_required_for_update = true;
    }
    else
    {
        if (lvgl_lock(-1))
        {
            widget->update_data_function();
            lvgl_unlock();
        }
    }
}

static void do_wifi_update(uint64_t current_time, uint32_t *next_update_delay, bool *wifi_required_for_update)
{
    widget_node_t *current = NULL;
    EventBits_t wifi_event_bits = xEventGroupWaitBits(
            s_wifi_event_group,
            WIFI_STA_CONNECTED_BIT | WIFI_STA_FAIL_BIT,
            pdFALSE,
            pdFALSE,
            pdMS_TO_TICKS(15000)
            );

    if (wifi_event_bits & WIFI_STA_CONNECTED_BIT)
    {
        current = get_active_screen()->widget_display_list;
        while (current != NULL)
        {
            widget_t *widget = current->widget;
            if ((widget->flag & WIFI_REQUIRED) && widget_schedule_is_in_window(widget))
            {
                if (lvgl_lock(-1))
                {
                    widget->update_data_function();
                    lvgl_unlock();
                }
                widget->update_data_timestamp = current_time;
            }
            current = current->next;
        }
    }
    *wifi_required_for_update = false;
}
