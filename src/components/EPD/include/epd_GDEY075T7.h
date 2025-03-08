#ifndef GDEY075T7_H
#define GDEY075T7_H

#define GDEY075T7_WIDTH     800
#define GDEY075T7_HEIGHT    480
#define GDEY075T7_ARRAY     (GDEY075T7_WIDTH * GDEY075T7_HEIGHT / 8)

#define GDEY075T7_GRAY      4 // 8-16

#define GDEY075T7_BUSY      GPIO_NUM_5
#define GDEY075T7_RST       GPIO_NUM_6
#define GDEY075T7_DC        GPIO_NUM_7
#define GDEY075T7_CS        GPIO_NUM_10
#define GDEY075T7_MOSI      GPIO_NUM_11
#define GDEY075T7_SCLK      GPIO_NUM_12

#include "epd_interface.h"

extern epd_interface_t gdey075t7_driver;

#endif
