#ifndef FOOBAR_H
#define FOOBAR_H

#include "esp_err.h"
#include "misc/lv_types.h"

#define FOOBAR_FILE_PATH "foobar.json"

typedef struct foobar_s {
    lv_obj_t    *container_content;

    lv_obj_t    *button;
    lv_obj_t    *button_label;
} foobar_t;

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t   widget_foobar_draw(lv_obj_t *screen);
    esp_err_t   widget_foobar_erase(void);
    esp_err_t   widget_foobar_update(void);
    esp_err_t   widget_foobar_update_data(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
