#include "widget.h"
#include "widget/{{NAME}}.h"
#include "widget_autogen.h"

esp_err_t widget_{{NAME}}_draw(lv_obj_t *screen)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_{{NAME_UPPER}}, &widget) != ESP_OK)
        return ESP_FAIL;

    widget_{{NAME}}(screen, widget);
    return ESP_OK;
}

esp_err_t widget_{{NAME}}_erase(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_{{NAME_UPPER}}, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_delete(widget->lv_obj);
    return ESP_OK;
}

esp_err_t widget_{{NAME}}_update(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_{{NAME_UPPER}}, &widget) != ESP_OK)
        return ESP_FAIL;

    lv_obj_set_size(widget->lv_obj, widget->width, widget->height);
    lv_obj_set_pos(widget->lv_obj, widget->pos_x, widget->pos_y);
    return ESP_OK;
}

esp_err_t widget_{{NAME}}_update_data(void)
{
    widget_t *widget = NULL;
    if (get_widget_by_type(WIDGET_TYPE_{{NAME_UPPER}}, &widget) != ESP_OK)
        return ESP_FAIL;

    return ESP_OK;
}

static void widget_{{NAME}}(lv_obj_t *screen, widget_t *widget)
{
    static {{NAME}}_t {{NAME}}_child;

    widget->lv_obj = lv_obj_create(screen);
    widget->child = &{{NAME}}_child;
}
