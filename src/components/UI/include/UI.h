#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "epd_interface.h"
#include "filesystem_interface.h"
#include "freertos/FreeRTOS.h"
#include "freertos/idf_additions.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "hal/spi_types.h"
#include "esp_err.h"
#include "lvgl.h"
#include "misc/lv_color.h"
#include "misc/lv_types.h"

#include "widget.h"
#include "font.h"

#define LVGL_TICK_PERIOD_MS     1
#define LVGL_TASK_MAX_DELAY_MS  150
#define LVGL_TASK_MIN_DELAY_MS  1
#define LVGL_TASK_STACK_SIZE    (16 * 1024)
#define LVGL_TASK_PRIORITY      10

#define MAX_SCREEN              3 //CONFIG_DISPLAY_SCREEN
#define LAYOUT_TYPE             3 //config un enum pour representer un layout

#define WIDGET_INDEX_PATH_BASE  "widget_index_screen_"
#define WIDGET_INDEX_PATH_EXT   ".json"
#define WIDGET_INDEX_PATH_LEN   30

#define FULL_REFRESH_EVERY      50

typedef struct screen_s {
    uint8_t             id;
    lv_obj_t            *lv_screen;
    widget_container_t  containers[LAYOUT_TYPE];
    widget_node_t       *widget_display_list;
} screen_t;

typedef struct display_s {
    lv_display_t        *lv_display;
    epd_interface_t     *display_driver;
    screen_t            screen[MAX_SCREEN];
    uint8_t             active_screen;
    const widget_t      *widget_info_list;
} display_t;


#ifdef __cplusplus
extern "C" {
#endif

    ////////////////////////////////////////////////////////////////////////////////
    //  EPD MAIN
    ////////////////////////////////////////////////////////////////////////////////
    esp_err_t       init_ui(void);
    esp_err_t       init_lvgl(display_t *display);
    bool            lvgl_lock(int timeout_ms);
    void            lvgl_unlock(void);
    void            lvgl_clear_screen(screen_t *screen, void (*clear)(void));
    void            lvgl_draw_screen(screen_t *screen, void (*clear)(void));
    void            lvgl_switch_screen(screen_t *screen, void (*clear)(void));
    void            lvgl_force_refresh_screen(screen_t *screen, void (*clear)(void));

    display_t       *get_main_display(void);
    screen_t        *get_active_screen(void);
    esp_err_t       set_active_screen(uint8_t screen_id);

    /* Waits for the e-paper display to complete its flush cycle.
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
     */
    esp_err_t epd_wait_flush_complete(TickType_t timeout_ticks);

    uint8_t     *epd_get_basemap(void);

    ////////////////////////////////////////////////////////////////////////////////
    //  DRAW
    ////////////////////////////////////////////////////////////////////////////////
    void            fullscreen_qrcode(const char *data);
    void            btn_bottom_left(const char *label);
    void            btn_bottom_right(const char *label);

    ////////////////////////////////////////////////////////////////////////////////
    //  DRAW/SCREEN
    ////////////////////////////////////////////////////////////////////////////////
    void            draw_screen_wifi_config(const char *data);
    void            draw_screen_wifi_success(const char *data);
    void            draw_splash_screen(void);
    void            splash_screen_set_wifi_state(const char *ssid);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
