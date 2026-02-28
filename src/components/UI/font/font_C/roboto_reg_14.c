/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --stride 1 --align 1 --font Roboto-Regular.ttf --range 32-127,160-255,8352-8399,8192-8303 --format lvgl -o roboto_reg_14.c
 ******************************************************************************/

#include "UI.h"

#ifndef ROBOTO_REG_14
#define ROBOTO_REG_14 1
#endif

#if ROBOTO_REG_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfe, 0x20,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x12, 0x14, 0x14, 0x7f, 0x24, 0x24, 0x24, 0xfe,
    0x28, 0x28, 0x28,

    /* U+0024 "$" */
    0x10, 0x43, 0x9f, 0x45, 0x16, 0x4, 0xe, 0x18,
    0x7f, 0x78, 0x41, 0x0,

    /* U+0025 "%" */
    0x60, 0x49, 0x24, 0x92, 0x86, 0x40, 0x40, 0x4c,
    0x29, 0x24, 0x92, 0x40, 0xc0,

    /* U+0026 "&" */
    0x38, 0x44, 0x44, 0x4c, 0x38, 0x70, 0xd2, 0x8a,
    0x8e, 0xce, 0x7a,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x5, 0x29, 0x24, 0x92, 0x24, 0x88,

    /* U+0029 ")" */
    0x11, 0x22, 0x49, 0x24, 0xa4, 0xa0,

    /* U+002A "*" */
    0x21, 0x3e, 0x45, 0x6c,

    /* U+002B "+" */
    0x10, 0x20, 0x40, 0x8f, 0xe2, 0x4, 0x8, 0x10,

    /* U+002C "," */
    0x54,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x8, 0x44, 0x21, 0x10, 0x84, 0x42, 0x31, 0x0,

    /* U+0030 "0" */
    0x79, 0x28, 0x61, 0x86, 0x18, 0x61, 0x85, 0x27,
    0x80,

    /* U+0031 "1" */
    0x1f, 0x91, 0x11, 0x11, 0x11, 0x10,

    /* U+0032 "2" */
    0x79, 0x9a, 0x10, 0x20, 0x41, 0x4, 0x18, 0x60,
    0x83, 0xf8,

    /* U+0033 "3" */
    0x7b, 0x18, 0x41, 0xc, 0xe0, 0xc1, 0x87, 0x37,
    0x80,

    /* U+0034 "4" */
    0x4, 0x18, 0x50, 0xa2, 0x44, 0x91, 0x7f, 0x4,
    0x8, 0x10,

    /* U+0035 "5" */
    0x7d, 0x4, 0x10, 0xf9, 0x30, 0x41, 0x87, 0x37,
    0x80,

    /* U+0036 "6" */
    0x39, 0x84, 0x20, 0xbb, 0x38, 0x61, 0x85, 0x37,
    0x80,

    /* U+0037 "7" */
    0xfe, 0xc, 0x10, 0x20, 0x81, 0x6, 0x8, 0x30,
    0x40, 0x80,

    /* U+0038 "8" */
    0x7b, 0x38, 0x61, 0xcd, 0xec, 0xe1, 0x87, 0x37,
    0x80,

    /* U+0039 "9" */
    0x73, 0x28, 0x61, 0x87, 0x37, 0x41, 0x8, 0x67,
    0x0,

    /* U+003A ":" */
    0x81,

    /* U+003B ";" */
    0x87, 0x80,

    /* U+003C "<" */
    0x4, 0x66, 0x30, 0x70, 0x70, 0x40,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x83, 0x81, 0x83, 0x3b, 0x0, 0x0,

    /* U+003F "?" */
    0x76, 0x62, 0x11, 0x88, 0x84, 0x0, 0x8,

    /* U+0040 "@" */
    0xf, 0x6, 0x11, 0x1, 0x27, 0x38, 0x93, 0x22,
    0x64, 0x4c, 0x91, 0x92, 0x32, 0x6b, 0x37, 0x20,
    0x2, 0x0, 0x3c, 0x0,

    /* U+0041 "A" */
    0xc, 0x7, 0x1, 0xc0, 0x58, 0x36, 0xc, 0x82,
    0x31, 0xfc, 0x61, 0x90, 0x24, 0x8,

    /* U+0042 "B" */
    0xf9, 0xa, 0x14, 0x28, 0xdf, 0x21, 0xc1, 0x83,
    0xf, 0xf0,

    /* U+0043 "C" */
    0x3c, 0x8e, 0xc, 0x18, 0x10, 0x20, 0x40, 0x82,
    0x8c, 0xf0,

    /* U+0044 "D" */
    0xf9, 0x1a, 0x14, 0x18, 0x30, 0x60, 0xc1, 0x85,
    0x1b, 0xe0,

    /* U+0045 "E" */
    0xfe, 0x8, 0x20, 0x83, 0xe8, 0x20, 0x82, 0xf,
    0xc0,

    /* U+0046 "F" */
    0xfe, 0x8, 0x20, 0x83, 0xe8, 0x20, 0x82, 0x8,
    0x0,

    /* U+0047 "G" */
    0x3c, 0x42, 0xc1, 0x80, 0x80, 0x80, 0x8f, 0x81,
    0xc1, 0x61, 0x3e,

    /* U+0048 "H" */
    0x81, 0x81, 0x81, 0x81, 0x81, 0xff, 0x81, 0x81,
    0x81, 0x81, 0x81,

    /* U+0049 "I" */
    0xff, 0xe0,

    /* U+004A "J" */
    0x4, 0x10, 0x41, 0x4, 0x10, 0x41, 0x87, 0x37,
    0x80,

    /* U+004B "K" */
    0x87, 0x1a, 0x64, 0x8a, 0x1e, 0x34, 0x4c, 0x8d,
    0xa, 0x18,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x82, 0xf,
    0xc0,

    /* U+004D "M" */
    0xc0, 0xf0, 0x3c, 0xe, 0x85, 0xa1, 0x6c, 0xd9,
    0x26, 0x49, 0x8c, 0x63, 0x18, 0xc4,

    /* U+004E "N" */
    0x81, 0xc1, 0xe1, 0xa1, 0xb1, 0x99, 0x8d, 0x8d,
    0x87, 0x83, 0x81,

    /* U+004F "O" */
    0x3c, 0x42, 0xc3, 0x81, 0x81, 0x81, 0x81, 0x81,
    0xc3, 0x42, 0x3c,

    /* U+0050 "P" */
    0xfd, 0xa, 0xc, 0x18, 0x30, 0xff, 0x40, 0x81,
    0x2, 0x0,

    /* U+0051 "Q" */
    0x3c, 0x42, 0xc3, 0x81, 0x81, 0x81, 0x81, 0x81,
    0xc3, 0x42, 0x3e, 0x3, 0x0,

    /* U+0052 "R" */
    0xfd, 0xe, 0xc, 0x18, 0x30, 0xbe, 0x46, 0x85,
    0xe, 0x8,

    /* U+0053 "S" */
    0x3c, 0x62, 0x41, 0x40, 0x70, 0x1c, 0x7, 0x1,
    0x41, 0x63, 0x3e,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x40,

    /* U+0055 "U" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+0056 "V" */
    0xc1, 0xa0, 0x90, 0x4c, 0x62, 0x21, 0x10, 0xd8,
    0x28, 0x14, 0xe, 0x2, 0x0,

    /* U+0057 "W" */
    0x42, 0x14, 0x63, 0x46, 0x34, 0x52, 0x65, 0x22,
    0xd2, 0x29, 0x62, 0x8c, 0x28, 0xc3, 0xc, 0x10,
    0xc0,

    /* U+0058 "X" */
    0x43, 0x62, 0x26, 0x34, 0x1c, 0x8, 0x1c, 0x34,
    0x26, 0x63, 0x41,

    /* U+0059 "Y" */
    0x83, 0x8d, 0x13, 0x62, 0x87, 0x4, 0x8, 0x10,
    0x20, 0x40,

    /* U+005A "Z" */
    0xfe, 0xc, 0x30, 0x41, 0x82, 0x8, 0x30, 0x41,
    0x3, 0xf8,

    /* U+005B "[" */
    0xea, 0xaa, 0xaa, 0xb0,

    /* U+005C "\\" */
    0xc1, 0x4, 0x8, 0x20, 0x81, 0x4, 0x18, 0x20,
    0x83,

    /* U+005D "]" */
    0xd5, 0x55, 0x55, 0x70,

    /* U+005E "^" */
    0x21, 0x8c, 0xe4, 0xa4,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0x44,

    /* U+0061 "a" */
    0x7b, 0x10, 0x5f, 0xc6, 0x18, 0xdd,

    /* U+0062 "b" */
    0x82, 0x8, 0x2e, 0xce, 0x18, 0x61, 0x87, 0x3b,
    0x80,

    /* U+0063 "c" */
    0x79, 0x38, 0x60, 0x82, 0x14, 0xde,

    /* U+0064 "d" */
    0x4, 0x10, 0x5d, 0xce, 0x18, 0x61, 0x85, 0x37,
    0x40,

    /* U+0065 "e" */
    0x39, 0x38, 0x7f, 0x82, 0x4, 0x5e,

    /* U+0066 "f" */
    0x3a, 0x11, 0xe4, 0x21, 0x8, 0x42, 0x10,

    /* U+0067 "g" */
    0x77, 0x38, 0x61, 0x86, 0x14, 0xdd, 0x6, 0x37,
    0x80,

    /* U+0068 "h" */
    0x82, 0x8, 0x2e, 0xc6, 0x18, 0x61, 0x86, 0x18,
    0x40,

    /* U+0069 "i" */
    0x9f, 0xe0,

    /* U+006A "j" */
    0x20, 0x12, 0x49, 0x24, 0x93, 0x80,

    /* U+006B "k" */
    0x82, 0x8, 0x22, 0x92, 0x8e, 0x38, 0x92, 0x68,
    0xc0,

    /* U+006C "l" */
    0xff, 0xe0,

    /* U+006D "m" */
    0xb9, 0xd8, 0xc6, 0x10, 0xc2, 0x18, 0x43, 0x8,
    0x61, 0xc, 0x21,

    /* U+006E "n" */
    0xbb, 0x18, 0x61, 0x86, 0x18, 0x61,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c,

    /* U+0070 "p" */
    0xbb, 0x38, 0x61, 0x86, 0x18, 0xbe, 0x82, 0x8,
    0x0,

    /* U+0071 "q" */
    0x77, 0x38, 0x61, 0x86, 0x1c, 0xdd, 0x4, 0x10,
    0x40,

    /* U+0072 "r" */
    0xfa, 0x49, 0x24,

    /* U+0073 "s" */
    0x39, 0x14, 0x1c, 0x1c, 0x14, 0x4e,

    /* U+0074 "t" */
    0x4b, 0xa4, 0x92, 0x4c,

    /* U+0075 "u" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0xdf,

    /* U+0076 "v" */
    0xc4, 0x89, 0x33, 0x42, 0x85, 0xc, 0x8,

    /* U+0077 "w" */
    0xc4, 0x53, 0x14, 0xcd, 0x2a, 0x72, 0x8c, 0xa3,
    0x10, 0xc4,

    /* U+0078 "x" */
    0x44, 0xd8, 0xa1, 0x83, 0x5, 0x1b, 0x22,

    /* U+0079 "y" */
    0xc5, 0x14, 0xda, 0x28, 0xa3, 0x4, 0x10, 0x86,
    0x0,

    /* U+007A "z" */
    0xfc, 0x31, 0x8c, 0x31, 0x8c, 0x3f,

    /* U+007B "{" */
    0x5, 0x24, 0x94, 0x49, 0x24, 0x40,

    /* U+007C "|" */
    0xff, 0xf8,

    /* U+007D "}" */
    0x99, 0x24, 0x99, 0x69, 0x25, 0xa0,

    /* U+007E "~" */
    0x71, 0x9b, 0x8e,

    /* U+00A0 " " */
    0x0,

    /* U+00A1 "¡" */
    0x9f, 0xc0,

    /* U+00A2 "¢" */
    0x10, 0x47, 0x9f, 0x86, 0x8, 0x21, 0x7d, 0xe1,
    0x4,

    /* U+00A3 "£" */
    0x3c, 0xcd, 0x1a, 0x4, 0x1e, 0x10, 0x20, 0x40,
    0x83, 0xf8,

    /* U+00A4 "¤" */
    0xbd, 0x43, 0xc3, 0x81, 0x81, 0x81, 0xc3, 0xc3,
    0xbd,

    /* U+00A5 "¥" */
    0xc6, 0x89, 0x11, 0x42, 0x87, 0x1f, 0x8, 0x7c,
    0x20, 0x40,

    /* U+00A6 "¦" */
    0xfb, 0xf0,

    /* U+00A7 "§" */
    0x7d, 0x8e, 0xc, 0x7, 0x13, 0xa1, 0xc1, 0x72,
    0x38, 0xc, 0x1c, 0x6f, 0x80,

    /* U+00A8 "¨" */
    0x90,

    /* U+00A9 "©" */
    0x1e, 0x8, 0x45, 0xca, 0x89, 0xa0, 0x68, 0x1a,
    0x6, 0x89, 0x5c, 0x88, 0x41, 0xe0,

    /* U+00AA "ª" */
    0x79, 0xf9, 0xf0,

    /* U+00AB "«" */
    0x4a, 0xa9, 0x45, 0x24,

    /* U+00AC "¬" */
    0xfc, 0x10, 0x40,

    /* U+00AD "­" */
    0xe0,

    /* U+00AE "®" */
    0x1e, 0x8, 0x45, 0xca, 0x49, 0x92, 0x67, 0x99,
    0x26, 0x49, 0x40, 0x88, 0x41, 0xe0,

    /* U+00AF "¯" */
    0xf8,

    /* U+00B0 "°" */
    0x69, 0x96,

    /* U+00B1 "±" */
    0x20, 0x82, 0x3f, 0x20, 0x82, 0x0, 0xfc,

    /* U+00B2 "²" */
    0xf9, 0x24, 0xf0,

    /* U+00B3 "³" */
    0xf1, 0x71, 0xf0,

    /* U+00B4 "´" */
    0x50,

    /* U+00B5 "µ" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x7f, 0x82, 0x8,
    0x0,

    /* U+00B6 "¶" */
    0x7f, 0xff, 0xff, 0xfd, 0xe1, 0x8, 0x42,

    /* U+00B7 "·" */
    0x80,

    /* U+00B8 "¸" */
    0x9c,

    /* U+00B9 "¹" */
    0xd5, 0x40,

    /* U+00BA "º" */
    0x74, 0x63, 0x17, 0x0,

    /* U+00BB "»" */
    0xa2, 0x92, 0x95, 0x50,

    /* U+00BC "¼" */
    0xc0, 0x21, 0x11, 0x9, 0x84, 0x92, 0x98, 0x4c,
    0x4a, 0x6f, 0x80, 0x80,

    /* U+00BD "½" */
    0x40, 0x60, 0x11, 0x8, 0x84, 0x82, 0x98, 0x52,
    0x41, 0x21, 0x21, 0x1, 0xe0,

    /* U+00BE "¾" */
    0xf0, 0x4, 0x47, 0x22, 0x48, 0xf4, 0x81, 0x60,
    0xa8, 0x4a, 0x17, 0xc0, 0x20,

    /* U+00BF "¿" */
    0x20, 0x0, 0x8, 0x21, 0xc, 0x20, 0x8e, 0x27,
    0x0,

    /* U+00C0 "À" */
    0x10, 0x6, 0x0, 0xc0, 0x30, 0x1c, 0x7, 0x1,
    0x60, 0xd8, 0x32, 0x8, 0xc7, 0xf1, 0x86, 0x40,
    0x90, 0x20,

    /* U+00C1 "Á" */
    0x6, 0x1, 0x0, 0x80, 0x30, 0x1c, 0x7, 0x1,
    0x60, 0xd8, 0x32, 0x8, 0xc7, 0xf1, 0x86, 0x40,
    0x90, 0x20,

    /* U+00C2 "Â" */
    0x8, 0x5, 0x0, 0x20, 0x30, 0x1c, 0x7, 0x1,
    0x60, 0xd8, 0x32, 0x8, 0xc7, 0xf1, 0x86, 0x40,
    0x90, 0x20,

    /* U+00C3 "Ã" */
    0x1a, 0x9, 0x80, 0xc0, 0x70, 0x1c, 0x5, 0x83,
    0x60, 0xc8, 0x23, 0x1f, 0xc6, 0x19, 0x2, 0x40,
    0x80,

    /* U+00C4 "Ä" */
    0x12, 0x0, 0x0, 0xc0, 0x70, 0x1c, 0x5, 0x81,
    0x60, 0xcc, 0x23, 0xf, 0xc6, 0x19, 0x2, 0x40,
    0x80,

    /* U+00C5 "Å" */
    0x1c, 0x5, 0x1, 0xc0, 0x20, 0x1c, 0x7, 0x1,
    0x40, 0x58, 0x32, 0x8, 0xc3, 0xf1, 0x84, 0x40,
    0x90, 0x20,

    /* U+00C6 "Æ" */
    0x3, 0xf8, 0x38, 0x1, 0x40, 0x1a, 0x0, 0x90,
    0xc, 0xf8, 0x44, 0x7, 0xe0, 0x21, 0x3, 0x8,
    0x10, 0x7e,

    /* U+00C7 "Ç" */
    0x3c, 0x42, 0xc3, 0x81, 0x80, 0x80, 0x80, 0x80,
    0x83, 0x42, 0x3c, 0x18, 0x8, 0x18,

    /* U+00C8 "È" */
    0x40, 0x82, 0x3f, 0x82, 0x8, 0x20, 0xfa, 0x8,
    0x20, 0x83, 0xf0,

    /* U+00C9 "É" */
    0x18, 0x42, 0x3f, 0x82, 0x8, 0x20, 0xfa, 0x8,
    0x20, 0x83, 0xf0,

    /* U+00CA "Ê" */
    0x20, 0xc4, 0xbf, 0x82, 0x8, 0x20, 0xfa, 0x8,
    0x20, 0x83, 0xf0,

    /* U+00CB "Ë" */
    0x48, 0xf, 0xe0, 0x82, 0x8, 0x3e, 0x82, 0x8,
    0x20, 0xfc,

    /* U+00CC "Ì" */
    0xb5, 0x55, 0x55, 0x50,

    /* U+00CD "Í" */
    0x7a, 0xaa, 0xaa, 0xa0,

    /* U+00CE "Î" */
    0x56, 0xa4, 0x92, 0x49, 0x24, 0x80,

    /* U+00CF "Ï" */
    0x90, 0x22, 0x22, 0x22, 0x22, 0x22, 0x20,

    /* U+00D0 "Ð" */
    0x7c, 0x46, 0x42, 0x41, 0x41, 0xf1, 0x41, 0x41,
    0x42, 0x46, 0x7c,

    /* U+00D1 "Ñ" */
    0x32, 0x4c, 0x81, 0xc1, 0xe1, 0xa1, 0xb1, 0x99,
    0x8d, 0x8d, 0x87, 0x83, 0x81,

    /* U+00D2 "Ò" */
    0x20, 0x10, 0x8, 0x3c, 0x42, 0xc3, 0x81, 0x81,
    0x81, 0x81, 0x81, 0xc3, 0x42, 0x3c,

    /* U+00D3 "Ó" */
    0x4, 0x8, 0x10, 0x3c, 0x42, 0xc3, 0x81, 0x81,
    0x81, 0x81, 0x81, 0xc3, 0x42, 0x3c,

    /* U+00D4 "Ô" */
    0x0, 0x18, 0x24, 0x3c, 0x42, 0xc3, 0x81, 0x81,
    0x81, 0x81, 0x81, 0xc3, 0x42, 0x3c,

    /* U+00D5 "Õ" */
    0x3c, 0x0, 0x3c, 0x42, 0xc3, 0x81, 0x81, 0x81,
    0x81, 0x81, 0xc3, 0x42, 0x3c,

    /* U+00D6 "Ö" */
    0x24, 0x0, 0x3c, 0x42, 0xc3, 0x81, 0x81, 0x81,
    0x81, 0x81, 0xc3, 0x42, 0x3c,

    /* U+00D7 "×" */
    0x8f, 0x67, 0xc, 0x5a, 0x30, 0x0,

    /* U+00D8 "Ø" */
    0x3d, 0x42, 0xc3, 0x85, 0x89, 0x89, 0x91, 0xa1,
    0xe3, 0x42, 0x7c, 0x80,

    /* U+00D9 "Ù" */
    0x60, 0x60, 0x44, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xc, 0x14, 0x47, 0x0,

    /* U+00DA "Ú" */
    0xc, 0x30, 0x44, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xc, 0x14, 0x47, 0x0,

    /* U+00DB "Û" */
    0x10, 0x51, 0x14, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xc, 0x14, 0x47, 0x0,

    /* U+00DC "Ü" */
    0x24, 0x2, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xa, 0x23, 0x80,

    /* U+00DD "Ý" */
    0xc, 0x30, 0x44, 0x1c, 0x68, 0x9b, 0x14, 0x38,
    0x20, 0x40, 0x81, 0x2, 0x0,

    /* U+00DE "Þ" */
    0x82, 0x8, 0x3e, 0x8e, 0x18, 0x63, 0xfa, 0x8,
    0x0,

    /* U+00DF "ß" */
    0x71, 0x12, 0x24, 0x49, 0x12, 0x22, 0x43, 0x83,
    0x6, 0xf0,

    /* U+00E0 "à" */
    0x60, 0xc0, 0x1e, 0xc4, 0x17, 0xf1, 0x86, 0x37,
    0x40,

    /* U+00E1 "á" */
    0x8, 0x40, 0x1e, 0xc4, 0x17, 0xf1, 0x86, 0x37,
    0x40,

    /* U+00E2 "â" */
    0x31, 0xa0, 0x1e, 0xc4, 0x17, 0xf1, 0x86, 0x37,
    0x40,

    /* U+00E3 "ã" */
    0x65, 0x60, 0x1e, 0xc4, 0x17, 0xf1, 0x86, 0x37,
    0x40,

    /* U+00E4 "ä" */
    0x48, 0x0, 0x1e, 0xc4, 0x17, 0xf1, 0x86, 0x37,
    0x40,

    /* U+00E5 "å" */
    0x38, 0xa3, 0x80, 0x7b, 0x10, 0x5f, 0xc6, 0x18,
    0xdd,

    /* U+00E6 "æ" */
    0x7b, 0xb1, 0x90, 0x45, 0xff, 0xc4, 0x21, 0x8,
    0xe5, 0xef,

    /* U+00E7 "ç" */
    0x79, 0x38, 0x60, 0x82, 0x14, 0xde, 0x30, 0x43,
    0x0,

    /* U+00E8 "è" */
    0x60, 0x80, 0xe, 0x4e, 0x1f, 0xe0, 0x81, 0x17,
    0x80,

    /* U+00E9 "é" */
    0x18, 0x40, 0xe, 0x4e, 0x1f, 0xe0, 0x81, 0x17,
    0x80,

    /* U+00EA "ê" */
    0x31, 0x20, 0xe, 0x4e, 0x1f, 0xe0, 0x81, 0x17,
    0x80,

    /* U+00EB "ë" */
    0x48, 0x0, 0xe, 0x4e, 0x1f, 0xe0, 0x81, 0x37,
    0x80,

    /* U+00EC "ì" */
    0x91, 0x55, 0x54,

    /* U+00ED "í" */
    0x50, 0x49, 0x24, 0x92, 0x0,

    /* U+00EE "î" */
    0x54, 0x24, 0x92, 0x49, 0x0,

    /* U+00EF "ï" */
    0x90, 0x2, 0x22, 0x22, 0x22, 0x20,

    /* U+00F0 "ð" */
    0x60, 0xe2, 0x82, 0x77, 0x38, 0x61, 0x87, 0x27,
    0x80,

    /* U+00F1 "ñ" */
    0x66, 0x60, 0x2e, 0xc6, 0x18, 0x61, 0x86, 0x18,
    0x40,

    /* U+00F2 "ò" */
    0x60, 0x60, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+00F3 "ó" */
    0x8, 0x20, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+00F4 "ô" */
    0x30, 0xd0, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+00F5 "õ" */
    0x74, 0xb8, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+00F6 "ö" */
    0x48, 0x0, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+00F7 "÷" */
    0x10, 0x0, 0x7, 0xf0, 0x0, 0x4, 0x0,

    /* U+00F8 "ø" */
    0x4, 0x79, 0x34, 0x59, 0x32, 0x68, 0xb2, 0x78,
    0x80,

    /* U+00F9 "ù" */
    0x60, 0xc0, 0x21, 0x86, 0x18, 0x61, 0x86, 0x37,
    0xc0,

    /* U+00FA "ú" */
    0x18, 0x40, 0x21, 0x86, 0x18, 0x61, 0x86, 0x37,
    0xc0,

    /* U+00FB "û" */
    0x31, 0x20, 0x21, 0x86, 0x18, 0x61, 0x86, 0x37,
    0xc0,

    /* U+00FC "ü" */
    0x48, 0x0, 0x21, 0x86, 0x18, 0x61, 0x86, 0x37,
    0x40,

    /* U+00FD "ý" */
    0x8, 0x40, 0x31, 0x45, 0x36, 0x8a, 0x28, 0xc1,
    0x4, 0x21, 0x80,

    /* U+00FE "þ" */
    0x82, 0x8, 0x2e, 0xce, 0x18, 0x61, 0x86, 0x2f,
    0xa0, 0x82, 0x0,

    /* U+00FF "ÿ" */
    0x48, 0x0, 0x23, 0xc9, 0x24, 0x9c, 0x70, 0xc2,
    0x8, 0x23, 0x0,

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
    0xe0,

    /* U+2011 "‑" */
    0xe0,

    /* U+2013 "–" */
    0xfe,

    /* U+2014 "—" */
    0xff, 0x80,

    /* U+2015 "―" */
    0xff, 0x80,

    /* U+2017 "‗" */
    0xfc, 0xf, 0xc0,

    /* U+2018 "‘" */
    0x2a,

    /* U+2019 "’" */
    0x54,

    /* U+201A "‚" */
    0x54,

    /* U+201B "‛" */
    0xa8,

    /* U+201C "“" */
    0xa, 0xaa,

    /* U+201D "”" */
    0x55, 0x50,

    /* U+201E "„" */
    0x55, 0x5a,

    /* U+2020 "†" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x40,

    /* U+2021 "‡" */
    0x10, 0x20, 0x47, 0xf1, 0x2, 0x4, 0x8, 0x10,
    0x23, 0xf8, 0x81, 0x2, 0x0,

    /* U+2022 "•" */
    0xff, 0x80,

    /* U+2025 "‥" */
    0x90,

    /* U+2026 "…" */
    0x92,

    /* U+2027 "‧" */
    0x80,

    /* U+2030 "‰" */
    0x60, 0x9, 0x20, 0x92, 0x9, 0x40, 0x64, 0x0,
    0x80, 0x13, 0x61, 0x49, 0x24, 0x92, 0x49, 0x3,
    0x60,

    /* U+2032 "′" */
    0xe0,

    /* U+2033 "″" */
    0xb6, 0x80,

    /* U+2039 "‹" */
    0x4a, 0x44, 0x80,

    /* U+203A "›" */
    0x99, 0x2d, 0x0,

    /* U+203C "‼" */
    0x8c, 0x63, 0x18, 0xc6, 0x20, 0x0, 0x22,

    /* U+2044 "⁄" */
    0x0, 0x10, 0x84, 0x10, 0x82, 0x10, 0x40,

    /* U+20A3 "₣" */
    0x7e, 0x81, 0x2, 0x4, 0xf, 0x90, 0x20, 0xf0,
    0x81, 0x0,

    /* U+20A4 "₤" */
    0x3c, 0xcd, 0x1a, 0x4, 0x1f, 0x10, 0x7c, 0x40,
    0x83, 0xf8,

    /* U+20A6 "₦" */
    0x41, 0x18, 0x47, 0x11, 0x44, 0xff, 0xd2, 0x4f,
    0xfd, 0x1c, 0x43, 0x10, 0xc4, 0x10,

    /* U+20A7 "₧" */
    0xf8, 0x46, 0xa1, 0x50, 0xf8, 0x54, 0x6b, 0xe5,
    0x2, 0x81, 0x40, 0xa0, 0x60,

    /* U+20A8 "₨" */
    0xfc, 0x4, 0x30, 0x20, 0x81, 0x4, 0xe8, 0x29,
    0xc2, 0x47, 0xe3, 0x91, 0x87, 0x84, 0xc, 0x3c,
    0x60, 0xbc,

    /* U+20A9 "₩" */
    0xcc, 0xf3, 0x24, 0xc9, 0x32, 0xff, 0xd7, 0xef,
    0xfc, 0xcc, 0x33, 0xc, 0xc3, 0x30,

    /* U+20AA "₪" */
    0xf8, 0xc2, 0x61, 0x32, 0x99, 0x4c, 0x86, 0x43,
    0x3e,

    /* U+20AB "₫" */
    0x4, 0x1f, 0x4, 0x74, 0xcc, 0x84, 0x84, 0x84,
    0x84, 0x4c, 0x74, 0x0, 0x7e,

    /* U+20AC "€" */
    0x1c, 0x84, 0x10, 0xf9, 0xf, 0x90, 0x40, 0x81,
    0xc0,

    /* U+20B1 "₱" */
    0x7e, 0x21, 0x3f, 0xe8, 0x2f, 0xfa, 0x19, 0xf8,
    0x80, 0x40, 0x20, 0x10, 0x0,

    /* U+20B9 "₹" */
    0xfe, 0x11, 0xff, 0xf0, 0x9e, 0x18, 0x18, 0x10,
    0x10,

    /* U+20BA "₺" */
    0x20, 0x50, 0xe7, 0xb, 0x8e, 0x78, 0x91, 0x26,
    0x48, 0xe0,

    /* U+20BC "₼" */
    0x10, 0x20, 0xe2, 0xa9, 0x32, 0x64, 0xc9,

    /* U+20BD "₽" */
    0x7e, 0x42, 0x41, 0x41, 0x41, 0x43, 0xfe, 0x40,
    0xf8, 0x40, 0x40
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 56, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 58, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 72, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 5, .adv_w = 138, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 126, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 28, .adv_w = 164, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 139, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 39, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 53, .adv_w = 77, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 59, .adv_w = 78, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 65, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 69, .adv_w = 127, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 77, .adv_w = 44, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 78, .adv_w = 62, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 79, .adv_w = 59, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 92, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 88, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 126, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 54, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 47, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 181, .adv_w = 114, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 187, .adv_w = 123, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 190, .adv_w = 117, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 196, .adv_w = 106, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 201, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 223, .adv_w = 146, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 146, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 147, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 127, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 160, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 61, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 121, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 196, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 160, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 396, .adv_w = 138, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 133, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 417, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 427, .adv_w = 145, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 143, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 199, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 140, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 488, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 498, .adv_w = 59, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 502, .adv_w = 92, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 511, .adv_w = 59, .box_w = 2, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 515, .adv_w = 94, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 519, .adv_w = 101, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 520, .adv_w = 69, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 521, .adv_w = 122, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 117, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 119, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 78, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 573, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 54, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 584, .adv_w = 54, .box_w = 3, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 590, .adv_w = 114, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 54, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 601, .adv_w = 196, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 124, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 625, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 634, .adv_w = 127, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 643, .adv_w = 76, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 116, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 652, .adv_w = 73, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 123, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 109, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 168, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 686, .adv_w = 106, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 695, .adv_w = 111, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 701, .adv_w = 76, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 707, .adv_w = 55, .box_w = 1, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 709, .adv_w = 76, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 715, .adv_w = 152, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 718, .adv_w = 56, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 719, .adv_w = 55, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 721, .adv_w = 123, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 730, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 740, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 749, .adv_w = 118, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 759, .adv_w = 54, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 761, .adv_w = 137, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 774, .adv_w = 94, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 775, .adv_w = 176, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 789, .adv_w = 100, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 792, .adv_w = 105, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 796, .adv_w = 124, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 799, .adv_w = 62, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 800, .adv_w = 176, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 814, .adv_w = 103, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 815, .adv_w = 84, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 817, .adv_w = 120, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 82, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 827, .adv_w = 82, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 830, .adv_w = 70, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 831, .adv_w = 127, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 840, .adv_w = 110, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 847, .adv_w = 59, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 848, .adv_w = 56, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 849, .adv_w = 82, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 851, .adv_w = 102, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 855, .adv_w = 105, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 859, .adv_w = 164, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 871, .adv_w = 174, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 884, .adv_w = 174, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 897, .adv_w = 106, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 906, .adv_w = 146, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 924, .adv_w = 146, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 942, .adv_w = 146, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 960, .adv_w = 146, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 977, .adv_w = 146, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 994, .adv_w = 146, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1012, .adv_w = 209, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1030, .adv_w = 146, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1044, .adv_w = 127, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1055, .adv_w = 127, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1066, .adv_w = 127, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1077, .adv_w = 127, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1087, .adv_w = 61, .box_w = 2, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1091, .adv_w = 61, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1095, .adv_w = 61, .box_w = 3, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1101, .adv_w = 61, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1108, .adv_w = 150, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1119, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1132, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1146, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1160, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1174, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1187, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1200, .adv_w = 120, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1206, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1218, .adv_w = 145, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1231, .adv_w = 145, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1244, .adv_w = 145, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1257, .adv_w = 145, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1269, .adv_w = 135, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1282, .adv_w = 132, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1291, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1301, .adv_w = 122, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1310, .adv_w = 122, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1319, .adv_w = 122, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1328, .adv_w = 122, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1337, .adv_w = 122, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1346, .adv_w = 122, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1355, .adv_w = 189, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1365, .adv_w = 117, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1374, .adv_w = 119, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1383, .adv_w = 119, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1392, .adv_w = 119, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1401, .adv_w = 119, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1410, .adv_w = 55, .box_w = 2, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1413, .adv_w = 55, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1418, .adv_w = 55, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1423, .adv_w = 55, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1429, .adv_w = 131, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1438, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1447, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1457, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1467, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1477, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1487, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1497, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1504, .adv_w = 127, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1513, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1522, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1531, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1540, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1549, .adv_w = 106, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1560, .adv_w = 129, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1571, .adv_w = 106, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1582, .adv_w = 114, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1583, .adv_w = 228, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1584, .adv_w = 114, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1585, .adv_w = 228, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1586, .adv_w = 76, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1587, .adv_w = 57, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1588, .adv_w = 38, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1589, .adv_w = 126, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1590, .adv_w = 61, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1591, .adv_w = 46, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1592, .adv_w = 23, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1593, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1594, .adv_w = 62, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1595, .adv_w = 62, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1596, .adv_w = 147, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1597, .adv_w = 175, .box_w = 9, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1599, .adv_w = 175, .box_w = 9, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1601, .adv_w = 102, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1604, .adv_w = 45, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1605, .adv_w = 45, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1606, .adv_w = 45, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1607, .adv_w = 45, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1608, .adv_w = 79, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1610, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1612, .adv_w = 77, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1614, .adv_w = 124, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1624, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1637, .adv_w = 76, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1639, .adv_w = 105, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1640, .adv_w = 150, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1641, .adv_w = 42, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1642, .adv_w = 215, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1659, .adv_w = 39, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1660, .adv_w = 72, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1662, .adv_w = 67, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1665, .adv_w = 67, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1668, .adv_w = 116, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1675, .adv_w = 102, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1682, .adv_w = 124, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1692, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1702, .adv_w = 177, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1716, .adv_w = 184, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1729, .adv_w = 237, .box_w = 13, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1747, .adv_w = 166, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1761, .adv_w = 173, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1770, .adv_w = 130, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1783, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1792, .adv_w = 164, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1805, .adv_w = 116, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1814, .adv_w = 125, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1824, .adv_w = 148, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1831, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
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
    -12, -12, -12, -12, -12, -12, -12, -12,
    -12, -12, -12, -12, -12, -12, -12, -12,
    -12, -12, -19, -19, -19, -19, -19, -19,
    -19, -19, -19, -19, -19, -19, -19, -19,
    -19, -19, -19, -19, -24, -12, -12, -12,
    -12, -12, -12, -12, -12, -12, -12, -12,
    -12, -12, -12, -12, -12, -12, -12, -19,
    -19, -19, -19, -19, -19, -19, -19, -19,
    -12, -12, -12, -12, -12, -12, -12, -12,
    -12, -12, -12, -12, -12, -12, -12, -12,
    -12, -12, -12, -12, -12, -12, -12, -12,
    -12, -12, -12, -19, -19, -19, -19, -19,
    -19, -19, -19, -19, -19, -19, -19, -19,
    -19, -19, -19, -19, -19, -19, -19, -19,
    -19, -19, -19, -19, -19, -19, -12, -12,
    -12, -12, -12, -12, -12, -12, -12, -12,
    -12, -12, -12, -12, -12, -12, -12, -12
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

extern const lv_font_t roboto_reg_14;


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t roboto_reg_14 = {
#else
lv_font_t roboto_reg_14 = {
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
    .fallback = &roboto_reg_14,
#endif
    .user_data = NULL,
};



#endif /*#if ROBOTO_REG_14*/
