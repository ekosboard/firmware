#ifndef WIDGET_SCHEDULE_H
#define WIDGET_SCHEDULE_H

#include "esp_err.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// ─────────────────────────────────────────────────────────────────────────────
//  Sentinel
//  update_schedule_end == WIDGET_SCHEDULE_DISABLED → pas de contrainte horaire
// ─────────────────────────────────────────────────────────────────────────────

#define WIDGET_SCHEDULE_DISABLED    0
#define WIDGET_SCHEDULE_MINUTES_DAY 1440  // 24 * 60

struct widget_s;
typedef struct widget_s widget_t;

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Returns the number of minutes elapsed since midnight (local time).
     *
     * Uses gettimeofday() — reliable after SNTP initialization.
     * Returns 0 if the system time is not yet available.
     */
    uint16_t widget_schedule_minutes_now(void);

    /**
     * @brief Checks whether the widget is allowed to update right now.
     *
     * Returns true if:
     *   - No window is configured (update_schedule_end == WIDGET_SCHEDULE_DISABLED)
     *   - Current time is within [start, end[ (midnight wraparound supported)
     *
     * Does not consider the update interval — only the time window constraint.
     *
     * @param widget Widget to evaluate.
     */
    bool widget_schedule_is_in_window(const widget_t *widget);

    /**
     * @brief Computes the delay in ms before the next allowed update.
     *
     * Combines both the interval constraint and the time window constraint.
     * Returns the greater of the two — ensuring the device does not wake up
     * before the interval expires or outside the scheduled window.
     *
     * Cases covered:
     *   - No window configured → identical to current behavior (interval-based only)
     *   - Inside window, interval expired → 0 (immediate update)
     *   - Inside window, interval not expired → time remaining until interval expires
     *   - Outside window → time until next window opening (midnight wraparound handled)
     *
     * @param widget          Widget to evaluate.
     * @param current_time_ms Current timestamp in ms (esp_timer_get_time() / 1000).
     *
     * @return Delay in ms before the next allowed update.
     */
    uint64_t widget_schedule_ms_until_next_update(const widget_t *widget,
            uint64_t current_time_ms);

    /**
     * @brief Parses a "HH:MM" string into minutes since midnight.
     *
     * @param str  String in "HH:MM" format (e.g. "06:00", "20:30").
     * @param out  Output value in minutes since midnight [0, 1439].
     *
     * @return ESP_OK on success, ESP_ERR_INVALID_ARG on failure.
     */
    esp_err_t widget_schedule_parse_time(const char *str, uint16_t *out);

    /**
     * @brief Formats minutes since midnight into a "HH:MM" string.
     *
     * @param minutes   Minutes since midnight.
     * @param buf       Destination buffer.
     * @param buf_size  Buffer size (minimum 6: "HH:MM\0").
     */
    void widget_schedule_format_time(uint16_t minutes, char *buf, size_t buf_size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* WIDGET_SCHEDULE_H */
