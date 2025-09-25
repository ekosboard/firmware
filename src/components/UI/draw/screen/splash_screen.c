#include "UI.h"

void draw_splash_screen(void)
{
    lv_obj_clean(lv_screen_active());

    lv_obj_t * icon_logo = lv_image_create(lv_screen_active());
    lv_image_set_src(icon_logo, &logo);
    lv_obj_center(icon_logo);
}
