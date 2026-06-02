#include "screen_schedule.h"
#include "UI.h"
#include "widget_schedule.h"
#include "filesystem_interface.h"
#include "cJSON.h"
#include "esp_log.h"

static const char *TAG = "screen_schedule";

#define SCHEDULE_PATH LFS_BASE_PATH "/screens_schedule.json" // /littlefs/screens_schedule.json

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

bool screen_schedule_is_in_window(const screen_t *screen)
{
    if (screen == NULL)
        return false;

    if (screen->schedule_end == SCREEN_SCHEDULE_DISABLED)
        return false;

    uint16_t now = widget_schedule_minutes_now();
    return time_in_window(now, screen->schedule_start, screen->schedule_end);
}

uint32_t screen_schedule_ms_until_next_event(const screen_t *screen)
{
    if (screen == NULL || screen->schedule_end == SCREEN_SCHEDULE_DISABLED)
        return UINT32_MAX;

    uint16_t now = widget_schedule_minutes_now();

    if (time_in_window(now, screen->schedule_start, screen->schedule_end))
        return (uint32_t)minutes_until(now, screen->schedule_end) * 60 * 1000;
    else
        return (uint32_t)minutes_until(now, screen->schedule_start) * 60 * 1000;
}

esp_err_t screen_schedule_load(void)
{
    esp_err_t err = mount_lfs();
    if (err != ESP_OK)
        return err;

    cJSON *array = NULL;
    array = read_json_file(SCHEDULE_PATH, READ_LFS);
    if (array == NULL)
    {
        ESP_LOGW(TAG, "No schedule.json found, skipping");
        unmount_lfs();
        return ESP_OK;
    }

    unmount_lfs();

    cJSON *item = NULL;
    cJSON_ArrayForEach(item, array)
    {
        cJSON *id_json = cJSON_GetObjectItem(item, "screen_id");
        cJSON *start_json = cJSON_GetObjectItem(item, "start");
        cJSON *end_json = cJSON_GetObjectItem(item, "end");

        if (!cJSON_IsNumber(id_json) || !cJSON_IsString(start_json) || !cJSON_IsString(end_json))
        {
            ESP_LOGW(TAG, "Invalid schedule entry, skipping");
            continue;
        }

        uint8_t screen_id = (uint8_t)id_json->valueint;
        if (screen_id >= MAX_SCREEN)
        {
            ESP_LOGW(TAG, "screen_id %d out of range, skipping", screen_id);
            continue;
        }

        screen_t *screen = &get_main_display()->screen[screen_id];

        uint16_t start, end;
        if (widget_schedule_parse_time(start_json->valuestring, &start) != ESP_OK ||
                widget_schedule_parse_time(end_json->valuestring,   &end)   != ESP_OK)
        {
            ESP_LOGW(TAG, "Failed to parse time for screen %d, skipping", screen_id);
            continue;
        }

        screen->schedule_start = start;
        screen->schedule_end = end;
        ESP_LOGI(TAG, "Screen %d schedule loaded: %s → %s",
                screen_id, start_json->valuestring, end_json->valuestring);
    }

    cJSON_Delete(array);
    return ESP_OK;
}

esp_err_t screen_schedule_save(void)
{
    cJSON *array = cJSON_CreateArray();
    if (array == NULL)
        return ESP_FAIL;

    for (int i = 0; i < MAX_SCREEN; i++)
    {
        screen_t *screen = &get_main_display()->screen[i];
        if (screen->schedule_end == SCREEN_SCHEDULE_DISABLED)
            continue;

        cJSON *item = cJSON_CreateObject();
        cJSON_AddNumberToObject(item, "screen_id", i);

        char start_str[6], end_str[6];
        widget_schedule_format_time(screen->schedule_start, start_str, sizeof(start_str));
        widget_schedule_format_time(screen->schedule_end,   end_str,   sizeof(end_str));

        cJSON_AddStringToObject(item, "start", start_str);
        cJSON_AddStringToObject(item, "end",   end_str);
        cJSON_AddItemToArray(array, item);
    }

    char *buf = cJSON_Print(array);
    cJSON_Delete(array);
    if (buf == NULL)
        return ESP_FAIL;

    esp_err_t err = mount_lfs();
    if (err != ESP_OK)
    {
        free(buf);
        return err;
    }

    err = write_file_lfs(SCHEDULE_PATH, buf);
    free(buf);
    unmount_lfs();

    return err;
}
