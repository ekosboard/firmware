#ifndef FONT_H
#define FONT_H

#include "draw/lv_image_dsc.h"
#include "lvgl.h"

extern const lv_font_t roboto_48;
extern const lv_font_t roboto_64;
extern const lv_font_t roboto_96;
extern const lv_font_t roboto_48_bold;
extern const lv_font_t roboto_64_bold;
extern const lv_font_t roboto_96_bold;
extern const lv_font_t symbol_nerdfont;
extern const lv_font_t symbol_nerdfont_48;

extern const lv_font_t symbol_nerdfont_14;
extern const lv_font_t symbol_nerdfont_24;
extern const lv_font_t symbol_nerdfont_96;

extern const lv_image_dsc_t logo;

#define SYMBOL_THERMOMETER "\xEE\x88\x8A"
#define SYMBOL_THERMOMETER_2 "\xEE\x8D\x90"
#define SYMBOL_THERMOMETER_3 "\xEF\x8B\x89"
#define SYMBOL_HOME_THERMO "\xF3\xB0\xBD\x95"
#define SYMBOL_HUMIDITY "\xEE\x8D\xB3"
#define SYMBOL_HOME "\xF3\xB0\x8B\x9C"

#define SYMBOL_WEATHER_SUNNY            "\xEE\x8C\x8D" //e30d
#define SYMBOL_WEATHER_FEW_CLOUDS       "\xEE\x8C\x82" //e302
#define SYMBOL_WEATHER_SCATTERED_CLOUDS "\xEE\x8C\xBD" //e33d
#define SYMBOL_WEATHER_BROKEN_CLOUDS    "\xEE\x8C\x92" //e312
#define SYMBOL_WEATHER_RAIN             "\xEE\x8C\x88" //e308
#define SYMBOL_WEATHER_SHOWER_RAIN      "\xEE\x8C\x98" //e318
#define SYMBOL_WEATHER_THUNDERSTORM     "\xEE\x8C\x9D" //e31d
#define SYMBOL_WEATHER_MIST             "\xEE\x8C\x93" //e313
#define SYMBOL_WEATHER_SNOW             "\xEF\x8B\x9C" //f2dc

#define SYMBOL_WEATHER_SUNRISE          "\xEE\x8D\x8C" //e34c
#define SYMBOL_WEATHER_SUNSET           "\xEE\x8D\x8D" //e34d
#define SYMBOL_WEATHER_RAINDROPS        "\xEE\x8D\x8A" //e34a

#define SYMBOL_ARROW_DOWN               "\xEE\xAA\x9A" //ea9a
#define SYMBOL_ARROW_UP                 "\xEE\xAA\xA1" //eaa1
#define SYMBOL_ARROW_LEFT               "\xEE\xAA\x9B" //ea9b
#define SYMBOL_ARROW_RIGHT              "\xEE\xAA\x9C" //ea9c

#define SYMBOL_BATTERY_EMPTY            "\xEF\x89\x84" //f244
#define SYMBOL_BATTERY_QUARTER          "\xEF\x89\x83" //f243
#define SYMBOL_BATTERY_HALF             "\xEF\x89\x82" //f242
#define SYMBOL_BATTERY_FULL             "\xEF\x89\x80" //f240

#define SYMBOL_WIFI                     "\xF3\xB0\x96\xA9" //f05a9
#define SYMBOL_WIFI_OFF                 "\xF3\xB0\x96\xAA" //f05aa
#define SYMBOL_WIFI_ALERT               "\xF3\xB1\x9A\xB5" //f16b5
#define SYMBOL_WIFI_CHECK               "\xF3\xB1\x9A\xBD" //f16bd

#define SYMBOL_SYNC                     "\xEE\xA9\xB7" //ea77
#define SYMBOL_CHECK                    "\xEE\xAA\xB2" //eab2
#define SYMBOL_CLOSE                    "\xEE\xA9\xB6" //ea76

#endif
