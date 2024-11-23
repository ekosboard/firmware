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


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
