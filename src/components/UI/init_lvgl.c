#include "EPD.h"
#include "UI.h"
#include "display/lv_display.h"
#include "display/lv_display_private.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "lvgl_tick.h"
#include "misc/lv_area.h"
#include "misc/lv_color.h"
#include "misc/lv_types.h"
#include "portmacro.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef CONFIG_USE_GT911
#include "gt911.h"
#endif

const static char *TAG = "INIT_LVGL";
static SemaphoreHandle_t lvgl_mux = NULL;
EXT_RAM_BSS_ATTR static uint8_t epd_basemap[EPD_WIDTH * EPD_HEIGHT / 8 + 8];

uint8_t *epd_get_basemap(void)
{
    return epd_basemap;
}

static void disp_flush_grayscale(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    EXT_RAM_BSS_ATTR static uint8_t dst_buffer[(GDEY075T7_ARRAY * 2)];

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
    epd_interface_t *disp_driver = (epd_interface_t*)display->user_data;
    static uint8_t first_refresh = 0;
    const uint8_t *fb = px_map + 8;  // skip header LVGL

    uint32_t x = area->x1;
    uint32_t y = area->y1;
    uint32_t w = area->x2 - area->x1 + 1;
    uint32_t h = area->y2 - area->y1 + 1;

    bool is_last = lv_display_flush_is_last(display); // capture AVANT lv_disp_flush_ready


    if (first_refresh == 0)
    {
        ESP_LOGW(TAG, "disp_flush_monochrome FIRST RENDER");
        disp_driver->clear();
        first_refresh++;
    }

    disp_driver->display_image_area(fb, x, y, w, h);
    lv_disp_flush_ready(display);

    if (is_last)
    {
        memcpy(epd_basemap, px_map, EPD_WIDTH * EPD_HEIGHT / 8 + 8);
        set_epd_event(EPD_EVENT_FLUSH_COMPLETE);
        ESP_LOGW(TAG, "disp_flush_monochrome LAST FLUSH");
    }
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

    EXT_RAM_BSS_ATTR static uint8_t buf_1[(EPD_WIDTH * EPD_HEIGHT)];
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

    EXT_RAM_BSS_ATTR static uint8_t buf_1[(EPD_WIDTH * EPD_HEIGHT / 8) + 8];
    lv_display_set_buffers(display->lv_display, buf_1, NULL, (EPD_WIDTH * EPD_HEIGHT / 8) + 8, LV_DISPLAY_RENDER_MODE_DIRECT);
    /* lv_display_set_buffers(display->lv_display, buf_1, NULL, (EPD_WIDTH * EPD_HEIGHT / 8) + 8, LV_DISPLAY_RENDER_MODE_FULL); */
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


#ifdef CONFIG_USE_GT911
static void gt911_lvgl_read_cb(lv_indev_t *indev, lv_indev_data_t *data)
{
    gt911_t *gt911 = gt911_get();

    portENTER_CRITICAL(&gt911->lock);
    uint8_t points = gt911->data.points;
    uint16_t x = gt911->data.coords[0].x;
    uint16_t y = gt911->data.coords[0].y;
    gt911->data.points = 0;
    portEXIT_CRITICAL(&gt911->lock);

    if (points > 0)
    {
        data->state = LV_INDEV_STATE_PRESSED;
        data->point.x = x;
        data->point.y = y;
        ESP_LOGI("LVGL", "Touch: %d point(s) at X=%d, Y=%d", points, x, y);
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void lv_port_indev_init(void)
{
    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, gt911_lvgl_read_cb);
}
#endif

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
    /* init_driver_grayscale(display); */
    lv_display_set_antialiasing(display->lv_display, false);
#ifdef CONFIG_USE_GT911
    lv_port_indev_init();
#endif


    ESP_LOGI(TAG, "Install LVGL tick timer");
    ESP_ERROR_CHECK(lvgl_tick_init());

    err = lvgl_tick_start();
    if (err != ESP_OK)
        return ESP_FAIL;

    lvgl_mux = xSemaphoreCreateRecursiveMutex();
    if (!lvgl_mux)
        return ESP_FAIL;

    ESP_LOGI(TAG, "Create LVGL task");
    xTaskCreate(lvgl_port_task, "LVGL", LVGL_TASK_STACK_SIZE, NULL, LVGL_TASK_PRIORITY, NULL);

    return ESP_OK;
}
