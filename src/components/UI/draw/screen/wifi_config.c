#include "UI.h"
#include "core/lv_obj_style.h"
#include "core/lv_refr_private.h"
#include "font/lv_symbol_def.h"
#include "lv_conf_internal.h"
#include "misc/lv_area.h"
#include "misc/lv_color.h"
#include "misc/lv_style.h"
#include "misc/lv_style_gen.h"
#include "misc/lv_types.h"

static void wifi_config_top_label(void)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, &lv_font_montserrat_20);

    lv_obj_t *title_label;
    title_label = lv_label_create(lv_screen_active());
    lv_label_set_long_mode(title_label, LV_LABEL_LONG_WRAP);
    lv_label_set_text(title_label, "Follow the instructions on the application");

    lv_obj_add_style(title_label, &style, 0);
    lv_obj_set_width(title_label, 400);
    lv_obj_set_style_text_align(title_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 0);
}

void draw_screen_wifi_config(const char *data)
{
    lv_obj_clean(lv_screen_active());
    wifi_config_top_label();
    fullscreen_qrcode(data);
    btn_bottom_left("GET THE APP");
    btn_bottom_right("HELP");
}
