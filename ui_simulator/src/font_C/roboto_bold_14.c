/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --stride 1 --align 1 --font Roboto-Bold.ttf --range 32-127,160-255,8352-8399,8192-8303 --format lvgl -o roboto_bold_14.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef ROBOTO_BOLD_14
#define ROBOTO_BOLD_14 1
#endif

#if ROBOTO_BOLD_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0xc,

    /* U+0022 "\"" */
    0xff, 0xff,

    /* U+0023 "#" */
    0x14, 0x14, 0x14, 0x7f, 0x34, 0x24, 0x2c, 0xfe,
    0x28, 0x28, 0x28,

    /* U+0024 "$" */
    0x8, 0x10, 0xf3, 0xf6, 0x6c, 0xdc, 0xe, 0xf,
    0xcd, 0x9b, 0xf3, 0xc1, 0x2, 0x0,

    /* U+0025 "%" */
    0x70, 0x6d, 0x37, 0x9b, 0x87, 0x40, 0x40, 0x2c,
    0x2b, 0x15, 0x92, 0xc0, 0xc0,

    /* U+0026 "&" */
    0x38, 0x36, 0x1b, 0xf, 0x87, 0x83, 0xc3, 0xed,
    0xbe, 0xce, 0x63, 0x9e, 0xc0,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x13, 0x66, 0xcc, 0xcc, 0xcc, 0xc4, 0x62, 0x10,

    /* U+0029 ")" */
    0x8c, 0x66, 0x33, 0x33, 0x33, 0x32, 0x64, 0x80,

    /* U+002A "*" */
    0x21, 0x3e, 0xe5, 0x6c,

    /* U+002B "+" */
    0x18, 0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18,

    /* U+002C "," */
    0x6d, 0xe0,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x18, 0xc4, 0x63, 0x11, 0x8c, 0x42, 0x31, 0x0,

    /* U+0030 "0" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+0031 "1" */
    0x1b, 0xfe, 0x31, 0x8c, 0x63, 0x18, 0xc6,

    /* U+0032 "2" */
    0x79, 0x9b, 0x30, 0x60, 0xc3, 0xe, 0x18, 0x61,
    0xc3, 0xf8,

    /* U+0033 "3" */
    0x3c, 0xcf, 0x18, 0x31, 0xe3, 0x87, 0x83, 0x46,
    0xcc, 0xf0,

    /* U+0034 "4" */
    0xc, 0x38, 0xf1, 0xe6, 0xcd, 0xb3, 0x7f, 0xc,
    0x18, 0x30,

    /* U+0035 "5" */
    0x7e, 0xc1, 0x83, 0x7, 0xc9, 0xc1, 0x83, 0xc6,
    0xdc, 0xf0,

    /* U+0036 "6" */
    0x18, 0x61, 0x86, 0xf, 0xd9, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+0037 "7" */
    0xfe, 0xc, 0x30, 0x60, 0xc3, 0x6, 0x18, 0x30,
    0x61, 0x80,

    /* U+0038 "8" */
    0x7d, 0x8f, 0x1e, 0x3f, 0xef, 0xbb, 0xe3, 0xc7,
    0x8d, 0xf0,

    /* U+0039 "9" */
    0x38, 0xdb, 0x1e, 0x3c, 0x7c, 0xdf, 0x83, 0x4,
    0x18, 0xc0,

    /* U+003A ":" */
    0xc0, 0x3,

    /* U+003B ";" */
    0xc0, 0x3f, 0x80,

    /* U+003C "<" */
    0x4, 0x7f, 0xb0, 0xf8, 0x70, 0x40,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x83, 0x87, 0xc3, 0x7f, 0x88, 0x0,

    /* U+003F "?" */
    0x7b, 0x3c, 0xc3, 0x1c, 0x63, 0xc, 0x30, 0x3,
    0x0,

    /* U+0040 "@" */
    0xf, 0x6, 0x11, 0x81, 0x30, 0x1c, 0x73, 0x92,
    0x76, 0x4e, 0xc9, 0xd9, 0x3b, 0x6b, 0x37, 0x30,
    0x3, 0x0, 0x3e, 0x0,

    /* U+0041 "A" */
    0xc, 0xe, 0x7, 0x3, 0xc3, 0x61, 0x90, 0xcc,
    0xfe, 0x63, 0x30, 0xf8, 0x60,

    /* U+0042 "B" */
    0xfd, 0x8f, 0x1e, 0x3c, 0x7f, 0xb1, 0xe3, 0xc7,
    0x8f, 0xf0,

    /* U+0043 "C" */
    0x3c, 0x66, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc3, 0x66, 0x3c,

    /* U+0044 "D" */
    0xf8, 0xc6, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc6, 0xc6, 0xf8,

    /* U+0045 "E" */
    0xff, 0x83, 0x6, 0xc, 0x1f, 0xb0, 0x60, 0xc1,
    0x83, 0xf8,

    /* U+0046 "F" */
    0xff, 0x83, 0x6, 0xc, 0x1f, 0xb0, 0x60, 0xc1,
    0x83, 0x0,

    /* U+0047 "G" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc0, 0xc0, 0xcf, 0xc3,
    0xc3, 0x63, 0x3e,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0049 "I" */
    0xff, 0xff, 0xfc,

    /* U+004A "J" */
    0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x66,
    0xcc, 0xf0,

    /* U+004B "K" */
    0xc7, 0xce, 0xcc, 0xd8, 0xf8, 0xf8, 0xf8, 0xcc,
    0xce, 0xc6, 0xc7,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0x83, 0xf8,

    /* U+004D "M" */
    0xe0, 0xfc, 0x1f, 0xc7, 0xf8, 0xfd, 0x17, 0xb6,
    0xf6, 0xde, 0x53, 0xce, 0x79, 0xcf, 0x11, 0x80,

    /* U+004E "N" */
    0xc3, 0xe3, 0xe3, 0xf3, 0xf3, 0xdb, 0xcf, 0xcf,
    0xc7, 0xc7, 0xc3,

    /* U+004F "O" */
    0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x66, 0x3c,

    /* U+0050 "P" */
    0xfc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc6, 0xfc, 0xc0,
    0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x66, 0x3e, 0x7, 0x2,

    /* U+0052 "R" */
    0xfd, 0x9f, 0x1e, 0x3c, 0x79, 0xbe, 0x6c, 0xcd,
    0x9f, 0x18,

    /* U+0053 "S" */
    0x1e, 0x63, 0x63, 0x70, 0x7c, 0x3e, 0x1f, 0x7,
    0x63, 0x63, 0x3e,

    /* U+0054 "T" */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x66, 0x3c,

    /* U+0056 "V" */
    0xc1, 0xb1, 0xd8, 0xcc, 0x67, 0x31, 0xb0, 0xd8,
    0x6c, 0x1c, 0xe, 0x7, 0x0,

    /* U+0057 "W" */
    0xc6, 0x3c, 0x63, 0xc6, 0x36, 0xf6, 0x6f, 0x66,
    0xf6, 0x69, 0x67, 0x9e, 0x39, 0xc3, 0x9c, 0x30,
    0xc0,

    /* U+0058 "X" */
    0xe3, 0x31, 0x8d, 0x86, 0xc1, 0xc0, 0xe0, 0x70,
    0x6c, 0x76, 0x31, 0xb8, 0xc0,

    /* U+0059 "Y" */
    0xc3, 0xe7, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+005A "Z" */
    0xff, 0x7, 0x6, 0xc, 0xc, 0x18, 0x38, 0x30,
    0x60, 0xe0, 0xff,

    /* U+005B "[" */
    0xfb, 0x6d, 0xb6, 0xdb, 0x6d, 0xc0,

    /* U+005C "\\" */
    0xc1, 0x86, 0x18, 0x30, 0xc3, 0x6, 0x18, 0x60,
    0xc3,

    /* U+005D "]" */
    0xed, 0xb6, 0xdb, 0x6d, 0xb7, 0xc0,

    /* U+005E "^" */
    0x30, 0xc3, 0x9e, 0x4b, 0x30,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0x60,

    /* U+0061 "a" */
    0x3c, 0xcc, 0x19, 0xf6, 0x7c, 0xd9, 0x9f,

    /* U+0062 "b" */
    0xc1, 0x83, 0x7, 0xee, 0xd8, 0xf1, 0xe3, 0xc7,
    0xcb, 0xf0,

    /* U+0063 "c" */
    0x38, 0x9b, 0x16, 0xc, 0x18, 0xd3, 0x1c,

    /* U+0064 "d" */
    0x6, 0xc, 0x1b, 0xf6, 0xf8, 0xf1, 0xe3, 0xc6,
    0xdd, 0xf8,

    /* U+0065 "e" */
    0x38, 0xdb, 0x17, 0xfc, 0x18, 0x19, 0x1e,

    /* U+0066 "f" */
    0x3b, 0x19, 0xe6, 0x31, 0x8c, 0x63, 0x18,

    /* U+0067 "g" */
    0x7e, 0xcf, 0x1e, 0x3c, 0x78, 0xd9, 0xbf, 0x6,
    0x8d, 0xe0,

    /* U+0068 "h" */
    0xc3, 0xc, 0x3e, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xc0,

    /* U+0069 "i" */
    0xc3, 0xff, 0xfc,

    /* U+006A "j" */
    0x30, 0x3, 0x33, 0x33, 0x33, 0x33, 0x3e,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0x6d, 0x9f, 0x3c, 0x7c, 0xd9,
    0x9b, 0x38,

    /* U+006C "l" */
    0xff, 0xff, 0xfc,

    /* U+006D "m" */
    0xfb, 0xd9, 0x8f, 0x31, 0xe6, 0x3c, 0xc7, 0x98,
    0xf3, 0x1e, 0x63,

    /* U+006E "n" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3,

    /* U+006F "o" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xdb, 0x1c,

    /* U+0070 "p" */
    0xfd, 0xdb, 0x1e, 0x3c, 0x78, 0xfb, 0x7e, 0xc1,
    0x83, 0x0,

    /* U+0071 "q" */
    0x7e, 0xdf, 0x1e, 0x3c, 0x78, 0xdb, 0xbf, 0x6,
    0xc, 0x18,

    /* U+0072 "r" */
    0xfc, 0xcc, 0xcc, 0xcc,

    /* U+0073 "s" */
    0x7b, 0x3c, 0x3e, 0x7c, 0x3c, 0xde,

    /* U+0074 "t" */
    0x66, 0xf6, 0x66, 0x66, 0x73,

    /* U+0075 "u" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xdf,

    /* U+0076 "v" */
    0xc7, 0x8d, 0xb3, 0x66, 0xc7, 0xe, 0x1c,

    /* U+0077 "w" */
    0xcc, 0xf3, 0x34, 0xc9, 0xfe, 0x7f, 0x9c, 0xe7,
    0x38, 0xcc,

    /* U+0078 "x" */
    0x66, 0xd8, 0xf1, 0xc3, 0x8f, 0x9b, 0x73,

    /* U+0079 "y" */
    0xc6, 0xcd, 0xb3, 0x62, 0xc7, 0xe, 0xc, 0x10,
    0x61, 0x80,

    /* U+007A "z" */
    0xfc, 0x61, 0x8c, 0x21, 0x8c, 0x3f,

    /* U+007B "{" */
    0x13, 0x66, 0x66, 0xec, 0xe6, 0x66, 0x63, 0x10,

    /* U+007C "|" */
    0xff, 0xf0,

    /* U+007D "}" */
    0x8c, 0x66, 0x66, 0x73, 0x76, 0x66, 0x6c, 0x80,

    /* U+007E "~" */
    0x72, 0xde, 0x8e,

    /* U+00A0 " " */
    0x0,

    /* U+00A1 "¡" */
    0xc0, 0xff, 0xfc,

    /* U+00A2 "¢" */
    0x30, 0x60, 0xe3, 0xec, 0xd8, 0x30, 0x66, 0x7c,
    0x70, 0xc1, 0x80,

    /* U+00A3 "£" */
    0x3c, 0xcd, 0x9b, 0x6, 0x1f, 0x18, 0x30, 0x60,
    0xc3, 0xf8,

    /* U+00A4 "¤" */
    0xbd, 0x43, 0xc3, 0x81, 0x81, 0x81, 0xc3, 0xc7,
    0xbd,

    /* U+00A5 "¥" */
    0x66, 0x66, 0x66, 0x3c, 0x3c, 0x1c, 0x7e, 0x18,
    0x7e, 0x18, 0x18,

    /* U+00A6 "¦" */
    0xff, 0xcf, 0xff,

    /* U+00A7 "§" */
    0x7d, 0x9f, 0x1f, 0xf, 0x9f, 0xf3, 0xf3, 0xfe,
    0xfc, 0x3e, 0x3c, 0x6f, 0x80,

    /* U+00A8 "¨" */
    0xd8,

    /* U+00A9 "©" */
    0x1e, 0x8, 0x45, 0xca, 0x89, 0xa0, 0x68, 0x1a,
    0x6, 0x89, 0x5c, 0x88, 0x41, 0xe0,

    /* U+00AA "ª" */
    0x79, 0xf9, 0xf0,

    /* U+00AB "«" */
    0x6a, 0xf5, 0x6d, 0xa4,

    /* U+00AC "¬" */
    0xfe, 0xc, 0x18,

    /* U+00AD "­" */
    0xf0,

    /* U+00AE "®" */
    0x1e, 0x8, 0x45, 0xca, 0x49, 0x92, 0x67, 0x99,
    0x26, 0x49, 0x40, 0x88, 0x41, 0xe0,

    /* U+00AF "¯" */
    0xf8,

    /* U+00B0 "°" */
    0x69, 0x96,

    /* U+00B1 "±" */
    0x30, 0xc3, 0xc, 0xfc, 0xc3, 0xc, 0x3, 0xf0,

    /* U+00B2 "²" */
    0xf9, 0x34, 0xf0,

    /* U+00B3 "³" */
    0xe1, 0x71, 0xe0,

    /* U+00B4 "´" */
    0xc0,

    /* U+00B5 "µ" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xff, 0xc1,
    0x83, 0x0,

    /* U+00B6 "¶" */
    0x3d, 0xff, 0xff, 0xfd, 0xf7, 0xc3, 0xc, 0x30,
    0xc0,

    /* U+00B7 "·" */
    0xc0,

    /* U+00B8 "¸" */
    0xcb, 0x0,

    /* U+00B9 "¹" */
    0xd5, 0x40,

    /* U+00BA "º" */
    0x74, 0x63, 0x17, 0x0,

    /* U+00BB "»" */
    0xb6, 0x96, 0xdd, 0xc8,

    /* U+00BC "¼" */
    0x70, 0x2c, 0x83, 0x20, 0xd0, 0x35, 0x8f, 0xe1,
    0xb8, 0x7e, 0x37, 0xc0, 0x60,

    /* U+00BD "½" */
    0x10, 0x3c, 0x3, 0x20, 0xc8, 0x34, 0xf, 0x60,
    0xa4, 0x63, 0x11, 0x8c, 0x40, 0x3c,

    /* U+00BE "¾" */
    0xf0, 0x2, 0x20, 0xc4, 0x49, 0xf, 0x6c, 0xb,
    0x82, 0xf0, 0xd6, 0x13, 0xe0, 0x18,

    /* U+00BF "¿" */
    0x30, 0x0, 0xc, 0x31, 0x8e, 0x30, 0xcf, 0x37,
    0x80,

    /* U+00C0 "À" */
    0x18, 0x0, 0x3, 0x3, 0x81, 0xc0, 0xf0, 0xd8,
    0x64, 0x33, 0x3f, 0x98, 0xcc, 0x3e, 0x18,

    /* U+00C1 "Á" */
    0x4, 0x0, 0x3, 0x3, 0x81, 0xc0, 0xf0, 0xd8,
    0x64, 0x33, 0x3f, 0x98, 0xcc, 0x3e, 0x18,

    /* U+00C2 "Â" */
    0x8, 0xe, 0xc, 0x81, 0x81, 0xc0, 0xe0, 0x78,
    0x6c, 0x32, 0x19, 0x9f, 0xcc, 0x66, 0x1f, 0xc,

    /* U+00C3 "Ã" */
    0x1e, 0x0, 0x3, 0x3, 0x81, 0xc0, 0xf0, 0xd8,
    0x64, 0x33, 0x3f, 0x98, 0xcc, 0x3e, 0x18,

    /* U+00C4 "Ä" */
    0x33, 0x0, 0x0, 0xc0, 0x78, 0x1e, 0x7, 0x83,
    0x70, 0xcc, 0x33, 0x1f, 0xe6, 0x19, 0x87, 0xc1,
    0xc0,

    /* U+00C5 "Å" */
    0x1c, 0xa, 0x7, 0x1, 0x1, 0xc0, 0xa0, 0x58,
    0x6c, 0x36, 0x11, 0x9f, 0xcc, 0x66, 0x1e, 0xc,

    /* U+00C6 "Æ" */
    0x7, 0xf0, 0x78, 0x3, 0xc0, 0x36, 0x1, 0xb0,
    0x19, 0xf8, 0xcc, 0xf, 0xe0, 0x63, 0x7, 0x18,
    0x30, 0xfe,

    /* U+00C7 "Ç" */
    0x3c, 0x63, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0, 0xc3,
    0xff, 0x7e, 0x3c, 0x18, 0xc, 0x18,

    /* U+00C8 "È" */
    0x30, 0x3, 0xfe, 0xc, 0x18, 0x30, 0x7e, 0xc1,
    0x83, 0x6, 0xf, 0xe0,

    /* U+00C9 "É" */
    0x18, 0x3, 0xfe, 0xc, 0x18, 0x30, 0x7e, 0xc1,
    0x83, 0x6, 0xf, 0xe0,

    /* U+00CA "Ê" */
    0x10, 0x71, 0x17, 0xfc, 0x18, 0x30, 0x60, 0xfd,
    0x83, 0x6, 0xc, 0x1f, 0xc0,

    /* U+00CB "Ë" */
    0x6c, 0x3, 0xfe, 0xc, 0x18, 0x30, 0x7e, 0xc1,
    0x83, 0x6, 0xf, 0xe0,

    /* U+00CC "Ì" */
    0x60, 0x33, 0x33, 0x33, 0x33, 0x33, 0x30,

    /* U+00CD "Í" */
    0x60, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xc0,

    /* U+00CE "Î" */
    0x31, 0xec, 0xcc, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0xc, 0x30, 0xc0,

    /* U+00CF "Ï" */
    0xd8, 0xc, 0x63, 0x18, 0xc6, 0x31, 0x8c, 0x63,
    0x0,

    /* U+00D0 "Ð" */
    0x7c, 0x31, 0x98, 0x4c, 0x36, 0x1f, 0xcd, 0x86,
    0xc3, 0x63, 0x31, 0x9f, 0x0,

    /* U+00D1 "Ñ" */
    0x3c, 0x0, 0xc3, 0xe3, 0xe3, 0xf3, 0xf3, 0xdb,
    0xcf, 0xcf, 0xc7, 0xc7, 0xc3,

    /* U+00D2 "Ò" */
    0x10, 0x0, 0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x66, 0x3c,

    /* U+00D3 "Ó" */
    0x8, 0x0, 0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x66, 0x3c,

    /* U+00D4 "Ô" */
    0x18, 0x38, 0x24, 0x3c, 0x66, 0xc2, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c,

    /* U+00D5 "Õ" */
    0x3c, 0x0, 0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x66, 0x3c,

    /* U+00D6 "Ö" */
    0x36, 0x0, 0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x66, 0x3c,

    /* U+00D7 "×" */
    0x46, 0xd8, 0xe1, 0xc6, 0xcc, 0xc0, 0x0,

    /* U+00D8 "Ø" */
    0x3e, 0x66, 0xc6, 0xc7, 0xcb, 0xcb, 0xd3, 0xf3,
    0xe3, 0x66, 0x7c, 0xc0,

    /* U+00D9 "Ù" */
    0x30, 0x0, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x66, 0x3c,

    /* U+00DA "Ú" */
    0xc, 0x0, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x66, 0x3c,

    /* U+00DB "Û" */
    0x18, 0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c,

    /* U+00DC "Ü" */
    0x6c, 0x0, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x66, 0x3c,

    /* U+00DD "Ý" */
    0xc, 0x0, 0xc3, 0xe7, 0x66, 0x66, 0x3c, 0x3c,
    0x18, 0x18, 0x18, 0x18, 0x18,

    /* U+00DE "Þ" */
    0xc1, 0x83, 0x7, 0xec, 0x78, 0xf1, 0xe3, 0xfd,
    0x83, 0x0,

    /* U+00DF "ß" */
    0x79, 0x9b, 0x36, 0x6d, 0x9b, 0x37, 0x67, 0xc7,
    0x8f, 0xf0,

    /* U+00E0 "à" */
    0x30, 0x0, 0x1, 0xe6, 0x60, 0xcf, 0xb3, 0xe6,
    0xcc, 0xf8,

    /* U+00E1 "á" */
    0xc, 0x0, 0x1, 0xe6, 0x60, 0xcf, 0xb3, 0xe6,
    0xcc, 0xf8,

    /* U+00E2 "â" */
    0x18, 0x48, 0x1, 0xe6, 0x60, 0xcf, 0xb3, 0xe6,
    0xcc, 0xf8,

    /* U+00E3 "ã" */
    0x7c, 0x0, 0x1, 0xe6, 0x60, 0xcf, 0xb3, 0xe6,
    0xcc, 0xf8,

    /* U+00E4 "ä" */
    0x6c, 0x0, 0x1, 0xe6, 0x60, 0xcf, 0xb3, 0xe6,
    0xcd, 0xf8,

    /* U+00E5 "å" */
    0x38, 0xa3, 0x80, 0x7b, 0xb0, 0xdf, 0xcf, 0x3c,
    0xdf,

    /* U+00E6 "æ" */
    0x7b, 0xd9, 0xcc, 0x31, 0xbf, 0xfc, 0xc1, 0x98,
    0x33, 0x93, 0xdf,

    /* U+00E7 "ç" */
    0x38, 0x9b, 0x6, 0xc, 0x7d, 0x9f, 0x1c, 0x30,
    0x30, 0xc0,

    /* U+00E8 "è" */
    0x20, 0x0, 0x1, 0xc6, 0xd8, 0xbf, 0xe0, 0xc0,
    0xc8, 0xf0,

    /* U+00E9 "é" */
    0x18, 0x0, 0x1, 0xc6, 0xd8, 0xbf, 0xe0, 0xc0,
    0xc8, 0xf0,

    /* U+00EA "ê" */
    0x30, 0xd0, 0x1, 0xc6, 0xd8, 0xbf, 0xe0, 0xc0,
    0xc8, 0xf0,

    /* U+00EB "ë" */
    0x6c, 0x0, 0x1, 0xc6, 0x58, 0xbf, 0xe0, 0xc0,
    0xc8, 0xf0,

    /* U+00EC "ì" */
    0x60, 0x3, 0x33, 0x33, 0x33, 0x30,

    /* U+00ED "í" */
    0x60, 0xc, 0xcc, 0xcc, 0xcc, 0xc0,

    /* U+00EE "î" */
    0x31, 0x20, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0x0,

    /* U+00EF "ï" */
    0xd8, 0x0, 0x63, 0x18, 0xc6, 0x31, 0x8c,

    /* U+00F0 "ð" */
    0x74, 0x70, 0xf0, 0x77, 0xfc, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+00F1 "ñ" */
    0x78, 0x0, 0x3e, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xc0,

    /* U+00F2 "ò" */
    0x30, 0x0, 0x1, 0xc6, 0xd8, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+00F3 "ó" */
    0x18, 0x0, 0x1, 0xc6, 0xd8, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+00F4 "ô" */
    0x38, 0xd8, 0x1, 0xc6, 0xd8, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+00F5 "õ" */
    0x7c, 0x0, 0x1, 0xc6, 0xd8, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+00F6 "ö" */
    0x6c, 0x0, 0x1, 0xc6, 0xd8, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+00F7 "÷" */
    0x18, 0x3, 0xf8, 0x0, 0x0, 0x6, 0x0,

    /* U+00F8 "ø" */
    0x4, 0x79, 0xb6, 0x7d, 0x7a, 0xf9, 0xb6, 0x78,
    0x80,

    /* U+00F9 "ù" */
    0x20, 0x0, 0x33, 0xcf, 0x3c, 0xf3, 0xcf, 0x37,
    0xc0,

    /* U+00FA "ú" */
    0x10, 0x0, 0x33, 0xcf, 0x3c, 0xf3, 0xcf, 0x37,
    0xc0,

    /* U+00FB "û" */
    0x31, 0x60, 0x33, 0xcf, 0x3c, 0xf3, 0xcf, 0x37,
    0xc0,

    /* U+00FC "ü" */
    0x6c, 0x0, 0x33, 0xcf, 0x3c, 0xf3, 0xcf, 0x37,
    0xc0,

    /* U+00FD "ý" */
    0x18, 0x0, 0x6, 0x36, 0x6d, 0x9b, 0x16, 0x38,
    0x70, 0x60, 0x83, 0xc, 0x0,

    /* U+00FE "þ" */
    0xc1, 0x83, 0x7, 0xec, 0xd8, 0xf1, 0xe3, 0xc7,
    0xdb, 0xf6, 0xc, 0x18, 0x0,

    /* U+00FF "ÿ" */
    0x6c, 0x0, 0x6, 0x36, 0xcd, 0x9b, 0x14, 0x38,
    0x70, 0x60, 0x83, 0xc, 0x0,

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
    0xfe,

    /* U+2014 "—" */
    0xff, 0x80,

    /* U+2015 "―" */
    0xff, 0x80,

    /* U+2017 "‗" */
    0xfc, 0xf, 0xc0,

    /* U+2018 "‘" */
    0x5b, 0x60,

    /* U+2019 "’" */
    0x6d, 0xa0,

    /* U+201A "‚" */
    0x6d, 0xa0,

    /* U+201B "‛" */
    0xdb, 0x20,

    /* U+201C "“" */
    0x57, 0xbd, 0xe0,

    /* U+201D "”" */
    0x7b, 0xde, 0xa0,

    /* U+201E "„" */
    0x7b, 0xde, 0xa0,

    /* U+2020 "†" */
    0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+2021 "‡" */
    0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0xff, 0x18, 0x18, 0x18,

    /* U+2022 "•" */
    0xff, 0x80,

    /* U+2025 "‥" */
    0xd8,

    /* U+2026 "…" */
    0xdb,

    /* U+2027 "‧" */
    0xc0,

    /* U+2030 "‰" */
    0x70, 0x4, 0xc8, 0x26, 0x81, 0x3c, 0x7, 0x40,
    0x6, 0x0, 0x2d, 0xc2, 0xd3, 0x36, 0x99, 0x34,
    0xc0, 0xdc,

    /* U+2032 "′" */
    0xff,

    /* U+2033 "″" */
    0xff, 0xff,

    /* U+2039 "‹" */
    0x6b, 0x64, 0xc0,

    /* U+203A "›" */
    0x99, 0x3d, 0x0,

    /* U+203C "‼" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xc0, 0x0, 0xc,
    0xc0,

    /* U+2044 "⁄" */
    0x0, 0x30, 0x86, 0x10, 0x86, 0x10, 0xc0,

    /* U+20A3 "₣" */
    0x7f, 0x60, 0x60, 0x60, 0x60, 0x7e, 0x60, 0x60,
    0xf8, 0x60, 0x60,

    /* U+20A4 "₤" */
    0x3c, 0xcd, 0x9b, 0x6, 0x1f, 0x18, 0x7c, 0x60,
    0xc3, 0xf8,

    /* U+20A6 "₦" */
    0x61, 0x9c, 0x67, 0x19, 0xe6, 0xff, 0xdb, 0x6f,
    0xfd, 0x9e, 0x63, 0x98, 0xe6, 0x18,

    /* U+20A7 "₧" */
    0xf9, 0xb3, 0x6c, 0xfb, 0x3f, 0xcf, 0xb3, 0x6f,
    0x9b, 0x6, 0xc1, 0xb0, 0x7c, 0xc,

    /* U+20A8 "₨" */
    0xfc, 0x3, 0x38, 0xc, 0x60, 0x31, 0x9e, 0xc6,
    0xcf, 0x37, 0x3f, 0x8f, 0xb6, 0x1f, 0xcc, 0x1f,
    0x38, 0x3c, 0x6f, 0x80,

    /* U+20A9 "₩" */
    0x44, 0x4d, 0xd9, 0xbb, 0x7f, 0xf6, 0xed, 0xff,
    0xce, 0xe1, 0xdc, 0x3b, 0x87, 0x70, 0xee, 0x0,

    /* U+20AA "₪" */
    0xfe, 0x78, 0x6f, 0x6d, 0xed, 0xbd, 0xb7, 0xb6,
    0xf6, 0x1e, 0xfc,

    /* U+20AB "₫" */
    0x6, 0x1f, 0x6, 0x7e, 0x6e, 0xc6, 0xc6, 0xc6,
    0xc6, 0x6e, 0x7e, 0x0, 0x7e,

    /* U+20AC "€" */
    0x1e, 0x61, 0x83, 0xf, 0x8c, 0x3e, 0x30, 0x60,
    0x60, 0x78,

    /* U+20B1 "₱" */
    0x7e, 0x18, 0xc6, 0x1b, 0xff, 0xff, 0xd8, 0xc7,
    0xe1, 0x80, 0x60, 0x18, 0x6, 0x0,

    /* U+20B9 "₹" */
    0x7f, 0xf0, 0x37, 0xf1, 0xdf, 0x18, 0x18, 0x38,
    0x38,

    /* U+20BA "₺" */
    0x60, 0xe1, 0xc7, 0x7, 0x1e, 0x39, 0xb3, 0x66,
    0xd9, 0xe0,

    /* U+20BC "₼" */
    0x18, 0x18, 0x3c, 0x7e, 0xdb, 0xdb, 0xdb, 0xdb,

    /* U+20BD "₽" */
    0x3f, 0xc, 0x63, 0x8, 0xc3, 0x30, 0xcc, 0x6f,
    0xf0, 0xc0, 0xfc, 0xc, 0x3, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 56, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 61, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 71, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 6, .adv_w = 133, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 129, .box_w = 7, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 31, .adv_w = 166, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 147, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 36, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 58, .adv_w = 78, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 66, .adv_w = 79, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 74, .adv_w = 102, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 78, .adv_w = 122, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 86, .adv_w = 55, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 88, .adv_w = 88, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 89, .adv_w = 65, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 83, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 98, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 129, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 63, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 59, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 200, .adv_w = 114, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 206, .adv_w = 129, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 209, .adv_w = 116, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 215, .adv_w = 111, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 201, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 244, .adv_w = 151, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 143, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 147, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 146, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 320, .adv_w = 158, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 66, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 125, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 142, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 196, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 158, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 144, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 427, .adv_w = 144, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 138, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 448, .adv_w = 139, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 148, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 146, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 196, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 142, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 139, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 524, .adv_w = 136, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 535, .adv_w = 62, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 541, .adv_w = 94, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 550, .adv_w = 62, .box_w = 3, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 556, .adv_w = 98, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 561, .adv_w = 100, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 562, .adv_w = 74, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 10},
    {.bitmap_index = 563, .adv_w = 120, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 570, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 580, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 597, .adv_w = 121, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 604, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 621, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 630, .adv_w = 59, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 633, .adv_w = 58, .box_w = 4, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 640, .adv_w = 120, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 650, .adv_w = 59, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 653, .adv_w = 194, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 664, .adv_w = 126, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 687, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 697, .adv_w = 82, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 701, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 76, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 712, .adv_w = 125, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 718, .adv_w = 113, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 725, .adv_w = 165, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 735, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 742, .adv_w = 113, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 752, .adv_w = 114, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 74, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 766, .adv_w = 56, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 768, .adv_w = 74, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 776, .adv_w = 145, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 779, .adv_w = 56, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 780, .adv_w = 63, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 783, .adv_w = 129, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 794, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 804, .adv_w = 155, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 813, .adv_w = 120, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 56, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 827, .adv_w = 141, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 840, .adv_w = 105, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 841, .adv_w = 176, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 855, .adv_w = 99, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 858, .adv_w = 112, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 862, .adv_w = 123, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 865, .adv_w = 88, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 866, .adv_w = 176, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 880, .adv_w = 112, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 881, .adv_w = 87, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 883, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 891, .adv_w = 83, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 894, .adv_w = 83, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 897, .adv_w = 74, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 898, .adv_w = 138, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 908, .adv_w = 109, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 917, .adv_w = 68, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 918, .adv_w = 60, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 920, .adv_w = 83, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 922, .adv_w = 102, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 926, .adv_w = 112, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 930, .adv_w = 160, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 943, .adv_w = 170, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 957, .adv_w = 181, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 971, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 980, .adv_w = 151, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 995, .adv_w = 151, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1010, .adv_w = 151, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1026, .adv_w = 151, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1041, .adv_w = 151, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1058, .adv_w = 151, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1074, .adv_w = 210, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1092, .adv_w = 147, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1106, .adv_w = 126, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1118, .adv_w = 126, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1130, .adv_w = 126, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1143, .adv_w = 126, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1155, .adv_w = 66, .box_w = 4, .box_h = 13, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1162, .adv_w = 66, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1169, .adv_w = 66, .box_w = 6, .box_h = 14, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1180, .adv_w = 66, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1189, .adv_w = 149, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1202, .adv_w = 158, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1215, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1228, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1241, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1255, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1268, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1281, .adv_w = 119, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1288, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1300, .adv_w = 148, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1313, .adv_w = 148, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1326, .adv_w = 148, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1340, .adv_w = 148, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1353, .adv_w = 139, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1366, .adv_w = 137, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1376, .adv_w = 142, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1386, .adv_w = 120, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1396, .adv_w = 120, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1406, .adv_w = 120, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1416, .adv_w = 120, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1426, .adv_w = 120, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1436, .adv_w = 120, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1445, .adv_w = 189, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1456, .adv_w = 117, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1466, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1476, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1486, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1496, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1506, .adv_w = 61, .box_w = 4, .box_h = 11, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1512, .adv_w = 61, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1518, .adv_w = 61, .box_w = 6, .box_h = 11, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1527, .adv_w = 61, .box_w = 5, .box_h = 11, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1534, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1544, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1553, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1563, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1573, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1583, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1593, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1603, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1610, .adv_w = 126, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1619, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1628, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1637, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1646, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1655, .adv_w = 113, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1668, .adv_w = 127, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1681, .adv_w = 113, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1694, .adv_w = 114, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1695, .adv_w = 228, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1696, .adv_w = 114, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1697, .adv_w = 228, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1698, .adv_w = 76, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1699, .adv_w = 57, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1700, .adv_w = 38, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1701, .adv_w = 126, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1702, .adv_w = 61, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1703, .adv_w = 46, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1704, .adv_w = 23, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1705, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1706, .adv_w = 88, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1707, .adv_w = 88, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1708, .adv_w = 141, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1709, .adv_w = 171, .box_w = 9, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1711, .adv_w = 171, .box_w = 9, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1713, .adv_w = 100, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1716, .adv_w = 52, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1718, .adv_w = 51, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1720, .adv_w = 56, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1722, .adv_w = 47, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1724, .adv_w = 90, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1727, .adv_w = 91, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1730, .adv_w = 90, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1733, .adv_w = 121, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1744, .adv_w = 130, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1758, .adv_w = 81, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1760, .adv_w = 117, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1761, .adv_w = 166, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1762, .adv_w = 58, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1763, .adv_w = 215, .box_w = 13, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1781, .adv_w = 36, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1782, .adv_w = 71, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1784, .adv_w = 70, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1787, .adv_w = 68, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1790, .adv_w = 121, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1799, .adv_w = 100, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1806, .adv_w = 123, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1817, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1827, .adv_w = 182, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1841, .adv_w = 193, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1855, .adv_w = 243, .box_w = 14, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1875, .adv_w = 182, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1891, .adv_w = 195, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1902, .adv_w = 129, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1915, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1925, .adv_w = 167, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1939, .adv_w = 118, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1948, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1958, .adv_w = 153, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1966, .adv_w = 158, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0}
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
    -7, -7, -27, -27, -27, -27, -27, -27,
    -27, -27, -27, -27, -27, -27, -27, -27,
    -27, -27, -27, -27, -26, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -27,
    -27, -27, -27, -27, -27, -27, -27, -27,
    -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -27, -27, -27, -27, -27,
    -27, -27, -27, -27, -27, -27, -27, -27,
    -27, -27, -27, -27, -27, -27, -27, -27,
    -27, -27, -27, -27, -27, -27, -7, -7,
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

extern const lv_font_t roboto_bold_14;


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t roboto_bold_14 = {
#else
lv_font_t roboto_bold_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &roboto_bold_14,
#endif
    .user_data = NULL,
};



#endif /*#if ROBOTO_BOLD_14*/
