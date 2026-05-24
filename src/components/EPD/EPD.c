#include "EPD.h"
#include "esp_log.h"
#include "freertos/idf_additions.h"

static const char *TAG = "EPD";

static EventGroupHandle_t epd_event_group;
static uint8_t s_refresh_count = 0;

// ─────────────────────────────────────────────────────────────────────────────
//  Event group
// ─────────────────────────────────────────────────────────────────────────────

void init_epd_event_group(void)
{
    epd_event_group = xEventGroupCreate();
}

EventGroupHandle_t get_epd_event_group(void)
{
    return epd_event_group;
}

void set_epd_event(uint32_t bits)
{
    xEventGroupSetBits(epd_event_group, bits);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Synchronisation flush
// ─────────────────────────────────────────────────────────────────────────────

esp_err_t epd_wait_flush_complete(TickType_t timeout_ticks)
{
    EventBits_t bits = xEventGroupWaitBits(
            epd_event_group,
            EPD_EVENT_FLUSH_COMPLETE,
            pdTRUE,   // clear on exit
            pdTRUE,
            timeout_ticks);

    // Délai de garde — laisse le temps à l'EPD de terminer physiquement
    // son cycle de refresh après que LVGL a signalé la fin du flush.
    vTaskDelay(pdMS_TO_TICKS(1000));

    if (bits & EPD_EVENT_FLUSH_COMPLETE)
    {
        ESP_LOGD(TAG, "epd_wait_flush_complete: OK");
        return ESP_OK;
    }

    ESP_LOGW(TAG, "epd_wait_flush_complete: TIMEOUT");
    return ESP_ERR_TIMEOUT;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Full refresh périodique
// ─────────────────────────────────────────────────────────────────────────────

bool epd_full_refresh_needed(void)
{
    s_refresh_count++;
    if (s_refresh_count >= FULL_REFRESH_EVERY)
    {
        s_refresh_count = 0;
        ESP_LOGI(TAG, "Full refresh triggered (every %d flushes)", FULL_REFRESH_EVERY);
        return true;
    }
    return false;
}

void epd_reset_refresh_counter(void)
{
    s_refresh_count = 0;
    ESP_LOGD(TAG, "Refresh counter reset");
}
