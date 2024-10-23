#include "EPD.h"

void fullscreen_qrcode(const char *data)
{
    lv_obj_t * qr = lv_qrcode_create(lv_screen_active());
    lv_color_t bg_color = lv_color_white();
    lv_color_t fg_color = lv_color_black();

    lv_qrcode_set_size(qr, 150);
    lv_qrcode_set_dark_color(qr, fg_color);
    lv_qrcode_set_light_color(qr, bg_color);

    lv_qrcode_update(qr, data, strlen(data));
    lv_obj_center(qr);

    /*Add a border with bg_color*/
    lv_obj_set_style_border_color(qr, bg_color, 0);
    lv_obj_set_style_border_width(qr, 5, 0);
}
