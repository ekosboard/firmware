#include "lvgl_tick.h"

#include "UI.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"

#ifndef LVGL_TICK_PERIOD_MS
#error "LVGL_TICK_PERIOD_MS must be defined"
#endif

static const char *TAG = "LVGL_TICK";
static esp_timer_handle_t lvgl_tick_timer = NULL;

static void increase_lvgl_tick(void *arg)
{
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(LVGL_TICK_PERIOD_MS);
}

esp_err_t lvgl_tick_init(void)
{
    if (lvgl_tick_timer != NULL)
    {
        return ESP_OK;
    }

    const esp_timer_create_args_t timer_args = {
        .callback = &increase_lvgl_tick,
        .name = "lvgl_tick"
    };

    esp_err_t err = esp_timer_create(&timer_args, &lvgl_tick_timer);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to create LVGL tick timer");
        return err;
    }

    return ESP_OK;
}

esp_err_t lvgl_tick_start(void)
{
    if (!lvgl_tick_timer)
        return ESP_FAIL;

    if (esp_timer_is_active(lvgl_tick_timer))
        return ESP_OK;

    return esp_timer_start_periodic(lvgl_tick_timer,LVGL_TICK_PERIOD_MS);
}

esp_err_t lvgl_tick_stop(void)
{
    if (!lvgl_tick_timer)
        return ESP_FAIL;

    if (!esp_timer_is_active(lvgl_tick_timer))
        return ESP_OK;

    return esp_timer_stop(lvgl_tick_timer);
}

bool lvgl_tick_is_running(void)
{
    return esp_timer_is_active(lvgl_tick_timer);
}
