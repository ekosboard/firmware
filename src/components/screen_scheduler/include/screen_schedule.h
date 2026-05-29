#ifndef SCREEN_SCHEDULE_H
#define SCREEN_SCHEDULE_H

#include "esp_err.h"
#include <stdbool.h>
#include <stdint.h>

#define SCREEN_SCHEDULE_DISABLED    0
#define SCREEN_SCHEDULE_MINUTES_DAY 1440

struct screen_s;
typedef struct screen_s screen_t;

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Checks whether the screen has an active schedule slot right now.
     *
     * Returns true if:
     *   - No window is configured (schedule_end == SCREEN_SCHEDULE_DISABLED)
     *   - Current time is within [start, end[ (midnight wraparound supported)
     *
     * @param screen Screen to evaluate.
     */
    bool screen_schedule_is_in_window(const screen_t *screen);

    /**
     * @brief Computes the delay in ms until the next screen switch event.
     *
     * @param screen          Screen to evaluate.
     * @return Delay in ms, or UINT32_MAX if no schedule configured.
     */
    uint32_t screen_schedule_ms_until_next_event(const screen_t *screen);

    /**
     * @brief Loads schedule.json from LittleFS and populates schedule_start/end
     *        fields in the main display's screen array.
     *
     * @return ESP_OK on success.
     */
    esp_err_t screen_schedule_load(void);

    /**
     * @brief Saves current schedule to schedule.json on LittleFS.
     *
     * @return ESP_OK on success.
     */
    esp_err_t screen_schedule_save(void);

#ifdef __cplusplus
}
#endif

#endif /* SCREEN_SCHEDULE_H */
