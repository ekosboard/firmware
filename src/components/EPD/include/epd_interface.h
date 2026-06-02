#ifndef EPD_INTERFACE_H
#define EPD_INTERFACE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    void (*init)(void);
    void (*clear)(void);
    void (*display_image)(const uint8_t* image);
    void (*display_image_fast)(const uint8_t* image);
    void (*display_image_grayscale)(const uint8_t* image);
    void (*display_image_partial)(const uint8_t* image, bool set_ram);
    void (*display_image_area)(const uint8_t* image, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
    void (*set_basemap)(const uint8_t* image);
    void (*sleep)(void);
}   epd_interface_t;

#endif
