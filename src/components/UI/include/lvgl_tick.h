#ifndef LVGL_TICK_H
#define LVGL_TICK_H

#include "esp_err.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Initialize the LVGL tick timer module.
     *
     * Creates the internal esp_timer used to periodically increment the LVGL tick
     * counter via lv_tick_inc(). This function must be called once before using
     * lvgl_tick_start().
     *
     * Calling this function multiple times is safe. If the timer is already created,
     * the function simply returns ESP_OK.
     *
     * @return
     *      - ESP_OK on success
     *      - ESP_FAIL if the timer could not be created
     */
    esp_err_t lvgl_tick_init(void);


    /**
     * @brief Start the LVGL tick timer.
     *
     * Starts the periodic esp_timer responsible for updating the LVGL internal tick.
     * This timer calls lv_tick_inc() at a fixed interval defined by
     * LVGL_TICK_PERIOD_MS.
     *
     * This function is safe to call multiple times. If the timer is already running,
     * it returns ESP_OK without restarting it.
     *
     * Typically called:
     *  - after LVGL initialization
     *  - after exiting light sleep
     *
     * @return
     *      - ESP_OK if the timer is running
     *      - ESP_ERR_INVALID_STATE if the timer was not initialized
     *      - error code returned by esp_timer_start_periodic() otherwise
     */
    esp_err_t lvgl_tick_start(void);


    /**
     * @brief Stop the LVGL tick timer.
     *
     * Stops the periodic esp_timer responsible for updating the LVGL internal tick.
     *
     * This is especially useful before entering light sleep to prevent esp_timer
     * callback backlog accumulation during sleep.
     *
     * This function is safe to call multiple times. If the timer is already stopped,
     * it returns ESP_OK.
     *
     * Typically called:
     *  - before entering light sleep
     *
     * @return
     *      - ESP_OK if the timer is stopped
     *      - ESP_ERR_INVALID_STATE if the timer was not initialized
     *      - error code returned by esp_timer_stop() otherwise
     */
    esp_err_t lvgl_tick_stop(void);


    /**
     * @brief Check whether the LVGL tick timer is currently running.
     *
     * Allows verifying the current state of the LVGL tick timer. Useful for debugging,
     * power management transitions, or conditional timer control.
     *
     * @return
     *      - true if the timer is running
     *      - false otherwise
     */
    bool lvgl_tick_is_running(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
