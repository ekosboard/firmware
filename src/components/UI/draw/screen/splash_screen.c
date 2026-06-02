#include "UI.h"
#include "core/lv_obj_pos.h"
#include "core/lv_obj_style_gen.h"
#include "display/lv_display.h"
#include "misc/lv_area.h"
#include "misc/lv_style_gen.h"
#include "misc/lv_types.h"
#include "widgets/image/lv_image.h"
#include "widgets/label/lv_label.h"
#include <stdio.h>

static lv_obj_t *icon_logo;
static lv_obj_t *wifi_state;

void splash_screen_set_wifi_state(const char *ssid)
{
    char buff[256];
    snprintf(buff, sizeof(buff), "Connected to %s", ssid);
    lv_label_set_text(wifi_state, buff);
    lv_obj_align_to(wifi_state, icon_logo, LV_ALIGN_BOTTOM_MID, 0, 80);
}

void draw_splash_screen(void)
{
    lv_obj_clean(lv_screen_active());

    icon_logo = lv_image_create(lv_screen_active());
    lv_image_set_src(icon_logo, &logo);
    lv_obj_center(icon_logo);

    wifi_state = lv_label_create(lv_screen_active());
    lv_label_set_text(wifi_state, "");
    lv_obj_set_style_text_font(wifi_state, &roboto_reg_22, 0);
}
