#ifndef GDEY042T81_H
#define GDEY042T81_H

#define GDEY042T81_WIDTH    400
#define GDEY042T81_HEIGHT   300
#define GDEY042T81_ARRAY    (GDEY042T81_WIDTH*GDEY042T81_HEIGHT / 8)

#define GDEY042T81_GRAY     4

#define GDEY042T81_MOSI     GPIO_NUM_4
#define GDEY042T81_SCLK     GPIO_NUM_5
#define GDEY042T81_CS       GPIO_NUM_6
#define GDEY042T81_DC       GPIO_NUM_7
#define GDEY042T81_RST      GPIO_NUM_15
#define GDEY042T81_BUSY     GPIO_NUM_16

#include "epd_interface.h"

extern epd_interface_t gdey042t81_driver;

#endif
