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

#define EPD_EVENT_FLUSH_COMPLETE   BIT0

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

#ifdef CONFIG_EPD_WS073F
    #include "epd_WS073F.h"
    #define EPD_DRIVER  (&ws073f_driver)
    #define EPD_WIDTH   WS073F_WIDTH
    #define EPD_HEIGHT  WS073F_HEIGHT
    #define EPD_ARRAY   WS073F_ARRAY
#endif

#ifdef __cplusplus
extern "C" {
#endif

    void init_epd_event_group(void);
    void set_epd_event(uint32_t bits);
    EventGroupHandle_t get_epd_event_group(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
