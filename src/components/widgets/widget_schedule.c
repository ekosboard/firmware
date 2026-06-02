#include "widget_schedule.h"
#include "widget.h"
#include "esp_err.h"
#include "esp_log.h"
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

static const char *TAG = "WIDGET_SCHEDULE";

/**
 * @brief Checks whether `now` falls within the [start, end[ window.
 *
 * Handles two cases:
 *   - Normal window  : start <= end  (e.g. 06:00 → 20:00)
 *   - Midnight wrap  : start >  end  (e.g. 22:00 → 06:00)
 */
static bool time_in_window(uint16_t now, uint16_t start, uint16_t end)
{

    if (start <= end)
    {
        // Cas normal : [start, end[
        return (now >= start && now < end);
    }
    else
    {
        // Fenêtre qui traverse minuit : [start, 1440[ ∪ [0, end[
        return (now >= start || now < end);
    }
}

/**
 * @brief Minutes remaining until `target` is reached from `now`.
 *
 * Handles midnight wraparound: if target < now, counts to end of day
 * then to target.
 */
static uint16_t minutes_until(uint16_t now, uint16_t target)
{
    if (target > now)
        return target - now;
    else
        return (WIDGET_SCHEDULE_MINUTES_DAY - now) + target;
}

uint16_t widget_schedule_minutes_now(void)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) != 0)
    {
        ESP_LOGW(TAG, "gettimeofday failed — returning 0");
        return 0;
    }

    // Epoch 0 signifie que le SNTP n'a pas encore synchronisé
    if (tv.tv_sec < 1000000)
    {
        ESP_LOGW(TAG, "System time not yet synced — returning 0");
        return 0;
    }

    struct tm local_time;
    localtime_r(&tv.tv_sec, &local_time);

    return (uint16_t)(local_time.tm_hour * 60 + local_time.tm_min);
}

bool widget_schedule_is_in_window(const widget_t *widget)
{
    if (widget == NULL)
        return false;

    // Pas de contrainte configurée
    if (widget->update_schedule_end == WIDGET_SCHEDULE_DISABLED)
        return true;

    uint16_t now = widget_schedule_minutes_now();
    return time_in_window(now, widget->update_schedule_start, widget->update_schedule_end);
}

uint64_t widget_schedule_ms_until_next_update(const widget_t *widget, uint64_t current_time_ms)
{
    if (widget == NULL)
        return UINT64_MAX;

    // Calcul du délai purement basé sur l'interval (comportement actuel)
    uint64_t ms_until_interval;
    if (widget->update_data_timestamp == 0)
    {
        ms_until_interval = 0;
    }
    else
    {
        uint64_t elapsed = current_time_ms - widget->update_data_timestamp;
        if (elapsed >= widget->update_data_interval_ms)
            ms_until_interval = 0;
        else
            ms_until_interval = widget->update_data_interval_ms - elapsed;
    }

    // Pas de contrainte horaire → on retourne directement le délai d'interval
    if (widget->update_schedule_end == WIDGET_SCHEDULE_DISABLED)
        return ms_until_interval;

    uint16_t now = widget_schedule_minutes_now();

    // Dans la fenêtre → on respecte l'interval normalement
    if (time_in_window(now, widget->update_schedule_start, widget->update_schedule_end))
        return ms_until_interval;

    // Hors fenêtre → réveil à l'ouverture de la prochaine fenêtre
    uint16_t mins_until_open = minutes_until(now, widget->update_schedule_start);
    uint64_t ms_until_open   = (uint64_t)mins_until_open * 60 * 1000;

    ESP_LOGD(TAG, "Widget hors fenetre — prochaine ouverture dans %u min (%"PRIu64" ms)",
            mins_until_open, ms_until_open);

    return ms_until_open;
}

esp_err_t widget_schedule_parse_time(const char *str, uint16_t *out)
{
    if (!str || !out)
        return ESP_ERR_INVALID_ARG;

    uint16_t hours = 0, minutes = 0;
    if (sscanf(str, "%hu:%hu", &hours, &minutes) != 2)
    {
        ESP_LOGW(TAG, "Failed to parse time string: \"%s\"", str);
        return ESP_ERR_INVALID_ARG;
    }

    if (hours > 23 || minutes > 59)
    {
        ESP_LOGW(TAG, "Time out of range: %02u:%02u", hours, minutes);
        return ESP_ERR_INVALID_ARG;
    }

    *out = hours * 60 + minutes;
    return ESP_OK;
}

void widget_schedule_format_time(uint16_t minutes, char *buf, size_t buf_size)
{
    if (!buf || buf_size < 6)
        return;

    uint16_t h = minutes / 60;
    uint16_t m = minutes % 60;
    snprintf(buf, buf_size, "%02u:%02u", h, m);
}
