#ifndef EPD_H
#define EPD_H

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "hal/spi_types.h"
#include "esp_err.h"
#include "lvgl.h"
#include "misc/lv_color.h"


#define LVGL_TICK_PERIOD_MS    2
#define LVGL_TASK_MAX_DELAY_MS 150
#define LVGL_TASK_MIN_DELAY_MS 1
#define LVGL_TASK_STACK_SIZE   (4 * 1024)
#define LVGL_TASK_PRIORITY     10

#ifdef CONFIG_EPD_GDEY042T81
    #include "epd_GDEY042T81.h"
    #define EPD_DRIVER  (&gdey042t81_driver)
    #define EPD_WIDTH   GDEY042T81_WIDTH
    #define EPD_HEIGHT  GDEY042T81_HEIGHT
    #define EPD_ARRAY   GDEY042T81_ARRAY
#endif



#ifdef __cplusplus
extern "C" {
#endif

    ////////////////////////////////////////////////////////////////////////////////
    //  EPD MAIN
    ////////////////////////////////////////////////////////////////////////////////
    lv_display_t    *init_display(void);
    bool            lvgl_lock(int timeout_ms);
    void            lvgl_unlock(void);


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

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
