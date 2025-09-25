/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --stride 1 --align 1 --font BlexMonoNerdFontMono-SemiBold.ttf --range 32-127,57866,58227,58125,58136,983772,984294,984295,58192,62153,986965,58125,58114,58173,58130,58136,58120,58141,62172,58131,58188,58189,58186,60058,60065,60059,60060,62020,62019,62018,62016,984489,984490,988853,988861,60023,60082 --format lvgl -o symbol_nerdfont_14.c
 ******************************************************************************/

#include "UI.h"

#ifndef SYMBOL_NERDFONT_14
#define SYMBOL_NERDFONT_14 1
#endif

#if SYMBOL_NERDFONT_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xf8, 0x3c,

    /* U+0022 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+0023 "#" */
    0x12, 0x36, 0x36, 0xf7, 0x24, 0x24, 0x24, 0xef,
    0x6c, 0x6c, 0x48,

    /* U+0024 "$" */
    0x18, 0x31, 0xf7, 0xed, 0x9b, 0x1f, 0x1f, 0x1e,
    0x3f, 0x7f, 0xe1, 0x83, 0x0,

    /* U+0025 "%" */
    0x73, 0xda, 0xda, 0xdc, 0xdc, 0x70, 0xe, 0x3b,
    0x7b, 0x5b, 0xce,

    /* U+0026 "&" */
    0x3c, 0x64, 0x60, 0x60, 0x30, 0x7b, 0xda, 0xce,
    0xc6, 0xc6, 0x7b,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x19, 0x98, 0x8c, 0x63, 0x18, 0xc2, 0x18, 0x61,
    0x80,

    /* U+0029 ")" */
    0xc3, 0xc, 0x21, 0x8c, 0x63, 0x18, 0x8c, 0xcc,
    0x0,

    /* U+002A "*" */
    0x18, 0x18, 0xdb, 0xff, 0x3c, 0x3c, 0x66, 0x0,

    /* U+002B "+" */
    0x30, 0x60, 0xc7, 0xf3, 0x6, 0xc, 0x0,

    /* U+002C "," */
    0xdb, 0x40,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xfc,

    /* U+002F "/" */
    0x4, 0x30, 0x86, 0x18, 0x43, 0xc, 0x21, 0x86,
    0x10, 0xc3, 0x0,

    /* U+0030 "0" */
    0x38, 0xdb, 0x1e, 0x3c, 0x7b, 0xf7, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+0031 "1" */
    0x3c, 0x3c, 0x6c, 0x4c, 0xc, 0xc, 0xc, 0xc,
    0xc, 0xc, 0x7f,

    /* U+0032 "2" */
    0x79, 0x89, 0x18, 0x30, 0x61, 0xc7, 0x1c, 0x71,
    0xc3, 0xf8,

    /* U+0033 "3" */
    0x7c, 0x8d, 0x18, 0x30, 0x47, 0x1, 0x83, 0x47,
    0x8d, 0xf0,

    /* U+0034 "4" */
    0xe, 0xe, 0x1e, 0x16, 0x36, 0x26, 0x66, 0x46,
    0xff, 0x6, 0x6,

    /* U+0035 "5" */
    0x7e, 0x60, 0x60, 0x60, 0x5e, 0x67, 0x3, 0x3,
    0x43, 0x66, 0x3c,

    /* U+0036 "6" */
    0x18, 0x61, 0x83, 0xd, 0xdd, 0xf1, 0xe3, 0xc6,
    0x98, 0xe0,

    /* U+0037 "7" */
    0xff, 0x8f, 0x18, 0x60, 0xc1, 0x86, 0xc, 0x18,
    0x60, 0xc0,

    /* U+0038 "8" */
    0x7d, 0x8f, 0x1e, 0x34, 0x47, 0x31, 0xe3, 0xc7,
    0x8d, 0xf0,

    /* U+0039 "9" */
    0x38, 0xdb, 0x1e, 0x3c, 0x7d, 0xdd, 0x86, 0xc,
    0x30, 0xc0,

    /* U+003A ":" */
    0xfc, 0x3f,

    /* U+003B ";" */
    0xfc, 0xf, 0xa0,

    /* U+003C "<" */
    0x4, 0x73, 0xb8, 0xc3, 0x83, 0x83, 0x4,

    /* U+003D "=" */
    0xfe, 0x0, 0x0, 0xf, 0xe0,

    /* U+003E ">" */
    0x83, 0x87, 0x7, 0xc, 0x77, 0x30, 0x80,

    /* U+003F "?" */
    0x3d, 0x8d, 0x18, 0x30, 0xe7, 0xc, 0x0, 0x0,
    0x60, 0xc0,

    /* U+0040 "@" */
    0x3c, 0xcb, 0x1e, 0xff, 0x7e, 0xfd, 0xfb, 0xdf,
    0x81, 0x81, 0xc0,

    /* U+0041 "A" */
    0x1c, 0x1c, 0x3c, 0x3c, 0x36, 0x26, 0x66, 0x7e,
    0x63, 0x43, 0xc3,

    /* U+0042 "B" */
    0xf9, 0x9b, 0x36, 0x6c, 0xdf, 0x31, 0xe3, 0xc7,
    0x8f, 0xf0,

    /* U+0043 "C" */
    0x3c, 0xcf, 0x1e, 0xc, 0x18, 0x30, 0x60, 0xc6,
    0xcc, 0xf0,

    /* U+0044 "D" */
    0xf9, 0x9b, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x9b, 0xe0,

    /* U+0045 "E" */
    0xff, 0xc, 0x30, 0xc3, 0xfc, 0x30, 0xc3, 0xf,
    0xc0,

    /* U+0046 "F" */
    0xff, 0x83, 0x6, 0xc, 0x1f, 0xb0, 0x60, 0xc1,
    0x83, 0x0,

    /* U+0047 "G" */
    0x3c, 0xdf, 0x16, 0xc, 0x1b, 0xf1, 0xe3, 0xc6,
    0xdd, 0xd8,

    /* U+0048 "H" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x7f, 0xf1, 0xe3, 0xc7,
    0x8f, 0x18,

    /* U+0049 "I" */
    0xfc, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xcf,
    0xc0,

    /* U+004A "J" */
    0x7e, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x46,
    0xcc, 0xf0,

    /* U+004B "K" */
    0xc7, 0x9b, 0x36, 0xcf, 0x1f, 0x3e, 0x66, 0xcd,
    0x8f, 0x18,

    /* U+004C "L" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xf,
    0xc0,

    /* U+004D "M" */
    0xef, 0xdf, 0xbf, 0xfd, 0x7a, 0xf5, 0xeb, 0xc7,
    0x8f, 0x18,

    /* U+004E "N" */
    0xe7, 0xcf, 0x9f, 0xbd, 0x7a, 0xf5, 0xef, 0xcf,
    0x9f, 0x38,

    /* U+004F "O" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+0050 "P" */
    0xfd, 0x8f, 0x1e, 0x3c, 0x78, 0xff, 0x60, 0xc1,
    0x83, 0x0,

    /* U+0051 "Q" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    0xdd, 0xf0, 0xc1, 0x83, 0x80,

    /* U+0052 "R" */
    0xfd, 0x8f, 0x1e, 0x3c, 0x78, 0xff, 0x6c, 0xcd,
    0x9b, 0x18,

    /* U+0053 "S" */
    0x7d, 0x8b, 0x6, 0xf, 0x8f, 0x8f, 0x83, 0x7,
    0x89, 0xe0,

    /* U+0054 "T" */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8d, 0xf0,

    /* U+0056 "V" */
    0xc3, 0x63, 0x63, 0x66, 0x66, 0x26, 0x36, 0x34,
    0x3c, 0x1c, 0x1c,

    /* U+0057 "W" */
    0xc3, 0xc3, 0xc3, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    0xef, 0xe7, 0xe7,

    /* U+0058 "X" */
    0x63, 0x66, 0x36, 0x3c, 0x1c, 0x18, 0x3c, 0x3c,
    0x66, 0x66, 0xc3,

    /* U+0059 "Y" */
    0xc3, 0xe2, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+005A "Z" */
    0xfe, 0xc, 0x30, 0x61, 0x87, 0xc, 0x30, 0x61,
    0x83, 0xf8,

    /* U+005B "[" */
    0xfe, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8f,
    0x80,

    /* U+005C "\\" */
    0xc1, 0x6, 0x18, 0x20, 0xc3, 0x4, 0x18, 0x60,
    0x83, 0xc, 0x10,

    /* U+005D "]" */
    0xf8, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x3f,
    0x80,

    /* U+005E "^" */
    0x18, 0x1c, 0x3c, 0x26, 0x66, 0x63, 0x43,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0x4d, 0x80,

    /* U+0061 "a" */
    0x78, 0x98, 0x30, 0x67, 0xd9, 0xb3, 0x3f,

    /* U+0062 "b" */
    0xc1, 0x83, 0x6, 0xee, 0xf8, 0xf1, 0xe3, 0xc7,
    0x9f, 0xf0,

    /* U+0063 "c" */
    0x3c, 0xcb, 0x6, 0xc, 0x18, 0x19, 0x9e,

    /* U+0064 "d" */
    0x6, 0xc, 0x1b, 0xfe, 0x78, 0xf1, 0xe3, 0xc7,
    0xcd, 0xf8,

    /* U+0065 "e" */
    0x38, 0x8b, 0x1f, 0xfc, 0x18, 0x19, 0x1e,

    /* U+0066 "f" */
    0x1e, 0x60, 0xc7, 0xf3, 0x6, 0xc, 0x18, 0x30,
    0x63, 0xf8,

    /* U+0067 "g" */
    0x6, 0xfb, 0x1e, 0x3c, 0x6f, 0xb0, 0x60, 0x7d,
    0x8f, 0x1b, 0xe0,

    /* U+0068 "h" */
    0xc3, 0xc, 0x3e, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xc0,

    /* U+0069 "i" */
    0x30, 0xc0, 0x3c, 0x30, 0xc3, 0xc, 0x30, 0xcf,
    0xc0,

    /* U+006A "j" */
    0x18, 0xc1, 0xf1, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0xf8,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0x7c, 0xdb, 0x3c, 0x7c, 0xcd,
    0x9b, 0x18,

    /* U+006C "l" */
    0xf0, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xcf,
    0xc0,

    /* U+006D "m" */
    0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,

    /* U+006E "n" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3,

    /* U+006F "o" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xdb, 0x1c,

    /* U+0070 "p" */
    0xdd, 0xdf, 0x1e, 0x3c, 0x78, 0xf3, 0xfe, 0xc1,
    0x83, 0x0,

    /* U+0071 "q" */
    0x77, 0xdf, 0x1e, 0x3c, 0x78, 0xf9, 0xbf, 0x6,
    0xc, 0x18,

    /* U+0072 "r" */
    0xf6, 0x7c, 0xe1, 0x83, 0x6, 0xc, 0x7e,

    /* U+0073 "s" */
    0x7b, 0x2c, 0x3e, 0x7c, 0x38, 0xfe,

    /* U+0074 "t" */
    0x30, 0x60, 0xc7, 0xf3, 0x6, 0xc, 0x18, 0x30,
    0x60, 0x78,

    /* U+0075 "u" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xdf,

    /* U+0076 "v" */
    0xc7, 0x8b, 0x32, 0x66, 0x8d, 0xe, 0x18,

    /* U+0077 "w" */
    0xd9, 0xd9, 0xd9, 0x5f, 0x57, 0x57, 0x56, 0x66,

    /* U+0078 "x" */
    0x62, 0x36, 0x3c, 0x18, 0x1c, 0x3c, 0x66, 0x63,

    /* U+0079 "y" */
    0x43, 0x62, 0x66, 0x26, 0x34, 0x3c, 0x1c, 0x18,
    0x18, 0x10, 0x70,

    /* U+007A "z" */
    0xfc, 0x31, 0x8c, 0x31, 0x8c, 0x3f,

    /* U+007B "{" */
    0x3c, 0xc3, 0xe, 0x18, 0x6e, 0x6, 0x18, 0xe3,
    0xc, 0x3c,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xc0,

    /* U+007D "}" */
    0xf0, 0xc3, 0x1c, 0x61, 0x81, 0xd8, 0x61, 0xc3,
    0xc, 0xf0,

    /* U+007E "~" */
    0x67, 0x6e, 0x70,

    /* U+E20A "" */
    0x32, 0x94, 0xa5, 0x39, 0xce, 0x75, 0x7f, 0x57,
    0x0,

    /* U+E302 "" */
    0x0, 0x10, 0xc, 0x7c, 0xcc, 0x84, 0xfc,

    /* U+E308 "" */
    0x0, 0xe, 0x7c, 0xcc, 0x94, 0xfc, 0x20, 0x0,

    /* U+E30D "" */
    0x10, 0xcc, 0xd2, 0x70, 0x40,

    /* U+E312 "" */
    0x8, 0xed, 0x3c, 0x2f, 0xc0,

    /* U+E313 "" */
    0x10, 0xd0, 0x1b, 0xff, 0xcf, 0xc0,

    /* U+E318 "" */
    0x72, 0x38, 0x7b, 0x30,

    /* U+E31D "" */
    0x71, 0x38, 0xf5, 0x60, 0x0,

    /* U+E33D "" */
    0x72, 0x38, 0x7f,

    /* U+E34A "" */
    0x4, 0x6, 0x44, 0xe0, 0xe0, 0xe4, 0xe, 0xf,
    0x1f, 0x1f, 0xf, 0x4,

    /* U+E34C "" */
    0x10, 0x42, 0x3c, 0x44, 0x85, 0x10, 0x6c,

    /* U+E34D "" */
    0x10, 0x44, 0x3c, 0x44, 0x85, 0x0, 0x6c, 0x10,

    /* U+E350 "" */
    0x31, 0xa4, 0x92, 0x49, 0xa6, 0x9a, 0xe6, 0xfb,
    0xf3, 0x78,

    /* U+E373 "" */
    0x10, 0x71, 0xd6, 0xea, 0xfe, 0x7e, 0xae, 0x38,

    /* U+EA77 "" */
    0x0, 0x3c, 0x2, 0x43, 0xc0, 0x42, 0x3c,

    /* U+EA9A "" */
    0x10, 0x20, 0x40, 0x89, 0x2b, 0x8c, 0x0,

    /* U+EA9B "" */
    0x20, 0x82, 0x7, 0xf8, 0x8, 0x8, 0x0,

    /* U+EA9C "" */
    0x0, 0x10, 0x17, 0xf0, 0x41, 0x0, 0x0,

    /* U+EAA1 "" */
    0x10, 0xf2, 0x50, 0x81, 0x2, 0x4, 0x0,

    /* U+EAB2 "" */
    0x0, 0x1, 0x2, 0x4, 0x88, 0x50, 0x60,

    /* U+F240 "" */
    0xff, 0xff, 0xff, 0xff, 0xff,

    /* U+F242 "" */
    0xff, 0xf1, 0xf1, 0xf1, 0xff,

    /* U+F243 "" */
    0xff, 0xe1, 0xe1, 0xe1, 0xff,

    /* U+F244 "" */
    0xff, 0x81, 0x81, 0x81, 0xff,

    /* U+F2C9 "" */
    0x3c, 0x66, 0x46, 0x46, 0x56, 0x56, 0x56, 0xff,
    0xfb, 0xc3, 0x66, 0x3c,

    /* U+F2DC "" */
    0x8, 0xe, 0x3a, 0xff, 0xf0, 0x87, 0xff, 0xae,
    0x38, 0x8, 0x0,

    /* U+F02DC "󰋜" */
    0x0, 0x3c, 0x7e, 0xff, 0x7e, 0x66, 0x66,

    /* U+F04E6 "󰓦" */
    0x0, 0x10, 0x3c, 0x12, 0x81, 0x81, 0x81, 0x81,
    0x48, 0x3c, 0x8, 0x0,

    /* U+F04E7 "󰓧" */
    0x23, 0x4a, 0x89, 0x89, 0x81, 0x6b, 0x62,

    /* U+F05A9 "󰖩" */
    0x3e, 0xc3, 0x81, 0x3c, 0x2, 0x18, 0x18, 0x0,

    /* U+F05AA "󰖪" */
    0xbe, 0xc1, 0x2c, 0x36, 0x8, 0x1c, 0x2,

    /* U+F0F55 "󰽕" */
    0x18, 0x20, 0x47, 0xc3, 0x43, 0x47, 0x37,

    /* U+F16B5 "󱚵" */
    0x3e, 0x79, 0x0, 0x27, 0xd0, 0x0, 0xe4, 0x30,
    0x0,

    /* U+F16BD "󱚽" */
    0x7e, 0xc1, 0x1c, 0x26, 0x0, 0x19, 0x2
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 134, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 134, .box_w = 2, .box_h = 11, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 134, .box_w = 5, .box_h = 4, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 134, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 31, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 134, .box_w = 2, .box_h = 4, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 54, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 63, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 72, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 87, .adv_w = 134, .box_w = 3, .box_h = 4, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 89, .adv_w = 134, .box_w = 4, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 90, .adv_w = 134, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 102, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 134, .box_w = 2, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 134, .box_w = 2, .box_h = 10, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 210, .adv_w = 134, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 134, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 222, .adv_w = 134, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 250, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 261, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 300, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 320, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 134, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 421, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 441, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 525, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 536, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 545, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 552, .adv_w = 134, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 553, .adv_w = 134, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 555, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 579, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 589, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 617, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 134, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 644, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 654, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 671, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 694, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 704, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 711, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 727, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 733, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 740, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 748, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 756, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 767, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 773, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 783, .adv_w = 134, .box_w = 2, .box_h = 13, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 787, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 797, .adv_w = 134, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 800, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 809, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 816, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 824, .adv_w = 134, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 829, .adv_w = 134, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 834, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 840, .adv_w = 134, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 844, .adv_w = 134, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 849, .adv_w = 134, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 852, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 864, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 871, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 879, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 889, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 897, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 904, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 911, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 918, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 925, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 932, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 939, .adv_w = 134, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 944, .adv_w = 134, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 949, .adv_w = 134, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 954, .adv_w = 134, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 959, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 971, .adv_w = 134, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 982, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 989, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1001, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1008, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1016, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1023, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1030, .adv_w = 134, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1039, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0xf8, 0xfe, 0x103, 0x108, 0x109, 0x10e, 0x113,
    0x133, 0x140, 0x142, 0x143, 0x146, 0x169, 0x86d, 0x890,
    0x891, 0x892, 0x897, 0x8a8, 0x1036, 0x1038, 0x1039, 0x103a,
    0x10bf, 0x10d2
};

static const uint16_t unicode_list_2[] = {
    0x0, 0x20a, 0x20b, 0x2cd, 0x2ce, 0xc79, 0x13d9, 0x13e1
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 57866, .range_length = 4307, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 26, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 983772, .range_length = 5090, .glyph_id_start = 122,
        .unicode_list = unicode_list_2, .glyph_id_ofs_list = NULL, .list_length = 8, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 3,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};

extern const lv_font_t symbol_nerdfont_14;


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t symbol_nerdfont_14 = {
#else
lv_font_t symbol_nerdfont_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &symbol_nerdfont_14,
#endif
    .user_data = NULL,
};



#endif /*#if SYMBOL_NERDFONT_14*/
