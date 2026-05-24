#ifndef EPD_H
#define EPD_H

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/idf_additions.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "hal/spi_types.h"
#include "esp_err.h"


// ─────────────────────────────────────────────────────────────────────────────
//  Event bits
// ─────────────────────────────────────────────────────────────────────────────

#define EPD_EVENT_FLUSH_COMPLETE   BIT0

// ─────────────────────────────────────────────────────────────────────────────
//  Driver selection (Kconfig)
// ─────────────────────────────────────────────────────────────────────────────

#ifdef CONFIG_EPD_GDEY042T81
#include "epd_GDEY042T81.h"
#define EPD_DRIVER  (&gdey042t81_driver)
#define EPD_WIDTH   GDEY042T81_WIDTH
#define EPD_HEIGHT  GDEY042T81_HEIGHT
#define EPD_ARRAY   GDEY042T81_ARRAY
#endif

#ifdef CONFIG_EPD_GDEY075T7
#include "epd_GDEY075T7.h"
#define EPD_DRIVER  (&gdey075t7_driver)
#define EPD_WIDTH   GDEY075T7_WIDTH
#define EPD_HEIGHT  GDEY075T7_HEIGHT
#define EPD_ARRAY   GDEY075T7_ARRAY
#endif

// ─────────────────────────────────────────────────────────────────────────────
//  Full refresh periodicity
//  Déclenchement d'un full refresh toutes les N mises à jour partielles.
//  Géré par epd_full_refresh_needed(), consommé par update_manager_task.
// ─────────────────────────────────────────────────────────────────────────────

#define FULL_REFRESH_EVERY  50

#ifdef __cplusplus
extern "C" {
#endif

    // ─────────────────────────────────────────────────────────────────────────────
    //  Event group
    // ─────────────────────────────────────────────────────────────────────────────

    /**
     * @brief Initializes the event group used for EPD events.
     * @details
     * - Creates an event group to manage synchronization for EPD-related tasks.
     * - Must be called before using any other functions related to this event group.
     */
    void               init_epd_event_group(void);

    /**
     * @brief Sets specific bits in the EPD event group.
     * @param bits The event bits to be set.
     * @details
     * - Updates the event group to signal the occurrence of a specific event.
     * - This function can be used to notify waiting tasks that an event has occurred.
     * @note The bits set here may need to be cleared elsewhere depending on usage.
     */
    void               set_epd_event(uint32_t bits);

    /**
     * @brief Retrieves the event group handle for EPD events.
     * @return The handle to the EPD event group.
     * @note Ensure that `init_epd_event_group` has been called before using this function.
     */
    EventGroupHandle_t get_epd_event_group(void);

    // ─────────────────────────────────────────────────────────────────────────────
    //  Synchronisation flush
    // ─────────────────────────────────────────────────────────────────────────────

    /** Waits for the e-paper display to complete its flush cycle.
     * @Parameters:
     *   - timeout_ticks: Maximum number of FreeRTOS ticks to wait before timing out.
     * @Return:
     *   - ESP_OK: Flush cycle completed successfully.
     *   - ESP_ERR_TIMEOUT: The operation timed out before the flush cycle finished.
     * @Details:
     *   This function first waits until LVGL confirms that the last display flush
     *   operation has been issued. It then waits for the e-paper driver to signal
     *   that the flush is physically complete using the EPD_EVENT_FLUSH_COMPLETE
     *   event. Useful to synchronize application logic with the actual refresh
     *   state of the e-paper display and avoid screen tearing or premature
     *   power-down.
     **/
    esp_err_t epd_wait_flush_complete(TickType_t timeout_ticks);

    // ─────────────────────────────────────────────────────────────────────────────
    //  Full refresh périodique
    // ─────────────────────────────────────────────────────────────────────────────

    /**
     * @brief Incrémente le compteur de flush et indique si un full refresh
     *        doit être déclenché ce cycle.
     *
     * Appelé par update_manager_task après chaque flush complet.
     * Réinitialise le compteur automatiquement quand FULL_REFRESH_EVERY est atteint.
     *
     * @return true  si un full refresh doit être déclenché.
     * @return false si un refresh partiel normal suffit.
     */
    bool epd_full_refresh_needed(void);

    /**
     * @brief Réinitialise le compteur de full refresh.
     *
     * À appeler si un clear manuel est déclenché (ex: depuis l'API REST),
     * pour éviter un double full refresh inutile.
     */
    void epd_reset_refresh_counter(void);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
