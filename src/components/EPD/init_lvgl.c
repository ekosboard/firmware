#include "EPD.h"
#include "core/lv_obj_style.h"
#include "epd_GDEY042T81.h"
#include "epd_interface.h"
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
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const static char *TAG = "INIT_LVGL";
static SemaphoreHandle_t lvgl_mux = NULL;

void disp_flush_grayscale(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
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

void disp_flush_monochrome(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    static uint8_t i = 0;

    epd_interface_t *disp_driver = (epd_interface_t*)display->user_data;
    if (i++ == 0)
        disp_driver->display_image_partial((px_map + 8), true);
    disp_driver->display_image_partial((px_map + 8), false);
    lv_disp_flush_ready(display);
}

static void increase_lvgl_tick(void *arg)
{
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(LVGL_TICK_PERIOD_MS);
}

bool lvgl_lock(int timeout_ms)
{
    // Convert timeout in milliseconds to FreeRTOS ticks
    // If `timeout_ms` is set to -1, the program will block until the condition is met
    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return xSemaphoreTakeRecursive(lvgl_mux, timeout_ticks) == pdTRUE;
}

void lvgl_unlock(void)
{
    xSemaphoreGiveRecursive(lvgl_mux);
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

lv_display_t *init_driver_grayscale(void)
{
    lv_display_t *disp = lv_display_create(EPD_WIDTH, EPD_HEIGHT);
    epd_interface_t *disp_driver = EPD_DRIVER;

    disp_driver->init();

    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_display_set_resolution(disp, EPD_WIDTH, EPD_HEIGHT);
    lv_display_set_flush_cb(disp, disp_flush_grayscale);
    lv_display_set_color_format(disp, LV_COLOR_FORMAT_L8);
    lv_display_set_user_data(disp, disp_driver);

    static uint8_t buf_1[(EPD_WIDTH * EPD_HEIGHT)];
    lv_display_set_buffers(disp, buf_1, NULL, (EPD_WIDTH * EPD_HEIGHT), LV_DISPLAY_RENDER_MODE_FULL);

    return disp;
}

lv_display_t *init_driver_monochrome(void)
{
    lv_display_t *disp = lv_display_create(EPD_WIDTH, EPD_HEIGHT);
    epd_interface_t *disp_driver = EPD_DRIVER;

    disp_driver->init();

    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_display_set_resolution(disp, EPD_WIDTH, EPD_HEIGHT);
    lv_display_set_flush_cb(disp, disp_flush_monochrome);
    lv_display_set_color_format(disp, LV_COLOR_FORMAT_I1);
    lv_display_set_user_data(disp, disp_driver);

    static uint8_t buf_1[(EPD_WIDTH * EPD_HEIGHT / 8) + 8];
    lv_display_set_buffers(disp, buf_1, NULL, (EPD_WIDTH * EPD_HEIGHT / 8) + 8, LV_DISPLAY_RENDER_MODE_DIRECT);

    return disp;
}

lv_display_t  *init_display(void)
{
    lv_init();
    lv_display_t *disp = init_driver_monochrome();
    lv_display_set_antialiasing(disp, true);

    ESP_LOGI(TAG, "Install LVGL tick timer");
    // Tick interface for LVGL (using esp_timer to generate 2ms periodic event)
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &increase_lvgl_tick,
        .name = "lvgl_tick"
    };
    esp_timer_handle_t lvgl_tick_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, LVGL_TICK_PERIOD_MS * 1000));

    lvgl_mux = xSemaphoreCreateRecursiveMutex();
    assert(lvgl_mux);
    ESP_LOGI(TAG, "Create LVGL task");
    xTaskCreate(lvgl_port_task, "LVGL", LVGL_TASK_STACK_SIZE, NULL, LVGL_TASK_PRIORITY, NULL);

    return disp;
}
