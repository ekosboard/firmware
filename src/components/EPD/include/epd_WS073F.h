#ifndef EPD_WS073F_H
#define EPD_WS073F_H

#define EPD_7IN3F_BLACK   0x0
#define EPD_7IN3F_WHITE   0x1
#define EPD_7IN3F_GREEN   0x2
#define EPD_7IN3F_BLUE    0x3
#define EPD_7IN3F_RED     0x4
#define EPD_7IN3F_YELLOW  0x5
#define EPD_7IN3F_ORANGE  0x6
#define EPD_7IN3F_CLEAN   0x7

#define WS073F_WIDTH    800
#define WS073F_HEIGHT   480
#define WS073F_ARRAY    (WS073F_WIDTH * WS073F_HEIGHT / 2)

#define WS073F_BUSY     GPIO_NUM_5
#define WS073F_RST      GPIO_NUM_6
#define WS073F_DC       GPIO_NUM_7
#define WS073F_CS       GPIO_NUM_10
#define WS073F_MOSI     GPIO_NUM_11
#define WS073F_SCLK     GPIO_NUM_12

#include "epd_interface.h"

extern epd_interface_t ws073f_driver;

#endif
