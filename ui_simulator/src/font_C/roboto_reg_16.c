/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --no-compress --stride 1 --align 1 --font Roboto-Regular.ttf --range 32-127,160-255,8352-8399,8192-8303 --format lvgl -o roboto_reg_16.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef ROBOTO_REG_16
#define ROBOTO_REG_16 1
#endif

#if ROBOTO_REG_16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0x10,

    /* U+0022 "\"" */
    0xb6, 0xd0,

    /* U+0023 "#" */
    0x9, 0x9, 0x4, 0x8f, 0xf1, 0x20, 0x90, 0x48,
    0x48, 0xff, 0x12, 0x9, 0x4, 0x80,

    /* U+0024 "$" */
    0x10, 0x20, 0xf3, 0xf4, 0x28, 0x50, 0x18, 0xc,
    0x6, 0xc, 0x17, 0xe7, 0x84, 0x8,

    /* U+0025 "%" */
    0x70, 0x22, 0x48, 0x92, 0x28, 0x72, 0x1, 0x0,
    0xd8, 0x29, 0x12, 0x4c, 0x92, 0x24, 0x6,

    /* U+0026 "&" */
    0x38, 0x22, 0x11, 0x8, 0x87, 0x81, 0x81, 0xc1,
    0x92, 0x8d, 0x43, 0x31, 0xcf, 0xa0,

    /* U+0027 "'" */
    0xf0,

    /* U+0028 "(" */
    0x32, 0x44, 0x88, 0x88, 0x88, 0x88, 0x44, 0x42,
    0x0,

    /* U+0029 ")" */
    0xc4, 0x22, 0x11, 0x11, 0x11, 0x11, 0x22, 0x64,
    0x0,

    /* U+002A "*" */
    0x10, 0x23, 0x53, 0xe3, 0x85, 0x0, 0x0,

    /* U+002B "+" */
    0x10, 0x20, 0x40, 0x8f, 0xe2, 0x4, 0x8, 0x10,

    /* U+002C "," */
    0x56,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x4, 0x30, 0x82, 0x18, 0x41, 0x8, 0x21, 0x84,
    0x10, 0xc0,

    /* U+0030 "0" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x5, 0x11, 0xc0,

    /* U+0031 "1" */
    0x1f, 0x91, 0x11, 0x11, 0x11, 0x11,

    /* U+0032 "2" */
    0x3c, 0x8e, 0xc, 0x10, 0x20, 0x83, 0xc, 0x30,
    0xc1, 0x7, 0xf0,

    /* U+0033 "3" */
    0x7d, 0x8e, 0x8, 0x10, 0xe7, 0x83, 0x81, 0x3,
    0x7, 0x13, 0xc0,

    /* U+0034 "4" */
    0x4, 0xc, 0x1c, 0x14, 0x24, 0x24, 0x44, 0xc4,
    0xff, 0x4, 0x4, 0x4,

    /* U+0035 "5" */
    0x7e, 0x81, 0x2, 0x7, 0xc8, 0x80, 0x81, 0x3,
    0x85, 0x11, 0xc0,

    /* U+0036 "6" */
    0x1c, 0x41, 0x4, 0xb, 0x98, 0xa0, 0xc1, 0x83,
    0x5, 0x11, 0xc0,

    /* U+0037 "7" */
    0xff, 0x3, 0x2, 0x6, 0x4, 0xc, 0x8, 0x18,
    0x18, 0x10, 0x30, 0x20,

    /* U+0038 "8" */
    0x79, 0x8e, 0xc, 0x1c, 0x6f, 0x11, 0x41, 0x83,
    0x5, 0x11, 0xc0,

    /* U+0039 "9" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0xbd, 0x2,
    0x8, 0x33, 0x80,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0,

    /* U+003B ";" */
    0x6c, 0x0, 0x3, 0x6d, 0x20,

    /* U+003C "<" */
    0x6, 0x3d, 0xc6, 0xe, 0x7, 0x81, 0x80,

    /* U+003D "=" */
    0xfe, 0x0, 0x0, 0xf, 0xe0,

    /* U+003E ">" */
    0x81, 0xc0, 0xe0, 0x31, 0xce, 0x30, 0x0,

    /* U+003F "?" */
    0x7b, 0x38, 0x41, 0xc, 0x21, 0x8, 0x20, 0x0,
    0x8,

    /* U+0040 "@" */
    0xf, 0x80, 0x83, 0x8, 0x4, 0x87, 0x24, 0x48,
    0xc4, 0x46, 0x22, 0x31, 0x11, 0x88, 0x8c, 0x4c,
    0x62, 0x64, 0x9d, 0xc4, 0x0, 0x18, 0x0, 0x3e,
    0x0,

    /* U+0041 "A" */
    0xc, 0x3, 0x80, 0xe0, 0x68, 0x1b, 0x4, 0xc3,
    0x10, 0x84, 0x7f, 0x98, 0x64, 0xb, 0x3,

    /* U+0042 "B" */
    0xfd, 0xe, 0xc, 0x18, 0x7f, 0x21, 0xc1, 0x83,
    0x6, 0x1f, 0xe0,

    /* U+0043 "C" */
    0x3c, 0x42, 0x43, 0x81, 0x80, 0x80, 0x80, 0x80,
    0x81, 0x43, 0x42, 0x3c,

    /* U+0044 "D" */
    0xf8, 0x86, 0x82, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x81, 0x82, 0x86, 0xf8,

    /* U+0045 "E" */
    0xff, 0x2, 0x4, 0x8, 0x1f, 0xa0, 0x40, 0x81,
    0x2, 0x7, 0xf0,

    /* U+0046 "F" */
    0xff, 0x2, 0x4, 0x8, 0x10, 0x3f, 0x40, 0x81,
    0x2, 0x4, 0x0,

    /* U+0047 "G" */
    0x3e, 0x30, 0x90, 0x30, 0x8, 0x4, 0x2, 0x1f,
    0x1, 0x80, 0xa0, 0x58, 0x63, 0xe0,

    /* U+0048 "H" */
    0x81, 0x81, 0x81, 0x81, 0x81, 0xff, 0x81, 0x81,
    0x81, 0x81, 0x81, 0x81,

    /* U+0049 "I" */
    0xff, 0xf0,

    /* U+004A "J" */
    0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x81, 0x3,
    0x7, 0x13, 0xc0,

    /* U+004B "K" */
    0x82, 0x86, 0x8c, 0x98, 0xb0, 0xf0, 0xf0, 0xd8,
    0x8c, 0x84, 0x86, 0x83,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x82, 0x8,
    0x3f,

    /* U+004D "M" */
    0xc0, 0x78, 0xf, 0x83, 0xd0, 0x5a, 0xb, 0x63,
    0x64, 0x4c, 0xd9, 0x8a, 0x31, 0x46, 0x38, 0xc2,
    0x10,

    /* U+004E "N" */
    0x80, 0xe0, 0x78, 0x36, 0x1b, 0xc, 0xc6, 0x33,
    0xd, 0x86, 0xc1, 0xe0, 0x70, 0x10,

    /* U+004F "O" */
    0x3e, 0x31, 0x90, 0x50, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80, 0xa0, 0x98, 0xc7, 0xc0,

    /* U+0050 "P" */
    0xfc, 0x82, 0x81, 0x81, 0x81, 0x82, 0xfc, 0x80,
    0x80, 0x80, 0x80, 0x80,

    /* U+0051 "Q" */
    0x3e, 0x31, 0x90, 0x50, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80, 0xa0, 0x98, 0xc7, 0xc0, 0x18, 0x4,

    /* U+0052 "R" */
    0xfc, 0x41, 0x20, 0x50, 0x28, 0x14, 0x13, 0xf1,
    0x18, 0x86, 0x41, 0x20, 0xd0, 0x20,

    /* U+0053 "S" */
    0x1c, 0x62, 0x41, 0x40, 0x60, 0x3c, 0xe, 0x3,
    0x1, 0x81, 0x43, 0x3c,

    /* U+0054 "T" */
    0xff, 0x84, 0x2, 0x1, 0x0, 0x80, 0x40, 0x20,
    0x10, 0x8, 0x4, 0x2, 0x1, 0x0,

    /* U+0055 "U" */
    0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x81, 0x81, 0x42, 0x3c,

    /* U+0056 "V" */
    0xc0, 0xd0, 0x26, 0x9, 0x86, 0x21, 0xc, 0x41,
    0x30, 0x48, 0x1a, 0x3, 0x80, 0xc0, 0x30,

    /* U+0057 "W" */
    0x43, 0xd, 0xc, 0x36, 0x30, 0x98, 0xe2, 0x26,
    0x98, 0x92, 0x62, 0x4d, 0xd, 0x14, 0x3c, 0x50,
    0x61, 0xc1, 0x86, 0x6, 0x8,

    /* U+0058 "X" */
    0x61, 0x98, 0x63, 0x30, 0x48, 0x1e, 0x3, 0x0,
    0xc0, 0x78, 0x13, 0xc, 0xc6, 0x19, 0x82,

    /* U+0059 "Y" */
    0xc1, 0xa0, 0x98, 0xc4, 0x43, 0x60, 0xa0, 0x70,
    0x10, 0x8, 0x4, 0x2, 0x1, 0x0,

    /* U+005A "Z" */
    0xff, 0x2, 0x6, 0x4, 0x8, 0x18, 0x10, 0x20,
    0x20, 0x40, 0x80, 0xff,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x49, 0x27,

    /* U+005C "\\" */
    0x41, 0x6, 0x8, 0x20, 0xc1, 0x4, 0x18, 0x20,
    0xc1, 0x4,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x92, 0x4f,

    /* U+005E "^" */
    0x10, 0xc2, 0x9a, 0x4d, 0x10,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0xc6, 0x20,

    /* U+0061 "a" */
    0x7b, 0x18, 0x41, 0x7f, 0x18, 0x63, 0x74,

    /* U+0062 "b" */
    0x81, 0x2, 0x5, 0xcc, 0x50, 0x60, 0xc1, 0x83,
    0x7, 0x15, 0xc0,

    /* U+0063 "c" */
    0x3c, 0x8e, 0x1c, 0x8, 0x10, 0x21, 0xa3, 0x3c,

    /* U+0064 "d" */
    0x2, 0x4, 0x9, 0xd4, 0x70, 0x60, 0xc1, 0x83,
    0x5, 0x19, 0xd0,

    /* U+0065 "e" */
    0x38, 0x8a, 0xc, 0x1f, 0xf0, 0x20, 0x23, 0x3c,

    /* U+0066 "f" */
    0x3a, 0x10, 0x8f, 0x21, 0x8, 0x42, 0x10, 0x84,
    0x0,

    /* U+0067 "g" */
    0x3a, 0x8e, 0xc, 0x18, 0x30, 0x60, 0xa3, 0x3a,
    0x7, 0x13, 0xc0,

    /* U+0068 "h" */
    0x82, 0x8, 0x2e, 0xc6, 0x18, 0x61, 0x86, 0x18,
    0x61,

    /* U+0069 "i" */
    0x9f, 0xf0,

    /* U+006A "j" */
    0x20, 0x12, 0x49, 0x24, 0x92, 0x70,

    /* U+006B "k" */
    0x81, 0x2, 0x4, 0x69, 0x96, 0x38, 0x70, 0xb1,
    0x32, 0x34, 0x60,

    /* U+006C "l" */
    0xff, 0xf0,

    /* U+006D "m" */
    0xb9, 0xec, 0x63, 0x84, 0x18, 0x41, 0x84, 0x18,
    0x41, 0x84, 0x18, 0x41, 0x84, 0x10,

    /* U+006E "n" */
    0xbb, 0x18, 0x61, 0x86, 0x18, 0x61, 0x84,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xa2, 0x38,

    /* U+0070 "p" */
    0xb9, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xe2, 0xb9,
    0x2, 0x4, 0x0,

    /* U+0071 "q" */
    0x3a, 0x8e, 0xc, 0x18, 0x30, 0x60, 0xa3, 0x3a,
    0x4, 0x8, 0x10,

    /* U+0072 "r" */
    0xbc, 0x88, 0x88, 0x88, 0x80,

    /* U+0073 "s" */
    0x3c, 0x8d, 0xb, 0x3, 0xc0, 0xd0, 0xa1, 0x3c,

    /* U+0074 "t" */
    0x21, 0x3e, 0x42, 0x10, 0x84, 0x21, 0xe,

    /* U+0075 "u" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x63, 0x74,

    /* U+0076 "v" */
    0xc2, 0x85, 0x9b, 0x22, 0x45, 0x8e, 0xc, 0x18,

    /* U+0077 "w" */
    0xc6, 0x34, 0x62, 0x46, 0x26, 0xf6, 0x29, 0x42,
    0x94, 0x29, 0x43, 0xc, 0x10, 0x80,

    /* U+0078 "x" */
    0x42, 0x66, 0x3c, 0x18, 0x18, 0x38, 0x2c, 0x66,
    0x42,

    /* U+0079 "y" */
    0xc2, 0x8d, 0x9b, 0x22, 0xc7, 0x8e, 0xc, 0x10,
    0x20, 0xc3, 0x0,

    /* U+007A "z" */
    0xfe, 0xc, 0x30, 0xc1, 0x6, 0x18, 0x60, 0xfe,

    /* U+007B "{" */
    0x19, 0x8, 0x42, 0x10, 0x98, 0x21, 0x8, 0x42,
    0x10, 0x40,

    /* U+007C "|" */
    0xff, 0xfc,

    /* U+007D "}" */
    0x2, 0x8, 0x42, 0x10, 0x86, 0x19, 0x88, 0x42,
    0x10, 0x88, 0x0,

    /* U+007E "~" */
    0x70, 0xe4, 0xe1, 0xc0,

    /* U+00A0 " " */
    0x0,

    /* U+00A1 "¡" */
    0x9f, 0xe0,

    /* U+00A2 "¢" */
    0x10, 0x20, 0xf3, 0xfc, 0x70, 0x20, 0x40, 0xc6,
    0xf8, 0xe0, 0x81, 0x0,

    /* U+00A3 "£" */
    0x1e, 0x23, 0x41, 0x40, 0x40, 0x40, 0xf8, 0x40,
    0x40, 0x40, 0x40, 0xff,

    /* U+00A4 "¤" */
    0x9c, 0x98, 0xe4, 0x12, 0x2, 0x80, 0xa0, 0x28,
    0x9, 0x4, 0xe3, 0xa7, 0x20,

    /* U+00A5 "¥" */
    0xc7, 0x8d, 0x13, 0x62, 0x87, 0x1f, 0x88, 0x7e,
    0x20, 0x40, 0x80,

    /* U+00A6 "¦" */
    0xfc, 0xfc,

    /* U+00A7 "§" */
    0x3c, 0x63, 0x41, 0x40, 0x70, 0x7c, 0xc6, 0x81,
    0x81, 0x61, 0x3e, 0x7, 0x1, 0x81, 0x43, 0x3e,

    /* U+00A8 "¨" */
    0x88,

    /* U+00A9 "©" */
    0x1f, 0x6, 0x31, 0x39, 0x68, 0xb9, 0x3, 0x20,
    0x64, 0xc, 0x89, 0xce, 0x68, 0x8, 0xc6, 0xf,
    0x80,

    /* U+00AA "ª" */
    0x72, 0x5e, 0x94, 0xbc,

    /* U+00AB "«" */
    0x29, 0x6d, 0x34, 0x48, 0xa0,

    /* U+00AC "¬" */
    0xfc, 0x10, 0x40,

    /* U+00AD "­" */
    0xf0,

    /* U+00AE "®" */
    0x1f, 0x6, 0x31, 0x79, 0x68, 0xb9, 0x13, 0x22,
    0x67, 0x8c, 0x89, 0xd1, 0x68, 0x8, 0xc6, 0xf,
    0x80,

    /* U+00AF "¯" */
    0xf8,

    /* U+00B0 "°" */
    0x69, 0x96,

    /* U+00B1 "±" */
    0x10, 0x20, 0x40, 0x8f, 0xe2, 0x4, 0x8, 0x10,
    0x3, 0xf8,

    /* U+00B2 "²" */
    0x74, 0xc6, 0x64, 0x7c,

    /* U+00B3 "³" */
    0x70, 0x4e, 0x14, 0xb8,

    /* U+00B4 "´" */
    0x6b, 0x0,

    /* U+00B5 "µ" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x73, 0xf6, 0x8,
    0x20,

    /* U+00B6 "¶" */
    0x3d, 0xf7, 0xff, 0x7d, 0xf3, 0xc1, 0x4, 0x10,
    0x41,

    /* U+00B7 "·" */
    0xf0,

    /* U+00B8 "¸" */
    0xb6,

    /* U+00B9 "¹" */
    0x74, 0x92, 0x40,

    /* U+00BA "º" */
    0x74, 0x63, 0x18, 0xb8,

    /* U+00BB "»" */
    0x91, 0x26, 0xdb, 0x4a, 0x40,

    /* U+00BC "¼" */
    0x60, 0x14, 0x10, 0x84, 0x11, 0x2, 0x20, 0x48,
    0x83, 0x30, 0x4a, 0x13, 0x42, 0x7c, 0x1, 0x0,
    0x20,

    /* U+00BD "½" */
    0x60, 0x14, 0x20, 0x88, 0x11, 0x2, 0x40, 0x53,
    0x82, 0x88, 0x81, 0x10, 0xc4, 0x30, 0xf, 0x80,

    /* U+00BE "¾" */
    0x70, 0x4, 0x84, 0x8, 0xc3, 0x88, 0x9, 0x4,
    0x90, 0x72, 0x20, 0x66, 0x4, 0xa0, 0x92, 0x9,
    0xf0, 0x2, 0x0, 0x20,

    /* U+00BF "¿" */
    0x10, 0x0, 0x0, 0x81, 0x4, 0x10, 0x40, 0x81,
    0xb, 0x33, 0xc0,

    /* U+00C0 "À" */
    0x18, 0x3, 0x0, 0x40, 0x30, 0xe, 0x3, 0x81,
    0xa0, 0x6c, 0x13, 0xc, 0x42, 0x11, 0xfe, 0x61,
    0x90, 0x2c, 0xc,

    /* U+00C1 "Á" */
    0x2, 0x1, 0x80, 0x40, 0x30, 0xe, 0x3, 0x81,
    0xa0, 0x6c, 0x13, 0xc, 0x42, 0x11, 0xfe, 0x61,
    0x90, 0x2c, 0xc,

    /* U+00C2 "Â" */
    0xc, 0x6, 0x80, 0x0, 0x30, 0xe, 0x3, 0x81,
    0xa0, 0x6c, 0x13, 0xc, 0x42, 0x11, 0xfe, 0x61,
    0x90, 0x2c, 0xc,

    /* U+00C3 "Ã" */
    0x19, 0xd, 0x80, 0x0, 0x30, 0xe, 0x3, 0x81,
    0xa0, 0x6c, 0x13, 0xc, 0x42, 0x11, 0xfe, 0x61,
    0x90, 0x2c, 0xc,

    /* U+00C4 "Ä" */
    0x12, 0x0, 0x0, 0xc0, 0x30, 0x1e, 0x6, 0x81,
    0xa0, 0xcc, 0x31, 0x8, 0x47, 0xf9, 0x86, 0x40,
    0xb0, 0x30,

    /* U+00C5 "Å" */
    0xc, 0x4, 0x81, 0x20, 0x30, 0xc, 0x3, 0x1,
    0xe0, 0x68, 0x1a, 0xc, 0xc3, 0x10, 0x84, 0x7f,
    0x98, 0x64, 0xb, 0x3,

    /* U+00C6 "Æ" */
    0x1, 0xfc, 0x7, 0x0, 0xa, 0x0, 0x34, 0x0,
    0x48, 0x1, 0x9f, 0x82, 0x20, 0xc, 0x40, 0x3f,
    0x80, 0x61, 0x1, 0x82, 0x3, 0x7, 0xf0,

    /* U+00C7 "Ç" */
    0x3e, 0x31, 0x90, 0x50, 0x38, 0x4, 0x2, 0x1,
    0x0, 0x81, 0xa0, 0x98, 0xc7, 0xc1, 0x80, 0x20,
    0x60,

    /* U+00C8 "È" */
    0x60, 0x40, 0x7, 0xf8, 0x10, 0x20, 0x40, 0xfd,
    0x2, 0x4, 0x8, 0x10, 0x3f, 0x80,

    /* U+00C9 "É" */
    0x18, 0x20, 0x7, 0xf8, 0x10, 0x20, 0x40, 0xfd,
    0x2, 0x4, 0x8, 0x10, 0x3f, 0x80,

    /* U+00CA "Ê" */
    0x30, 0x90, 0x7, 0xf8, 0x10, 0x20, 0x40, 0xfd,
    0x2, 0x4, 0x8, 0x10, 0x3f, 0x80,

    /* U+00CB "Ë" */
    0x44, 0x3, 0xfc, 0x8, 0x10, 0x20, 0x7e, 0x81,
    0x2, 0x4, 0x8, 0x1f, 0xc0,

    /* U+00CC "Ì" */
    0x44, 0x12, 0x49, 0x24, 0x92, 0x48,

    /* U+00CD "Í" */
    0x50, 0x49, 0x24, 0x92, 0x49, 0x20,

    /* U+00CE "Î" */
    0x22, 0x80, 0x42, 0x10, 0x84, 0x21, 0x8, 0x42,
    0x10, 0x80,

    /* U+00CF "Ï" */
    0x88, 0x8, 0x42, 0x10, 0x84, 0x21, 0x8, 0x42,
    0x10,

    /* U+00D0 "Ð" */
    0x7c, 0x21, 0x90, 0x48, 0x14, 0xf, 0xc5, 0x2,
    0x81, 0x40, 0xa0, 0x90, 0xcf, 0x80,

    /* U+00D1 "Ñ" */
    0x33, 0x27, 0x0, 0x10, 0x1c, 0xf, 0x6, 0xc3,
    0x61, 0x98, 0xc6, 0x61, 0xb0, 0xd8, 0x3c, 0xe,
    0x2,

    /* U+00D2 "Ò" */
    0x30, 0x8, 0x2, 0x0, 0x3, 0xe3, 0x19, 0x5,
    0x1, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xa, 0x9,
    0x8c, 0x7c,

    /* U+00D3 "Ó" */
    0x6, 0x2, 0x2, 0x0, 0x3, 0xe3, 0x19, 0x5,
    0x1, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xa, 0x9,
    0x8c, 0x7c,

    /* U+00D4 "Ô" */
    0x8, 0xe, 0xd, 0x80, 0x3, 0xe3, 0x19, 0x5,
    0x1, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xa, 0x9,
    0x8c, 0x7c,

    /* U+00D5 "Õ" */
    0x3b, 0x37, 0x0, 0x7, 0xc6, 0x32, 0xa, 0x3,
    0x1, 0x80, 0xc0, 0x60, 0x30, 0x14, 0x13, 0x18,
    0xf8,

    /* U+00D6 "Ö" */
    0x22, 0x0, 0xf, 0x8c, 0x64, 0x14, 0x6, 0x3,
    0x1, 0x80, 0xc0, 0x60, 0x28, 0x26, 0x31, 0xf0,

    /* U+00D7 "×" */
    0x85, 0x99, 0xe1, 0x87, 0x99, 0xa1, 0x80,

    /* U+00D8 "Ø" */
    0x3e, 0xb1, 0x90, 0x50, 0x58, 0x4c, 0x26, 0x23,
    0x21, 0x90, 0xb0, 0x98, 0xcf, 0xc8, 0x0,

    /* U+00D9 "Ù" */
    0x30, 0x18, 0x0, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x81, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3c,

    /* U+00DA "Ú" */
    0xc, 0x8, 0x0, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x81, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3c,

    /* U+00DB "Û" */
    0x18, 0x24, 0x0, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x81, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3c,

    /* U+00DC "Ü" */
    0x24, 0x0, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x81, 0x81, 0x81, 0x81, 0x42, 0x3c,

    /* U+00DD "Ý" */
    0x4, 0x6, 0x2, 0x18, 0x34, 0x13, 0x18, 0x88,
    0x6c, 0x14, 0xe, 0x2, 0x1, 0x0, 0x80, 0x40,
    0x20,

    /* U+00DE "Þ" */
    0x81, 0x2, 0x7, 0xe8, 0x70, 0x60, 0xc3, 0xfd,
    0x2, 0x4, 0x0,

    /* U+00DF "ß" */
    0x78, 0xc4, 0x84, 0x84, 0x88, 0x88, 0x88, 0x86,
    0x83, 0x81, 0x81, 0xbe,

    /* U+00E0 "à" */
    0x60, 0xc0, 0x1e, 0xc6, 0x10, 0x5f, 0xc6, 0x18,
    0xdd,

    /* U+00E1 "á" */
    0x8, 0x40, 0x1e, 0xc6, 0x10, 0x5f, 0xc6, 0x18,
    0xdd,

    /* U+00E2 "â" */
    0x31, 0xa0, 0x1e, 0xc6, 0x10, 0x5f, 0xc6, 0x18,
    0xdd,

    /* U+00E3 "ã" */
    0x7c, 0x0, 0x1e, 0xc6, 0x10, 0x5f, 0xc6, 0x18,
    0xdd,

    /* U+00E4 "ä" */
    0x24, 0x0, 0xe, 0x67, 0x10, 0x5f, 0xc7, 0x1c,
    0xdf,

    /* U+00E5 "å" */
    0x10, 0xa2, 0x8e, 0x1, 0xec, 0x61, 0x5, 0xfc,
    0x61, 0x8d, 0xd0,

    /* U+00E6 "æ" */
    0x79, 0xcc, 0xe2, 0x84, 0x10, 0x41, 0x7f, 0xfc,
    0x40, 0x84, 0x8, 0xe1, 0x79, 0xe0,

    /* U+00E7 "ç" */
    0x3c, 0x8e, 0xc, 0x8, 0x10, 0x20, 0xa3, 0x3c,
    0x20, 0x21, 0x80,

    /* U+00E8 "è" */
    0x60, 0x20, 0x1, 0xc4, 0x50, 0x60, 0xff, 0x81,
    0x1, 0x19, 0xe0,

    /* U+00E9 "é" */
    0xc, 0x30, 0x1, 0xc4, 0x50, 0x60, 0xff, 0x81,
    0x1, 0x19, 0xe0,

    /* U+00EA "ê" */
    0x38, 0xd8, 0x1, 0xc4, 0x50, 0x60, 0xff, 0x81,
    0x1, 0x19, 0xe0,

    /* U+00EB "ë" */
    0x24, 0x0, 0x1, 0xc6, 0x58, 0x70, 0xff, 0xc1,
    0x81, 0x99, 0xe0,

    /* U+00EC "ì" */
    0x44, 0x12, 0x49, 0x24, 0x90,

    /* U+00ED "í" */
    0x50, 0x49, 0x24, 0x92, 0x40,

    /* U+00EE "î" */
    0x22, 0x80, 0x42, 0x10, 0x84, 0x21, 0x8, 0x40,

    /* U+00EF "ï" */
    0x88, 0x0, 0x42, 0x10, 0x84, 0x21, 0x8, 0x40,

    /* U+00F0 "ð" */
    0x40, 0xec, 0x61, 0xe0, 0x47, 0x51, 0xc1, 0x83,
    0x6, 0xa, 0x23, 0x80,

    /* U+00F1 "ñ" */
    0x66, 0x60, 0x2e, 0xc6, 0x18, 0x61, 0x86, 0x18,
    0x61,

    /* U+00F2 "ò" */
    0x60, 0x60, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x83,
    0x5, 0x11, 0xc0,

    /* U+00F3 "ó" */
    0x8, 0x20, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x83,
    0x5, 0x11, 0xc0,

    /* U+00F4 "ô" */
    0x30, 0xd0, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x83,
    0x5, 0x11, 0xc0,

    /* U+00F5 "õ" */
    0x7c, 0x0, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x83,
    0x5, 0x11, 0xc0,

    /* U+00F6 "ö" */
    0x24, 0x0, 0x1, 0xc6, 0x58, 0x70, 0xe1, 0xc3,
    0x85, 0x91, 0xc0,

    /* U+00F7 "÷" */
    0x18, 0x18, 0x0, 0x0, 0xff, 0x0, 0x0, 0x18,
    0x18,

    /* U+00F8 "ø" */
    0x4, 0x79, 0x14, 0x59, 0x32, 0x68, 0xd1, 0x64,
    0xf1, 0x0,

    /* U+00F9 "ù" */
    0x60, 0xc0, 0x21, 0x86, 0x18, 0x61, 0x86, 0x18,
    0xdd,

    /* U+00FA "ú" */
    0x18, 0x40, 0x21, 0x86, 0x18, 0x61, 0x86, 0x18,
    0xdd,

    /* U+00FB "û" */
    0x31, 0x20, 0x21, 0x86, 0x18, 0x61, 0x86, 0x18,
    0xdd,

    /* U+00FC "ü" */
    0x4c, 0x0, 0x21, 0x86, 0x18, 0x61, 0x86, 0x18,
    0xdf,

    /* U+00FD "ý" */
    0xc, 0x10, 0x6, 0x14, 0x6c, 0xd9, 0x16, 0x3c,
    0x70, 0x60, 0x81, 0x6, 0x18, 0x0,

    /* U+00FE "þ" */
    0x81, 0x2, 0x5, 0xcc, 0x50, 0x60, 0xc1, 0x83,
    0x7, 0x15, 0xc8, 0x10, 0x20, 0x0,

    /* U+00FF "ÿ" */
    0x44, 0x0, 0x4, 0x3c, 0x58, 0x93, 0x34, 0x68,
    0x70, 0xc1, 0x81, 0x4, 0x30, 0x0,

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
    0xf0,

    /* U+2011 "‑" */
    0xf0,

    /* U+2013 "–" */
    0xff,

    /* U+2014 "—" */
    0xff, 0xc0,

    /* U+2015 "―" */
    0xff, 0xc0,

    /* U+2017 "‗" */
    0xfe, 0x3, 0xf8,

    /* U+2018 "‘" */
    0x6a,

    /* U+2019 "’" */
    0x56,

    /* U+201A "‚" */
    0x54,

    /* U+201B "‛" */
    0xa9,

    /* U+201C "“" */
    0x4e, 0xa5, 0x20,

    /* U+201D "”" */
    0x4a, 0x57, 0x20,

    /* U+201E "„" */
    0x4a, 0x53, 0xb0,

    /* U+2020 "†" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x40, 0x80,

    /* U+2021 "‡" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x47, 0xf1, 0x2, 0x4, 0x0,

    /* U+2022 "•" */
    0xff, 0x80,

    /* U+2025 "‥" */
    0xde, 0xc0,

    /* U+2026 "…" */
    0xd9, 0xec, 0xc0,

    /* U+2027 "‧" */
    0x80,

    /* U+2030 "‰" */
    0x70, 0x2, 0x24, 0x8, 0x90, 0x22, 0x80, 0x72,
    0x0, 0x10, 0x0, 0xdb, 0x82, 0x91, 0x12, 0x44,
    0x49, 0x12, 0x24, 0x40, 0x6e,

    /* U+2032 "′" */
    0xf0,

    /* U+2033 "″" */
    0xb6, 0xd0,

    /* U+2039 "‹" */
    0x2b, 0x64, 0x40,

    /* U+203A "›" */
    0x89, 0xb5, 0x0,

    /* U+203C "‼" */
    0x8c, 0x63, 0x18, 0xc6, 0x31, 0x0, 0x1, 0x10,

    /* U+2044 "⁄" */
    0x0, 0x8, 0x10, 0x41, 0x82, 0x8, 0x10, 0x41,
    0x80,

    /* U+20A3 "₣" */
    0x7f, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7e, 0x40,
    0x40, 0xf0, 0x40, 0x40,

    /* U+20A4 "₤" */
    0x1e, 0x23, 0x41, 0x40, 0x40, 0xfc, 0x40, 0xfc,
    0x40, 0x40, 0x40, 0xff,

    /* U+20A6 "₦" */
    0x20, 0x21, 0x81, 0xe, 0x8, 0x58, 0x4f, 0xff,
    0x93, 0x10, 0x8c, 0x9f, 0xff, 0x21, 0xa1, 0x7,
    0x8, 0x18, 0x40, 0x40,

    /* U+20A7 "₧" */
    0xf8, 0x11, 0x92, 0x12, 0x43, 0xf8, 0x49, 0x19,
    0x3e, 0x24, 0x4, 0x80, 0x90, 0x12, 0x2, 0x40,
    0x70,

    /* U+20A8 "₨" */
    0xfc, 0x1, 0x4, 0x2, 0x4, 0x4, 0x9, 0xe8,
    0x14, 0x70, 0x48, 0x7f, 0x18, 0x46, 0x1e, 0x86,
    0x7, 0x4, 0x6, 0xd, 0xc, 0xd, 0xe0,

    /* U+20A9 "₩" */
    0xc4, 0x68, 0x89, 0x39, 0x25, 0x2f, 0xfe, 0xd5,
    0x9a, 0xa7, 0xff, 0x3b, 0x86, 0x30, 0xc6, 0x18,
    0xc0,

    /* U+20AA "₪" */
    0xfc, 0x61, 0x98, 0x26, 0x49, 0x92, 0x64, 0x99,
    0x6, 0x43, 0x9f, 0x80,

    /* U+20AB "₫" */
    0x2, 0x7, 0xc0, 0x87, 0x44, 0x64, 0x12, 0x9,
    0x4, 0x82, 0x41, 0x11, 0x87, 0x40, 0x3, 0xf8,

    /* U+20AC "€" */
    0x1e, 0x41, 0x2, 0xf, 0x88, 0x3e, 0x20, 0x40,
    0x80, 0x80, 0xf0,

    /* U+20B1 "₱" */
    0x3f, 0x4, 0x13, 0xff, 0x90, 0x2f, 0xfe, 0x41,
    0xf, 0xc1, 0x0, 0x20, 0x4, 0x0, 0x80, 0x10,
    0x0,

    /* U+20B9 "₹" */
    0xff, 0xc, 0x7f, 0xff, 0xc, 0x7c, 0x60, 0x30,
    0x10, 0x18, 0xc,

    /* U+20BA "₺" */
    0x20, 0x24, 0x3c, 0x70, 0xec, 0x38, 0xe1, 0xa1,
    0x21, 0x22, 0x26, 0x3c,

    /* U+20BC "₼" */
    0x8, 0x4, 0xf, 0x8d, 0x64, 0x94, 0x46, 0x23,
    0x11, 0x88, 0x80,

    /* U+20BD "₽" */
    0x3f, 0x8, 0x22, 0x4, 0x81, 0x20, 0x48, 0x2f,
    0xf0, 0x80, 0x20, 0x3f, 0x2, 0x0, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 64, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 66, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 82, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 5, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 144, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 33, .adv_w = 188, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 159, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 45, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 63, .adv_w = 88, .box_w = 4, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 72, .adv_w = 89, .box_w = 4, .box_h = 17, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 81, .adv_w = 110, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 88, .adv_w = 145, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 96, .adv_w = 50, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 97, .adv_w = 71, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 98, .adv_w = 68, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 106, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 109, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 144, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 62, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 54, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 224, .adv_w = 130, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 231, .adv_w = 141, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 236, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 243, .adv_w = 121, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 230, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 277, .adv_w = 167, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 160, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 167, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 168, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 174, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 183, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 70, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 377, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 161, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 138, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 224, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 183, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 176, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 162, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 176, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 482, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 152, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 153, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 522, .adv_w = 166, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 534, .adv_w = 163, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 549, .adv_w = 227, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 570, .adv_w = 161, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 153, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 68, .box_w = 3, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 617, .adv_w = 105, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 627, .adv_w = 68, .box_w = 3, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 633, .adv_w = 107, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 638, .adv_w = 116, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 639, .adv_w = 79, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 10},
    {.bitmap_index = 641, .adv_w = 139, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 667, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 678, .adv_w = 136, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 686, .adv_w = 89, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 695, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 706, .adv_w = 141, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 715, .adv_w = 62, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 61, .box_w = 3, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 723, .adv_w = 130, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 734, .adv_w = 62, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 736, .adv_w = 225, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 750, .adv_w = 141, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 757, .adv_w = 146, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 765, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 776, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 787, .adv_w = 87, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 792, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 800, .adv_w = 84, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 807, .adv_w = 141, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 814, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 822, .adv_w = 192, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 836, .adv_w = 127, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 845, .adv_w = 121, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 856, .adv_w = 127, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 864, .adv_w = 87, .box_w = 5, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 874, .adv_w = 63, .box_w = 1, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 876, .adv_w = 87, .box_w = 5, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 887, .adv_w = 174, .box_w = 9, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 891, .adv_w = 64, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 892, .adv_w = 63, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 894, .adv_w = 140, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 906, .adv_w = 149, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 918, .adv_w = 183, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 931, .adv_w = 135, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 942, .adv_w = 62, .box_w = 1, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 944, .adv_w = 157, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 960, .adv_w = 107, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 961, .adv_w = 201, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 978, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 982, .adv_w = 120, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 987, .adv_w = 142, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 990, .adv_w = 71, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 991, .adv_w = 201, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1008, .adv_w = 117, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 1009, .adv_w = 96, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1011, .adv_w = 137, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1021, .adv_w = 94, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1025, .adv_w = 94, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 1029, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 1031, .adv_w = 145, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1040, .adv_w = 125, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1049, .adv_w = 67, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1050, .adv_w = 64, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1051, .adv_w = 94, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1054, .adv_w = 117, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1058, .adv_w = 120, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1063, .adv_w = 188, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1080, .adv_w = 199, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1096, .adv_w = 199, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1116, .adv_w = 121, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1127, .adv_w = 167, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1146, .adv_w = 167, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1165, .adv_w = 167, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1184, .adv_w = 167, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1203, .adv_w = 167, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1221, .adv_w = 167, .box_w = 10, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1241, .adv_w = 239, .box_w = 15, .box_h = 12, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1264, .adv_w = 167, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1281, .adv_w = 146, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1295, .adv_w = 146, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1309, .adv_w = 146, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1323, .adv_w = 146, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1336, .adv_w = 70, .box_w = 3, .box_h = 15, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1342, .adv_w = 70, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1348, .adv_w = 70, .box_w = 5, .box_h = 15, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1358, .adv_w = 70, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1367, .adv_w = 172, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1381, .adv_w = 183, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1398, .adv_w = 176, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1416, .adv_w = 176, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1434, .adv_w = 176, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1452, .adv_w = 176, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1469, .adv_w = 176, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1485, .adv_w = 137, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1492, .adv_w = 176, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1507, .adv_w = 166, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1522, .adv_w = 166, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1537, .adv_w = 166, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1552, .adv_w = 166, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1566, .adv_w = 154, .box_w = 9, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1583, .adv_w = 151, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1594, .adv_w = 152, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1606, .adv_w = 139, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1615, .adv_w = 139, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1624, .adv_w = 139, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1633, .adv_w = 139, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1642, .adv_w = 139, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1651, .adv_w = 139, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1662, .adv_w = 216, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1676, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1687, .adv_w = 136, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1698, .adv_w = 136, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1709, .adv_w = 136, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1720, .adv_w = 136, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1731, .adv_w = 63, .box_w = 3, .box_h = 12, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1736, .adv_w = 63, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1741, .adv_w = 63, .box_w = 5, .box_h = 12, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1749, .adv_w = 63, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1757, .adv_w = 150, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1769, .adv_w = 141, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1778, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1789, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1800, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1811, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1822, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1833, .adv_w = 146, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1842, .adv_w = 145, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1852, .adv_w = 141, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1861, .adv_w = 141, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1870, .adv_w = 141, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1879, .adv_w = 141, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1888, .adv_w = 121, .box_w = 7, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1902, .adv_w = 148, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1916, .adv_w = 121, .box_w = 7, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1930, .adv_w = 131, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1931, .adv_w = 261, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1932, .adv_w = 131, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1933, .adv_w = 261, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1934, .adv_w = 87, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1935, .adv_w = 65, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1936, .adv_w = 44, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1937, .adv_w = 144, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1938, .adv_w = 70, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1939, .adv_w = 52, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1940, .adv_w = 26, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1941, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1942, .adv_w = 71, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1943, .adv_w = 71, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1944, .adv_w = 168, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1945, .adv_w = 200, .box_w = 10, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1947, .adv_w = 200, .box_w = 10, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1949, .adv_w = 117, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1952, .adv_w = 51, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 1953, .adv_w = 51, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1954, .adv_w = 51, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1955, .adv_w = 51, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1956, .adv_w = 91, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 1959, .adv_w = 92, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1962, .adv_w = 88, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1965, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1976, .adv_w = 146, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1990, .adv_w = 86, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1992, .adv_w = 121, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1994, .adv_w = 171, .box_w = 9, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1997, .adv_w = 48, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1998, .adv_w = 245, .box_w = 14, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2019, .adv_w = 45, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 2020, .adv_w = 82, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 2022, .adv_w = 77, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2025, .adv_w = 77, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2028, .adv_w = 132, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2036, .adv_w = 116, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2045, .adv_w = 142, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2057, .adv_w = 149, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2069, .adv_w = 203, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2089, .adv_w = 210, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2106, .adv_w = 271, .box_w = 15, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2129, .adv_w = 189, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2146, .adv_w = 197, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2158, .adv_w = 148, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2174, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2185, .adv_w = 187, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2202, .adv_w = 132, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2213, .adv_w = 143, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2225, .adv_w = 169, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2236, .adv_w = 170, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0}
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
    -13, -13, -13, -13, -13, -13, -13, -13,
    -13, -13, -13, -13, -13, -13, -13, -13,
    -13, -13, -21, -21, -21, -21, -21, -21,
    -21, -21, -21, -21, -21, -21, -21, -21,
    -21, -21, -21, -21, -28, -13, -13, -13,
    -13, -13, -13, -13, -13, -13, -13, -13,
    -13, -13, -13, -13, -13, -13, -13, -21,
    -21, -21, -21, -21, -21, -21, -21, -21,
    -13, -13, -13, -13, -13, -13, -13, -13,
    -13, -13, -13, -13, -13, -13, -13, -13,
    -13, -13, -13, -13, -13, -13, -13, -13,
    -13, -13, -13, -21, -21, -21, -21, -21,
    -21, -21, -21, -21, -21, -21, -21, -21,
    -21, -21, -21, -21, -21, -21, -21, -21,
    -21, -21, -21, -21, -21, -21, -13, -13,
    -13, -13, -13, -13, -13, -13, -13, -13,
    -13, -13, -13, -13, -13, -13, -13, -13
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

extern const lv_font_t roboto_reg_16;


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t roboto_reg_16 = {
#else
lv_font_t roboto_reg_16 = {
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
    .fallback = &roboto_reg_16,
#endif
    .user_data = NULL,
};



#endif /*#if ROBOTO_REG_16*/
