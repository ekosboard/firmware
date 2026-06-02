/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --no-compress --stride 1 --align 1 --font Roboto-Bold.ttf --range 32-127,160-255,8352-8399,8192-8303 --format lvgl -o roboto_bold_16.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef ROBOTO_BOLD_16
#define ROBOTO_BOLD_16 1
#endif

#if ROBOTO_BOLD_16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0xf,

    /* U+0022 "\"" */
    0xff, 0xff,

    /* U+0023 "#" */
    0x1a, 0xd, 0x4, 0x8f, 0xf7, 0xf8, 0xb0, 0xd1,
    0xfe, 0xff, 0x12, 0x9, 0x5, 0x80,

    /* U+0024 "$" */
    0x8, 0x8, 0x3c, 0x7e, 0x67, 0x63, 0x60, 0x38,
    0xe, 0x3, 0x63, 0x67, 0x7f, 0x3e, 0x8, 0x8,

    /* U+0025 "%" */
    0x70, 0x1f, 0x3, 0x64, 0x6d, 0x8f, 0xa0, 0xe8,
    0x3, 0xf0, 0x7f, 0x16, 0x64, 0xcc, 0x1f, 0x81,
    0xe0,

    /* U+0026 "&" */
    0x3c, 0x1f, 0x86, 0x61, 0x98, 0x7c, 0xe, 0x7,
    0x9b, 0x76, 0xcf, 0xb1, 0xcf, 0xf0, 0xf6,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x13, 0x66, 0xcc, 0xcc, 0xcc, 0xcc, 0x66, 0x33,
    0x0,

    /* U+0029 ")" */
    0x8c, 0x66, 0x23, 0x33, 0x33, 0x33, 0x66, 0xcc,
    0x0,

    /* U+002A "*" */
    0x18, 0x18, 0xdb, 0x7e, 0x3c, 0x6c, 0x66,

    /* U+002B "+" */
    0x18, 0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18,
    0x18, 0x18,

    /* U+002C "," */
    0x6d, 0xb4,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0xc, 0x21, 0x86, 0x10, 0xc3, 0x8, 0x61, 0x84,
    0x30, 0xc0,

    /* U+0030 "0" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3c,

    /* U+0031 "1" */
    0xb, 0xff, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x30,

    /* U+0032 "2" */
    0x3c, 0x7e, 0xc6, 0xc6, 0x6, 0xc, 0x1c, 0x18,
    0x30, 0x60, 0xff, 0xff,

    /* U+0033 "3" */
    0x3c, 0x7f, 0x63, 0x3, 0x1f, 0x1e, 0x1f, 0x3,
    0x63, 0x63, 0x7e, 0x3c,

    /* U+0034 "4" */
    0x6, 0x7, 0x7, 0x83, 0xc3, 0x61, 0x31, 0x99,
    0xff, 0xff, 0x83, 0x1, 0x80, 0xc0,

    /* U+0035 "5" */
    0xff, 0xff, 0x6, 0xf, 0xdf, 0xd3, 0x83, 0x7,
    0x8f, 0xf3, 0xc0,

    /* U+0036 "6" */
    0xc, 0x3c, 0x70, 0x60, 0xdc, 0xfe, 0xc7, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3c,

    /* U+0037 "7" */
    0xff, 0xff, 0x7, 0x6, 0x6, 0xc, 0xc, 0x18,
    0x18, 0x38, 0x30, 0x70,

    /* U+0038 "8" */
    0x3c, 0xff, 0xc3, 0xc3, 0xe7, 0x3c, 0x7e, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3c,

    /* U+0039 "9" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xe3, 0x7f, 0x3b,
    0x6, 0xe, 0x3c, 0x30,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0,

    /* U+003B ";" */
    0xf0, 0xf, 0xf8,

    /* U+003C "<" */
    0x2, 0x3d, 0xf7, 0x8f, 0x7, 0xc3, 0x81,

    /* U+003D "=" */
    0xff, 0xfc, 0x7, 0xff, 0xe0,

    /* U+003E ">" */
    0x81, 0xe1, 0xf0, 0x71, 0xff, 0x38, 0x40,

    /* U+003F "?" */
    0x3e, 0x7f, 0x63, 0x3, 0x3, 0xe, 0x1c, 0x18,
    0x18, 0x0, 0x18, 0x18,

    /* U+0040 "@" */
    0xf, 0x80, 0xff, 0xe, 0x1c, 0xce, 0x66, 0xf9,
    0xe6, 0x4f, 0x66, 0x7b, 0x33, 0xd9, 0x9e, 0xcd,
    0xf7, 0xbc, 0xdd, 0xc7, 0x0, 0x1f, 0xc0, 0x7c,
    0x0,

    /* U+0041 "A" */
    0xe, 0x1, 0xc0, 0x78, 0xf, 0x81, 0xb0, 0x76,
    0xc, 0xe1, 0x8c, 0x7f, 0x8f, 0xf9, 0x83, 0x70,
    0x60,

    /* U+0042 "B" */
    0xfc, 0xff, 0xc3, 0xc3, 0xc3, 0xfe, 0xff, 0xc3,
    0xc3, 0xc3, 0xfe, 0xfc,

    /* U+0043 "C" */
    0x1e, 0x3f, 0x98, 0xf8, 0x3c, 0x6, 0x3, 0x1,
    0x80, 0xc1, 0xb1, 0xdf, 0xc7, 0xc0,

    /* U+0044 "D" */
    0xfc, 0x7f, 0x30, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe1, 0xbf, 0x9f, 0x80,

    /* U+0045 "E" */
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xfe, 0xfe, 0xc0,
    0xc0, 0xc0, 0xff, 0xff,

    /* U+0046 "F" */
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xfe, 0xfe, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0047 "G" */
    0x3e, 0x3f, 0x98, 0xf8, 0x3c, 0x6, 0x3, 0x1f,
    0x8f, 0xc1, 0xb0, 0xdf, 0xe7, 0xc0,

    /* U+0048 "H" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1f, 0xff, 0xff,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x30,

    /* U+0049 "I" */
    0xff, 0xff, 0xff,

    /* U+004A "J" */
    0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0xc7,
    0x8d, 0xf1, 0xc0,

    /* U+004B "K" */
    0xc3, 0x63, 0xb3, 0x9b, 0x8d, 0x87, 0xc3, 0xf1,
    0xf8, 0xce, 0x63, 0x31, 0xd8, 0x70,

    /* U+004C "L" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xff, 0xff,

    /* U+004D "M" */
    0xe0, 0x7e, 0x7, 0xf0, 0xff, 0xf, 0xd9, 0xbd,
    0x9b, 0xd9, 0xbc, 0xf3, 0xcf, 0x3c, 0xf3, 0xc6,
    0x3c, 0x63,

    /* U+004E "N" */
    0xc1, 0xf0, 0xfc, 0x7e, 0x3f, 0x9e, 0xcf, 0x37,
    0x9f, 0xc7, 0xe3, 0xf0, 0xf8, 0x30,

    /* U+004F "O" */
    0x1e, 0x1f, 0xe6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xd8, 0x67, 0xf8, 0x78,

    /* U+0050 "P" */
    0xfe, 0x7f, 0xb0, 0xf8, 0x3c, 0x1e, 0x1f, 0xfd,
    0xfc, 0xc0, 0x60, 0x30, 0x18, 0x0,

    /* U+0051 "Q" */
    0x1e, 0x1f, 0xe6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xd8, 0x67, 0xf8, 0x7e, 0x1,
    0xc0, 0x20,

    /* U+0052 "R" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xfc,
    0xce, 0xc6, 0xc7, 0xc3,

    /* U+0053 "S" */
    0x1e, 0x1f, 0x98, 0xec, 0x37, 0x1, 0xe0, 0x3c,
    0x7, 0x61, 0xb0, 0xdf, 0xe3, 0xc0,

    /* U+0054 "T" */
    0xff, 0xff, 0xf0, 0xc0, 0x30, 0xc, 0x3, 0x0,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xf1, 0xdf, 0xc7, 0xc0,

    /* U+0056 "V" */
    0xe0, 0xd8, 0x76, 0x1d, 0xc6, 0x31, 0x8c, 0xe3,
    0x30, 0x6c, 0x1f, 0x7, 0x81, 0xe0, 0x38,

    /* U+0057 "W" */
    0x63, 0x19, 0x8c, 0x66, 0x31, 0x99, 0xe6, 0x77,
    0xb8, 0xde, 0xc3, 0x7b, 0xd, 0x2c, 0x3c, 0xf0,
    0xf3, 0xc1, 0xce, 0x6, 0x18,

    /* U+0058 "X" */
    0x61, 0xdc, 0xe3, 0x38, 0xfc, 0x1e, 0x7, 0x81,
    0xe0, 0x78, 0x3f, 0xc, 0xe7, 0x1b, 0x87,

    /* U+0059 "Y" */
    0xe1, 0xd8, 0x67, 0x38, 0xcc, 0x3f, 0x7, 0x81,
    0xe0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30,

    /* U+005A "Z" */
    0xff, 0xff, 0xc1, 0xc0, 0xe0, 0xe0, 0xe0, 0x70,
    0x70, 0x70, 0x38, 0x3f, 0xff, 0xf0,

    /* U+005B "[" */
    0xff, 0x6d, 0xb6, 0xdb, 0x6d, 0xb7, 0xe0,

    /* U+005C "\\" */
    0xe0, 0xc1, 0x83, 0x83, 0x6, 0xe, 0xc, 0x18,
    0x38, 0x30, 0x70, 0x60,

    /* U+005D "]" */
    0xfd, 0xb6, 0xdb, 0x6d, 0xb6, 0xdf, 0xe0,

    /* U+005E "^" */
    0x38, 0x70, 0xa3, 0x66, 0xc8, 0x80,

    /* U+005F "_" */
    0xff, 0xfc,

    /* U+0060 "`" */
    0x63,

    /* U+0061 "a" */
    0x7d, 0xff, 0x1b, 0xff, 0xf8, 0xf1, 0xff, 0x76,

    /* U+0062 "b" */
    0xc1, 0x83, 0x7, 0xef, 0xd8, 0xf1, 0xe3, 0xc7,
    0x8f, 0xf7, 0xe0,

    /* U+0063 "c" */
    0x3c, 0x7e, 0xe6, 0xc0, 0xc0, 0xc0, 0xe6, 0x7e,
    0x3c,

    /* U+0064 "d" */
    0x6, 0xc, 0x1b, 0xb7, 0xfc, 0xf1, 0xe3, 0xc7,
    0x8d, 0xf9, 0xf0,

    /* U+0065 "e" */
    0x3c, 0x7e, 0xe3, 0xff, 0xff, 0xc0, 0xe2, 0x7f,
    0x3e,

    /* U+0066 "f" */
    0x1c, 0xf3, 0x3f, 0xfc, 0xc3, 0xc, 0x30, 0xc3,
    0xc,

    /* U+0067 "g" */
    0x3b, 0x7f, 0xe3, 0xc3, 0xc3, 0xc3, 0xe3, 0x7f,
    0x3b, 0x47, 0x7e, 0x3c,

    /* U+0068 "h" */
    0xc1, 0x83, 0x6, 0xef, 0xf8, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x30,

    /* U+0069 "i" */
    0xf3, 0xff, 0xff,

    /* U+006A "j" */
    0x33, 0x3, 0x33, 0x33, 0x33, 0x33, 0x3f, 0xe0,

    /* U+006B "k" */
    0xc0, 0xc0, 0xc0, 0xce, 0xdc, 0xd8, 0xf0, 0xf8,
    0xf8, 0xcc, 0xce, 0xc6,

    /* U+006C "l" */
    0xff, 0xff, 0xff,

    /* U+006D "m" */
    0xdc, 0xef, 0xff, 0xc6, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x30,

    /* U+006E "n" */
    0xdd, 0xff, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,

    /* U+006F "o" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e,
    0x3c,

    /* U+0070 "p" */
    0xfd, 0xfb, 0x3e, 0x3c, 0x78, 0xf3, 0xfe, 0xf9,
    0x83, 0x6, 0x0,

    /* U+0071 "q" */
    0x7e, 0xff, 0x9e, 0x3c, 0x78, 0xf1, 0xbf, 0x3e,
    0xc, 0x18, 0x30,

    /* U+0072 "r" */
    0xdf, 0xf1, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0073 "s" */
    0x3c, 0xff, 0x9b, 0x3, 0xc0, 0xf1, 0xff, 0x3c,

    /* U+0074 "t" */
    0x63, 0x3f, 0xf6, 0x31, 0x8c, 0x63, 0xce,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xff, 0x76,

    /* U+0076 "v" */
    0x63, 0x31, 0x9d, 0xce, 0xe3, 0x61, 0xb0, 0xf8,
    0x38, 0x1c, 0x0,

    /* U+0077 "w" */
    0xcc, 0x79, 0xdf, 0x3b, 0x6f, 0x67, 0xac, 0xf7,
    0x9c, 0xe3, 0x9c, 0x31, 0x80,

    /* U+0078 "x" */
    0x67, 0x66, 0x3e, 0x3c, 0x1c, 0x3c, 0x3e, 0x66,
    0xe7,

    /* U+0079 "y" */
    0xe3, 0x67, 0x66, 0x76, 0x3e, 0x3c, 0x3c, 0x1c,
    0x18, 0x18, 0x70, 0x70,

    /* U+007A "z" */
    0xff, 0xfc, 0x30, 0xe3, 0x8e, 0x1c, 0x7f, 0xfe,

    /* U+007B "{" */
    0x0, 0xcc, 0x63, 0x18, 0xce, 0xe7, 0x8c, 0x63,
    0x18, 0xc3, 0x8,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xf0,

    /* U+007D "}" */
    0x6, 0x18, 0xc6, 0x31, 0x8e, 0x3b, 0x98, 0xc6,
    0x31, 0x98, 0x80,

    /* U+007E "~" */
    0x71, 0xfc, 0xb3, 0xd8, 0xc0,

    /* U+00A0 " " */
    0x0,

    /* U+00A1 "¡" */
    0xf0, 0xff, 0xff,

    /* U+00A2 "¢" */
    0x18, 0x18, 0x3c, 0x7e, 0xe6, 0xc0, 0xc0, 0xc0,
    0xe6, 0x7e, 0x3c, 0x18, 0x18,

    /* U+00A3 "£" */
    0x1e, 0x3f, 0x67, 0x60, 0x60, 0xfc, 0xfc, 0x60,
    0x60, 0x60, 0xff, 0xff,

    /* U+00A4 "¤" */
    0xde, 0xff, 0xf6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xd, 0x86, 0xff, 0xd7, 0x80,

    /* U+00A5 "¥" */
    0xe7, 0x66, 0x66, 0x76, 0x3c, 0x3c, 0x7e, 0x7e,
    0x7e, 0x7e, 0x18, 0x18,

    /* U+00A6 "¦" */
    0xff, 0xf0, 0xff, 0xf0,

    /* U+00A7 "§" */
    0x3c, 0xff, 0xc3, 0xc0, 0x70, 0xfe, 0xc7, 0xe3,
    0x7b, 0x3e, 0x7, 0xc3, 0xc3, 0x7f, 0x3c,

    /* U+00A8 "¨" */
    0xcf, 0x30,

    /* U+00A9 "©" */
    0x1f, 0x6, 0x31, 0x39, 0x68, 0xb9, 0x3, 0x20,
    0x64, 0xc, 0x89, 0xce, 0x68, 0x8, 0xc6, 0xf,
    0x80,

    /* U+00AA "ª" */
    0x79, 0x37, 0xd3, 0x4d, 0xf0,

    /* U+00AB "«" */
    0x6d, 0x2d, 0xb6, 0x6d, 0x90,

    /* U+00AC "¬" */
    0xff, 0xfc, 0x18, 0x30,

    /* U+00AD "­" */
    0xff,

    /* U+00AE "®" */
    0x1f, 0x6, 0x31, 0x79, 0x68, 0xb9, 0x13, 0x3c,
    0x64, 0x4c, 0x89, 0xd1, 0x68, 0x8, 0xc6, 0xf,
    0x80,

    /* U+00AF "¯" */
    0xff, 0xc0,

    /* U+00B0 "°" */
    0x69, 0x96,

    /* U+00B1 "±" */
    0x18, 0x30, 0x67, 0xff, 0xe3, 0x6, 0xc, 0x1,
    0xff, 0xf8,

    /* U+00B2 "²" */
    0x76, 0xc6, 0x66, 0x7c,

    /* U+00B3 "³" */
    0x70, 0xce, 0x3d, 0xb8,

    /* U+00B4 "´" */
    0x6c,

    /* U+00B5 "µ" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xff, 0xff,
    0x83, 0x6, 0x0,

    /* U+00B6 "¶" */
    0x3e, 0xfd, 0xff, 0xf7, 0xef, 0xcf, 0x83, 0x6,
    0xc, 0x18, 0x30,

    /* U+00B7 "·" */
    0xf0,

    /* U+00B8 "¸" */
    0xcf, 0xe0,

    /* U+00B9 "¹" */
    0x3f, 0x33, 0x33,

    /* U+00BA "º" */
    0x7b, 0x3c, 0xf3, 0xcd, 0xe0,

    /* U+00BB "»" */
    0x99, 0x26, 0xdb, 0xda, 0x40,

    /* U+00BC "¼" */
    0x70, 0x1e, 0x20, 0xcc, 0x19, 0x3, 0x60, 0x69,
    0x83, 0x70, 0xd6, 0x1b, 0xe6, 0x7c, 0x3, 0x0,
    0x60,

    /* U+00BD "½" */
    0x70, 0x1e, 0x20, 0xcc, 0x1b, 0x3, 0x60, 0x7b,
    0x83, 0xd8, 0xc3, 0x10, 0xc6, 0x30, 0xf, 0x81,
    0xf0,

    /* U+00BE "¾" */
    0x70, 0xf, 0x80, 0x18, 0x83, 0x18, 0x19, 0xd,
    0xb0, 0x76, 0x60, 0x4e, 0xd, 0x60, 0x9f, 0x1b,
    0xf0, 0x6, 0x0, 0x60,

    /* U+00BF "¿" */
    0xc, 0x18, 0x0, 0x60, 0xc3, 0x1c, 0x70, 0xc1,
    0x8f, 0xfb, 0xe0,

    /* U+00C0 "À" */
    0x18, 0x1, 0x80, 0x0, 0x7, 0x0, 0xe0, 0x3c,
    0x7, 0xc0, 0xd8, 0x3b, 0x6, 0x70, 0xc6, 0x3f,
    0xc7, 0xfc, 0xc1, 0xb8, 0x30,

    /* U+00C1 "Á" */
    0x7, 0x0, 0xc0, 0x0, 0x7, 0x0, 0xe0, 0x3c,
    0x7, 0xc0, 0xd8, 0x3b, 0x6, 0x70, 0xc6, 0x3f,
    0xc7, 0xfc, 0xc1, 0xb8, 0x30,

    /* U+00C2 "Â" */
    0xe, 0x3, 0x60, 0x0, 0x7, 0x0, 0xe0, 0x3c,
    0x7, 0xc0, 0xd8, 0x3b, 0x6, 0x70, 0xc6, 0x3f,
    0xc7, 0xfc, 0xc1, 0xb8, 0x30,

    /* U+00C3 "Ã" */
    0x1f, 0x7, 0xe0, 0x0, 0x7, 0x0, 0xe0, 0x3c,
    0x6, 0xc0, 0xd8, 0x3b, 0x6, 0x30, 0xc6, 0x3f,
    0xe7, 0xfc, 0xc1, 0xb8, 0x38,

    /* U+00C4 "Ä" */
    0x33, 0xc, 0xc0, 0x0, 0x30, 0x1e, 0x7, 0x81,
    0xe0, 0xfc, 0x33, 0xc, 0xc7, 0x39, 0xfe, 0x7f,
    0xb8, 0x7c, 0xc,

    /* U+00C5 "Å" */
    0x6, 0x1, 0x20, 0x24, 0x3, 0x0, 0xe0, 0x1e,
    0x3, 0xc0, 0xf8, 0x1b, 0x83, 0x70, 0xe6, 0x18,
    0xc7, 0xfc, 0xff, 0x98, 0x37, 0x7,

    /* U+00C6 "Æ" */
    0x3, 0xfc, 0x1f, 0xf0, 0x78, 0x3, 0x60, 0xd,
    0x80, 0x67, 0xe1, 0x9f, 0x8f, 0xe0, 0x3f, 0x81,
    0xc6, 0x6, 0x1f, 0xf8, 0x7f,

    /* U+00C7 "Ç" */
    0x1e, 0x3f, 0x98, 0xf8, 0x3c, 0x6, 0x3, 0x1,
    0x80, 0xe1, 0xbf, 0xdf, 0xc7, 0xc1, 0xc0, 0x70,
    0x30,

    /* U+00C8 "È" */
    0x70, 0x38, 0x0, 0xff, 0xff, 0xc0, 0xc0, 0xc0,
    0xfe, 0xfe, 0xc0, 0xc0, 0xc0, 0xff, 0xff,

    /* U+00C9 "É" */
    0xc, 0x18, 0x0, 0xff, 0xff, 0xc0, 0xc0, 0xc0,
    0xfe, 0xfe, 0xc0, 0xc0, 0xc0, 0xff, 0xff,

    /* U+00CA "Ê" */
    0x38, 0x6c, 0x0, 0xff, 0xff, 0xc0, 0xc0, 0xc0,
    0xfe, 0xfe, 0xc0, 0xc0, 0xc0, 0xff, 0xff,

    /* U+00CB "Ë" */
    0x66, 0x66, 0x0, 0xff, 0xff, 0xc0, 0xc0, 0xc0,
    0xfe, 0xfe, 0xc0, 0xc0, 0xc0, 0xff, 0xff,

    /* U+00CC "Ì" */
    0x63, 0x3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x30,

    /* U+00CD "Í" */
    0x6c, 0xc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xc0,

    /* U+00CE "Î" */
    0x31, 0x60, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0xc, 0x30, 0xc3, 0x0,

    /* U+00CF "Ï" */
    0xcf, 0x30, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0xc, 0x30, 0xc3, 0x0,

    /* U+00D0 "Ð" */
    0x7e, 0x1f, 0xc6, 0x19, 0x83, 0x60, 0xfe, 0x3f,
    0x8d, 0x83, 0x60, 0xd8, 0x67, 0xf1, 0xf8,

    /* U+00D1 "Ñ" */
    0x3f, 0x1f, 0x0, 0x18, 0x3e, 0x1f, 0x8f, 0xc7,
    0xf3, 0xd9, 0xe6, 0xf3, 0xf8, 0xfc, 0x7e, 0x1f,
    0x6,

    /* U+00D2 "Ò" */
    0x38, 0x7, 0x0, 0x0, 0x78, 0x7f, 0x98, 0x6c,
    0xf, 0x3, 0xc0, 0xf0, 0x3c, 0xf, 0x3, 0x61,
    0x9f, 0xe1, 0xe0,

    /* U+00D3 "Ó" */
    0x7, 0x3, 0x80, 0x0, 0x78, 0x7f, 0x98, 0x6c,
    0xf, 0x3, 0xc0, 0xf0, 0x3c, 0xf, 0x3, 0x61,
    0x9f, 0xe1, 0xe0,

    /* U+00D4 "Ô" */
    0x1c, 0xc, 0xc0, 0x0, 0x78, 0x7f, 0x98, 0x6c,
    0xf, 0x3, 0xc0, 0xf0, 0x3c, 0xf, 0x3, 0x61,
    0x9f, 0xe1, 0xe0,

    /* U+00D5 "Õ" */
    0x3f, 0xf, 0xc0, 0x0, 0x78, 0x7f, 0x98, 0x6c,
    0xf, 0x3, 0xc0, 0xf0, 0x3c, 0xf, 0x3, 0x61,
    0x9f, 0xe1, 0xe0,

    /* U+00D6 "Ö" */
    0x33, 0xc, 0xc0, 0x0, 0x78, 0x7f, 0x98, 0x6c,
    0xf, 0x3, 0xc0, 0xf0, 0x3c, 0xf, 0x3, 0x61,
    0x9f, 0xe1, 0xe0,

    /* U+00D7 "×" */
    0xc7, 0xd9, 0xe1, 0xc7, 0xdd, 0xb1, 0x0,

    /* U+00D8 "Ø" */
    0x1e, 0x9f, 0xe6, 0x1b, 0xb, 0xc2, 0xf1, 0x3c,
    0x8f, 0x23, 0xd0, 0xdc, 0x67, 0xf9, 0x78, 0xc0,
    0x0,

    /* U+00D9 "Ù" */
    0x30, 0xc, 0x0, 0x18, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x3e, 0x3b, 0xf8,
    0xf8,

    /* U+00DA "Ú" */
    0x6, 0x6, 0x0, 0x18, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x3e, 0x3b, 0xf8,
    0xf8,

    /* U+00DB "Û" */
    0x1c, 0x1b, 0x0, 0x18, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x3e, 0x3b, 0xf8,
    0xf8,

    /* U+00DC "Ü" */
    0x66, 0x33, 0x0, 0x18, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x3e, 0x3b, 0xf8,
    0xf8,

    /* U+00DD "Ý" */
    0x6, 0x3, 0x0, 0x3, 0x87, 0x61, 0x9c, 0xe3,
    0x30, 0xfc, 0x1e, 0x7, 0x80, 0xc0, 0x30, 0xc,
    0x3, 0x0, 0xc0,

    /* U+00DE "Þ" */
    0xc0, 0xc0, 0xfc, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7,
    0xfe, 0xfc, 0xc0, 0xc0,

    /* U+00DF "ß" */
    0x3c, 0xfe, 0xc6, 0xc6, 0xcc, 0xcc, 0xcc, 0xc6,
    0xc3, 0xc3, 0xdf, 0xde,

    /* U+00E0 "à" */
    0x70, 0x70, 0x3, 0xef, 0xf8, 0xdf, 0xff, 0xc7,
    0x8f, 0xfb, 0xb0,

    /* U+00E1 "á" */
    0xc, 0x30, 0x3, 0xef, 0xf8, 0xdf, 0xff, 0xc7,
    0x8f, 0xfb, 0xb0,

    /* U+00E2 "â" */
    0x38, 0xd8, 0x3, 0xef, 0xf8, 0xdf, 0xff, 0xc7,
    0x8f, 0xfb, 0xb0,

    /* U+00E3 "ã" */
    0x7e, 0xf8, 0x3, 0xef, 0xf8, 0xdf, 0xff, 0xc7,
    0x8f, 0xfb, 0xb0,

    /* U+00E4 "ä" */
    0x66, 0xcc, 0x3, 0xef, 0xf8, 0xcf, 0xff, 0xc7,
    0x8f, 0xfb, 0xf0,

    /* U+00E5 "å" */
    0x38, 0x50, 0xe0, 0x7, 0xdf, 0xf1, 0xbf, 0xff,
    0x8f, 0x1f, 0xf7, 0x60,

    /* U+00E6 "æ" */
    0x3d, 0xef, 0xfe, 0xc7, 0x37, 0xff, 0xff, 0xfc,
    0x60, 0xc7, 0xf, 0xff, 0x79, 0xe0,

    /* U+00E7 "ç" */
    0x3c, 0x7e, 0xe6, 0xc0, 0xc0, 0xc7, 0xe6, 0x7e,
    0x3c, 0x18, 0x1c, 0x18,

    /* U+00E8 "è" */
    0x70, 0x38, 0x0, 0x3c, 0x7e, 0xe3, 0xff, 0xff,
    0xc0, 0xe2, 0x7f, 0x3e,

    /* U+00E9 "é" */
    0xc, 0x18, 0x0, 0x3c, 0x7e, 0xe3, 0xff, 0xff,
    0xc0, 0xe2, 0x7f, 0x3e,

    /* U+00EA "ê" */
    0x38, 0x66, 0x0, 0x3c, 0x7e, 0xe3, 0xff, 0xff,
    0xc0, 0xe2, 0x7f, 0x3e,

    /* U+00EB "ë" */
    0x66, 0x66, 0x0, 0x3c, 0x7e, 0xe3, 0xff, 0xff,
    0xc0, 0xe2, 0x7f, 0x3c,

    /* U+00EC "ì" */
    0x63, 0x3, 0x33, 0x33, 0x33, 0x33,

    /* U+00ED "í" */
    0x6c, 0xc, 0xcc, 0xcc, 0xcc, 0xcc,

    /* U+00EE "î" */
    0x31, 0x20, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0xc,

    /* U+00EF "ï" */
    0xcf, 0x30, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0xc,

    /* U+00F0 "ð" */
    0x60, 0x7e, 0x1c, 0x3e, 0x6, 0x3b, 0x7f, 0xe3,
    0xc3, 0xc3, 0xe7, 0x7e, 0x3c,

    /* U+00F1 "ñ" */
    0x7c, 0xf8, 0x6, 0xef, 0xf8, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x30,

    /* U+00F2 "ò" */
    0x30, 0x18, 0x0, 0x3c, 0x7e, 0xe7, 0xc3, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3c,

    /* U+00F3 "ó" */
    0xc, 0x18, 0x0, 0x3c, 0x7e, 0xe7, 0xc3, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3c,

    /* U+00F4 "ô" */
    0x18, 0x66, 0x0, 0x3c, 0x7e, 0xe7, 0xc3, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3c,

    /* U+00F5 "õ" */
    0x3e, 0x7c, 0x0, 0x3c, 0x7e, 0xe7, 0xc3, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3c,

    /* U+00F6 "ö" */
    0x66, 0x66, 0x0, 0x3c, 0x7e, 0xe7, 0xc3, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3c,

    /* U+00F7 "÷" */
    0x18, 0x18, 0x0, 0xff, 0xff, 0x0, 0x0, 0x18,
    0x18,

    /* U+00F8 "ø" */
    0x2, 0x3e, 0x7e, 0xef, 0xcb, 0xdb, 0xd3, 0xf7,
    0x7e, 0x7c, 0x40,

    /* U+00F9 "ù" */
    0x60, 0x60, 0x6, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0xfb, 0xb0,

    /* U+00FA "ú" */
    0xc, 0x30, 0x6, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0xfb, 0xb0,

    /* U+00FB "û" */
    0x38, 0xd8, 0x6, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0xfb, 0xb0,

    /* U+00FC "ü" */
    0x66, 0xcc, 0x6, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0xfb, 0xf0,

    /* U+00FD "ý" */
    0xe, 0x18, 0x0, 0xe3, 0x67, 0x66, 0x76, 0x3e,
    0x3c, 0x3c, 0x1c, 0x18, 0x18, 0x70, 0x70,

    /* U+00FE "þ" */
    0xc1, 0x83, 0x7, 0xef, 0xd9, 0xf1, 0xe3, 0xc7,
    0x9f, 0xf7, 0xcc, 0x18, 0x30, 0x0,

    /* U+00FF "ÿ" */
    0x66, 0x66, 0x0, 0xc7, 0x66, 0x66, 0x66, 0x3c,
    0x3c, 0x3c, 0x18, 0x18, 0x18, 0x70, 0x70,

    /* U+2000 " " */
    0x0,

    /* U+2001 " " */
    0x0,

    /* U+2002 " " */
    0x0,

    /* U+2003 " " */
    0x0,

    /* U+2004 " " */
    0x0,

    /* U+2005 " " */
    0x0,

    /* U+2006 " " */
    0x0,

    /* U+2007 " " */
    0x0,

    /* U+2008 " " */
    0x0,

    /* U+2009 " " */
    0x0,

    /* U+200A " " */
    0x0,

    /* U+200B "​" */
    0x0,

    /* U+2010 "‐" */
    0xff,

    /* U+2011 "‑" */
    0xff,

    /* U+2013 "–" */
    0xff, 0xff,

    /* U+2014 "—" */
    0xff, 0xff, 0xfc,

    /* U+2015 "―" */
    0xff, 0xff, 0xfc,

    /* U+2017 "‗" */
    0xfe, 0x3, 0xf8,

    /* U+2018 "‘" */
    0x7b, 0x60,

    /* U+2019 "’" */
    0x6d, 0xe0,

    /* U+201A "‚" */
    0x6d, 0xe0,

    /* U+201B "‛" */
    0xdb, 0x30,

    /* U+201C "“" */
    0x6f, 0x6d, 0xb6,

    /* U+201D "”" */
    0x6d, 0xb6, 0xf6,

    /* U+201E "„" */
    0x6d, 0xb6, 0xd2, 0x48,

    /* U+2020 "†" */
    0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18,

    /* U+2021 "‡" */
    0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18,
    0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18,

    /* U+2022 "•" */
    0x6f, 0xf6,

    /* U+2025 "‥" */
    0xcf, 0x30,

    /* U+2026 "…" */
    0xcc, 0xf3, 0x30,

    /* U+2027 "‧" */
    0xf0,

    /* U+2030 "‰" */
    0x70, 0x3, 0xe0, 0xd, 0x90, 0x36, 0xc0, 0xfa,
    0x1, 0xd0, 0x0, 0xfb, 0x83, 0xff, 0x16, 0x4c,
    0x99, 0x30, 0x7f, 0xc0, 0xee,

    /* U+2032 "′" */
    0xff,

    /* U+2033 "″" */
    0xff, 0xff,

    /* U+2039 "‹" */
    0x2f, 0x26, 0x40,

    /* U+203A "›" */
    0x89, 0xbd, 0x0,

    /* U+203C "‼" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0x0, 0xc,
    0xf3,

    /* U+2044 "⁄" */
    0x0, 0x8, 0x30, 0x41, 0x82, 0xc, 0x30, 0x41,
    0x80,

    /* U+20A3 "₣" */
    0x7f, 0xbf, 0xd8, 0xc, 0x6, 0x3, 0xf9, 0xfc,
    0xc0, 0xf8, 0x7c, 0x18, 0xc, 0x0,

    /* U+20A4 "₤" */
    0x1e, 0x3f, 0x67, 0x60, 0xf8, 0xf8, 0x60, 0xf8,
    0xf8, 0x60, 0xff, 0xff,

    /* U+20A6 "₦" */
    0x30, 0x61, 0xc3, 0xf, 0x18, 0x78, 0xcf, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x31, 0xe1, 0x8f,
    0xc, 0x38, 0x60, 0xc0,

    /* U+20A7 "₧" */
    0xfc, 0xf, 0xec, 0xcf, 0xcc, 0x7f, 0xc7, 0xfc,
    0xfc, 0xfe, 0xcf, 0xcc, 0xc0, 0xcc, 0xc, 0xc0,
    0xfc, 0x7,

    /* U+20A8 "₨" */
    0xfc, 0x0, 0xfe, 0x0, 0xc7, 0x0, 0xc3, 0x3c,
    0xc3, 0x7f, 0xc7, 0x67, 0xfe, 0x70, 0xfc, 0x3e,
    0xce, 0x7, 0xc7, 0x63, 0xc7, 0x7f, 0xc3, 0xbe,

    /* U+20A9 "₩" */
    0x63, 0x36, 0x33, 0xff, 0xff, 0xff, 0x37, 0xaf,
    0xff, 0xff, 0xf3, 0xfe, 0x3f, 0xe3, 0xce, 0x1c,
    0xe1, 0xce,

    /* U+20AA "₪" */
    0xff, 0x3f, 0xfb, 0xc1, 0xbc, 0xdb, 0xcd, 0xbc,
    0xdb, 0xcc, 0x3c, 0xfe, 0xcf, 0xc0,

    /* U+20AB "₫" */
    0x1f, 0x8f, 0xc0, 0xc7, 0x67, 0xf7, 0x1b, 0xd,
    0x86, 0xc3, 0x71, 0x9f, 0xc7, 0x60, 0x3, 0xf9,
    0xfc,

    /* U+20AC "€" */
    0x1e, 0x7d, 0xc3, 0xf, 0xcc, 0x3f, 0x30, 0x60,
    0xe0, 0xf8, 0xf0,

    /* U+20B1 "₱" */
    0x7f, 0xf, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xdf, 0xe3, 0xf8, 0x60, 0xc, 0x1, 0x80, 0x30,
    0x0,

    /* U+20B9 "₹" */
    0x7f, 0x1c, 0x7f, 0xff, 0xc, 0x7c, 0x78, 0x70,
    0x38, 0x1c, 0xe,

    /* U+20BA "₺" */
    0x30, 0x1e, 0xf, 0x1e, 0xb, 0xc3, 0xc3, 0xc6,
    0x63, 0x31, 0x99, 0x8f, 0xc7, 0x80,

    /* U+20BC "₼" */
    0xc, 0x3, 0x1, 0xe1, 0xfe, 0x6d, 0xb3, 0x3c,
    0xcf, 0x33, 0xcc, 0xc0,

    /* U+20BD "₽" */
    0x3f, 0xf, 0xe3, 0x18, 0xc3, 0x30, 0xcc, 0x6f,
    0xfb, 0xfc, 0xfc, 0x3f, 0x3, 0x0, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 64, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 69, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 82, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 6, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 147, .box_w = 8, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 36, .adv_w = 189, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 168, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 41, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 69, .adv_w = 90, .box_w = 4, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 78, .adv_w = 90, .box_w = 4, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 87, .adv_w = 116, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 94, .adv_w = 140, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 104, .adv_w = 63, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 106, .adv_w = 101, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 107, .adv_w = 74, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 95, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 118, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 130, .adv_w = 147, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 147, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 72, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 67, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 241, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 248, .adv_w = 147, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 253, .adv_w = 132, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 260, .adv_w = 127, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 230, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 297, .adv_w = 172, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 163, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 168, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 166, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 141, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 175, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 181, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 75, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 163, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 139, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 224, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 181, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 177, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 493, .adv_w = 165, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 177, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 525, .adv_w = 164, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 159, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 566, .adv_w = 169, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 580, .adv_w = 167, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 595, .adv_w = 224, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 163, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 159, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 155, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 660, .adv_w = 71, .box_w = 3, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 667, .adv_w = 108, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 679, .adv_w = 71, .box_w = 3, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 686, .adv_w = 112, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 692, .adv_w = 114, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 694, .adv_w = 85, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 10},
    {.bitmap_index = 695, .adv_w = 137, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 703, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 714, .adv_w = 133, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 723, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 734, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 92, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 752, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 764, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 775, .adv_w = 68, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 778, .adv_w = 67, .box_w = 4, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 786, .adv_w = 137, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 798, .adv_w = 68, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 801, .adv_w = 222, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 815, .adv_w = 144, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 823, .adv_w = 145, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 843, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 854, .adv_w = 94, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 860, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 868, .adv_w = 87, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 875, .adv_w = 143, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 883, .adv_w = 130, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 894, .adv_w = 188, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 907, .adv_w = 130, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 916, .adv_w = 129, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 928, .adv_w = 130, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 936, .adv_w = 84, .box_w = 5, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 947, .adv_w = 65, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 951, .adv_w = 84, .box_w = 5, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 962, .adv_w = 166, .box_w = 9, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 967, .adv_w = 64, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 968, .adv_w = 72, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 971, .adv_w = 148, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 984, .adv_w = 152, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 996, .adv_w = 177, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1009, .adv_w = 137, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1021, .adv_w = 64, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1025, .adv_w = 161, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1040, .adv_w = 120, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 1042, .adv_w = 201, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1059, .adv_w = 114, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1064, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1069, .adv_w = 141, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1073, .adv_w = 101, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1074, .adv_w = 201, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1091, .adv_w = 128, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 1093, .adv_w = 100, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1095, .adv_w = 138, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1105, .adv_w = 95, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1109, .adv_w = 95, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1113, .adv_w = 85, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 1114, .adv_w = 158, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1125, .adv_w = 125, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1136, .adv_w = 77, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1137, .adv_w = 69, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1139, .adv_w = 95, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1142, .adv_w = 117, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1147, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1152, .adv_w = 183, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1169, .adv_w = 194, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1186, .adv_w = 207, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1206, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1217, .adv_w = 172, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1238, .adv_w = 172, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1259, .adv_w = 172, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1280, .adv_w = 172, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1301, .adv_w = 172, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1320, .adv_w = 172, .box_w = 11, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1342, .adv_w = 240, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1363, .adv_w = 168, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1380, .adv_w = 144, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1395, .adv_w = 144, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1410, .adv_w = 144, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1425, .adv_w = 144, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1440, .adv_w = 75, .box_w = 4, .box_h = 15, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1448, .adv_w = 75, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1456, .adv_w = 75, .box_w = 6, .box_h = 15, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1468, .adv_w = 75, .box_w = 6, .box_h = 15, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1480, .adv_w = 170, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1495, .adv_w = 181, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1512, .adv_w = 177, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1531, .adv_w = 177, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1550, .adv_w = 177, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1569, .adv_w = 177, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1588, .adv_w = 177, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1607, .adv_w = 136, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1614, .adv_w = 176, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1631, .adv_w = 169, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1648, .adv_w = 169, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1665, .adv_w = 169, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1682, .adv_w = 169, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1699, .adv_w = 159, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1718, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1730, .adv_w = 162, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1742, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1753, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1764, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1775, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1786, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1797, .adv_w = 137, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1809, .adv_w = 216, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1823, .adv_w = 133, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1835, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1847, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1859, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1871, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1883, .adv_w = 70, .box_w = 4, .box_h = 12, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1889, .adv_w = 70, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1895, .adv_w = 70, .box_w = 6, .box_h = 12, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1904, .adv_w = 70, .box_w = 6, .box_h = 12, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1913, .adv_w = 147, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1926, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1937, .adv_w = 145, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1949, .adv_w = 145, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1961, .adv_w = 145, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1973, .adv_w = 145, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1985, .adv_w = 145, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1997, .adv_w = 146, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2006, .adv_w = 144, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2017, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2028, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2039, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2050, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2061, .adv_w = 129, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2076, .adv_w = 145, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2090, .adv_w = 129, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2105, .adv_w = 131, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2106, .adv_w = 261, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2107, .adv_w = 131, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2108, .adv_w = 261, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2109, .adv_w = 87, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2110, .adv_w = 65, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2111, .adv_w = 44, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2112, .adv_w = 144, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2113, .adv_w = 70, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2114, .adv_w = 52, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2115, .adv_w = 26, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2116, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2117, .adv_w = 101, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 2118, .adv_w = 101, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 2119, .adv_w = 161, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 2121, .adv_w = 195, .box_w = 11, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 2124, .adv_w = 195, .box_w = 11, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 2127, .adv_w = 114, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2130, .adv_w = 60, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 2132, .adv_w = 59, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 2134, .adv_w = 64, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2136, .adv_w = 53, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 2138, .adv_w = 103, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 2141, .adv_w = 104, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 2144, .adv_w = 103, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2148, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2160, .adv_w = 148, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2175, .adv_w = 92, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 2177, .adv_w = 134, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2179, .adv_w = 190, .box_w = 10, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2182, .adv_w = 66, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 2183, .adv_w = 246, .box_w = 14, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2204, .adv_w = 41, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 2205, .adv_w = 82, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 2207, .adv_w = 80, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2210, .adv_w = 77, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2213, .adv_w = 138, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2222, .adv_w = 114, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2231, .adv_w = 141, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2245, .adv_w = 152, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2257, .adv_w = 208, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2277, .adv_w = 221, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2295, .adv_w = 278, .box_w = 16, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2319, .adv_w = 208, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2337, .adv_w = 223, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2351, .adv_w = 148, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2368, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2379, .adv_w = 191, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2396, .adv_w = 135, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2407, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2421, .adv_w = 175, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2433, .adv_w = 181, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_3[] = {
    0x0, 0x1, 0x3, 0x4, 0x5, 0x7, 0x8, 0x9,
    0xa, 0xb, 0xc, 0xd, 0xe, 0x10, 0x11, 0x12,
    0x15, 0x16, 0x17, 0x20, 0x22, 0x23, 0x29, 0x2a,
    0x2c, 0x34, 0x93, 0x94, 0x96, 0x97, 0x98, 0x99,
    0x9a, 0x9b, 0x9c, 0xa1, 0xa9, 0xaa, 0xac, 0xad
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 160, .range_length = 96, .glyph_id_start = 96,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 8192, .range_length = 12, .glyph_id_start = 192,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 8208, .range_length = 174, .glyph_id_start = 204,
        .unicode_list = unicode_list_3, .glyph_id_ofs_list = NULL, .list_length = 40, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    3, 3,
    3, 8,
    3, 210,
    3, 211,
    3, 213,
    3, 214,
    3, 215,
    3, 224,
    3, 225,
    8, 3,
    8, 8,
    8, 210,
    8, 211,
    8, 213,
    8, 214,
    8, 215,
    8, 224,
    8, 225,
    13, 3,
    13, 8,
    13, 210,
    13, 211,
    13, 213,
    13, 214,
    13, 215,
    13, 224,
    13, 225,
    15, 3,
    15, 8,
    15, 210,
    15, 211,
    15, 213,
    15, 214,
    15, 215,
    15, 224,
    15, 225,
    16, 16,
    210, 3,
    210, 8,
    210, 210,
    210, 211,
    210, 213,
    210, 214,
    210, 215,
    210, 224,
    210, 225,
    211, 3,
    211, 8,
    211, 210,
    211, 211,
    211, 213,
    211, 214,
    211, 215,
    211, 224,
    211, 225,
    212, 3,
    212, 8,
    212, 210,
    212, 211,
    212, 213,
    212, 214,
    212, 215,
    212, 224,
    212, 225,
    213, 3,
    213, 8,
    213, 210,
    213, 211,
    213, 213,
    213, 214,
    213, 215,
    213, 224,
    213, 225,
    214, 3,
    214, 8,
    214, 210,
    214, 211,
    214, 213,
    214, 214,
    214, 215,
    214, 224,
    214, 225,
    215, 3,
    215, 8,
    215, 210,
    215, 211,
    215, 213,
    215, 214,
    215, 215,
    215, 224,
    215, 225,
    216, 3,
    216, 8,
    216, 210,
    216, 211,
    216, 213,
    216, 214,
    216, 215,
    216, 224,
    216, 225,
    220, 3,
    220, 8,
    220, 210,
    220, 211,
    220, 213,
    220, 214,
    220, 215,
    220, 224,
    220, 225,
    221, 3,
    221, 8,
    221, 210,
    221, 211,
    221, 213,
    221, 214,
    221, 215,
    221, 224,
    221, 225,
    224, 3,
    224, 8,
    224, 210,
    224, 211,
    224, 213,
    224, 214,
    224, 215,
    224, 224,
    224, 225,
    225, 3,
    225, 8,
    225, 210,
    225, 211,
    225, 213,
    225, 214,
    225, 215,
    225, 224,
    225, 225
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -31, -31, -31, -31, -31, -31,
    -31, -31, -31, -31, -31, -31, -31, -31,
    -31, -31, -31, -31, -30, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -31,
    -31, -31, -31, -31, -31, -31, -31, -31,
    -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -31, -31, -31, -31, -31,
    -31, -31, -31, -31, -31, -31, -31, -31,
    -31, -31, -31, -31, -31, -31, -31, -31,
    -31, -31, -31, -31, -31, -31, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 136,
    .glyph_ids_size = 0
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
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 4,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};

extern const lv_font_t roboto_bold_16;


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t roboto_bold_16 = {
#else
lv_font_t roboto_bold_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 20,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &roboto_bold_16,
#endif
    .user_data = NULL,
};



#endif /*#if ROBOTO_BOLD_16*/
