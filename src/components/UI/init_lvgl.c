#include "EPD.h"
#include "UI.h"
#include "core/lv_obj_style.h"
#include "epd_GDEY042T81.h"
/* #include "epd_interface.h" */
#include "display/lv_display.h"
#include "display/lv_display_private.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "misc/lv_area.h"
#include "misc/lv_color.h"
#include "misc/lv_palette.h"
#include "misc/lv_style.h"
#include "misc/lv_style_gen.h"
#include "misc/lv_types.h"
#include "osal/lv_os.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const static char *TAG = "INIT_LVGL";
static SemaphoreHandle_t lvgl_mux = NULL;

static void disp_flush_grayscale(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    static uint8_t dst_buffer[(GDEY042T81_ARRAY * 2)];

    size_t packed_index = 0;
    for (size_t y = 0; y < EPD_HEIGHT; y++) 
    {
        for (size_t x = 0; x < EPD_WIDTH; x += 4)
        {
            unsigned char packed_pixel = 0;
            // Récupérer les 4 pixels et les mettre dans le bon format
            for (int i = 0; i < 4; i++) 
            {
                if (x + i < EPD_WIDTH)
                {
                    uint8_t pixel = px_map[y * EPD_WIDTH + (x + i)];
                    uint8_t grayscale_value = pixel >> 6;
                    packed_pixel |= (grayscale_value << (6 - i * 2)); // Placer les bits
                }
            }
            // Stocker dans le buffer de destination
            dst_buffer[packed_index++] = packed_pixel;
        }
    }

    epd_interface_t *disp_driver = (epd_interface_t*)display->user_data;
    disp_driver->display_image_grayscale(dst_buffer);
    lv_disp_flush_ready(display);
}

static void disp_flush_monochrome(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    static uint8_t i = 0;

    epd_interface_t *disp_driver = (epd_interface_t*)display->user_data;
    if (i++ == 0)
        disp_driver->display_image_partial((px_map + 8), true);
    disp_driver->display_image_partial((px_map + 8), false);
    /* disp_driver->display_image_fast((px_map + 8)); */
    lv_disp_flush_ready(display);
}

static void increase_lvgl_tick(void *arg)
{
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(LVGL_TICK_PERIOD_MS);
}

static void lvgl_port_task(void *arg)
{
    ESP_LOGI(TAG, "Starting LVGL task");
    uint32_t task_delay_ms = LVGL_TASK_MAX_DELAY_MS;
    while (1) {
        // Lock the mutex due to the LVGL APIs are not thread-safe
        if (lvgl_lock(-1)) {
            task_delay_ms = lv_timer_handler();
            // Release the mutex
            lvgl_unlock();
        }
        if (task_delay_ms > LVGL_TASK_MAX_DELAY_MS) {
            task_delay_ms = LVGL_TASK_MAX_DELAY_MS;
        } else if (task_delay_ms < LVGL_TASK_MIN_DELAY_MS) {
            task_delay_ms = LVGL_TASK_MIN_DELAY_MS;
        }
        vTaskDelay(pdMS_TO_TICKS(task_delay_ms));
    }
}

static void init_driver_grayscale(display_t *display)
{
    display->lv_display = lv_display_create(EPD_WIDTH, EPD_HEIGHT);
    display->display_driver = EPD_DRIVER;

    display->display_driver->init();

    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_display_set_resolution(display->lv_display, EPD_WIDTH, EPD_HEIGHT);
    lv_display_set_flush_cb(display->lv_display, disp_flush_grayscale);
    lv_display_set_color_format(display->lv_display, LV_COLOR_FORMAT_L8);
    lv_display_set_user_data(display->lv_display, display->display_driver);

    static uint8_t buf_1[(EPD_WIDTH * EPD_HEIGHT)];
    lv_display_set_buffers(display->lv_display, buf_1, NULL, (EPD_WIDTH * EPD_HEIGHT), LV_DISPLAY_RENDER_MODE_FULL);
}

static void init_driver_monochrome(display_t *display)
{
    display->lv_display = lv_display_create(EPD_WIDTH, EPD_HEIGHT);
    display->display_driver = EPD_DRIVER;

    display->display_driver->init();

    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_display_set_resolution(display->lv_display, EPD_WIDTH, EPD_HEIGHT);
    lv_display_set_flush_cb(display->lv_display, disp_flush_monochrome);
    lv_display_set_color_format(display->lv_display, LV_COLOR_FORMAT_I1);
    lv_display_set_user_data(display->lv_display, display->display_driver);

    static uint8_t buf_1[(EPD_WIDTH * EPD_HEIGHT / 8) + 8];
    lv_display_set_buffers(display->lv_display, buf_1, NULL, (EPD_WIDTH * EPD_HEIGHT / 8) + 8, LV_DISPLAY_RENDER_MODE_DIRECT);
}

/* @Brief Locks access to LVGL to prevent concurrent calls to LVGL functions. */
/* This function attempts to acquire a recursive mutex that ensures only one task can access LVGL at a time. */
/* If the specified timeout is reached before the mutex becomes available, the function will return `false`. */
/* @Parameters: */
/*     - Timeout duration in milliseconds. If set to -1, the function will wait indefinitely */
/*                    until the mutex is available. */
/* @Return: */
/*     - `true` if the mutex was successfully acquired */
/*     - `false` if the timeout was reached. */
bool lvgl_lock(int timeout_ms)
{
    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return xSemaphoreTakeRecursive(lvgl_mux, timeout_ticks) == pdTRUE;
}

/* @Brief Releases the lock on LVGL, allowing other tasks to access LVGL functions. */
/* This function releases the recursive mutex acquired by `lvgl_lock`, enabling other tasks */
/* to proceed with LVGL operations. It should be called after completing a set of LVGL operations */
/*     that were protected by `lvgl_lock`. */
void lvgl_unlock(void)
{
    xSemaphoreGiveRecursive(lvgl_mux);
}

/* Initializes LVGL, sets up the display driver for a monochrome screen, */
/*      and allocates necessary resources such as a tick timer, a mutex, and a dedicated */
/*      task for rendering. */
/* @Parameters: */
/*     - display Pointer to a `display_t` structure containing display parameters */
/*      and the display driver. */
/* @Return: */
/*     - ESP_OK : Initialization successful. */
/*     - ESP_FAIL : Error occurred during timer, mutex, or task configuration. */
esp_err_t  init_lvgl(display_t *display)
{
    esp_err_t err;

    lv_init();
    init_driver_monochrome(display);
    lv_display_set_antialiasing(display->lv_display, true);

    ESP_LOGI(TAG, "Install LVGL tick timer");
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &increase_lvgl_tick,
        .name = "lvgl_tick"
    };
    esp_timer_handle_t lvgl_tick_timer = NULL;

    err = esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer);
    if (err != ESP_OK)
        return ESP_FAIL;

    err = esp_timer_start_periodic(lvgl_tick_timer, LVGL_TICK_PERIOD_MS * 1000);
    if (err != ESP_OK)
        return ESP_FAIL;

    lvgl_mux = xSemaphoreCreateRecursiveMutex();
    if (!lvgl_mux)
        return ESP_FAIL;

    ESP_LOGI(TAG, "Create LVGL task");
    xTaskCreate(lvgl_port_task, "LVGL", LVGL_TASK_STACK_SIZE, NULL, LVGL_TASK_PRIORITY, NULL);

    return ESP_OK;
}
