#ifndef {{NAME_UPPER}}_H
#define {{NAME_UPPER}}_H

#include "esp_err.h"
#include "misc/lv_types.h"

#define {{NAME_UPPER}}_FILE_PATH "{{NAME}}.json"

typedef struct {{NAME}}_s {
} {{NAME}}_t;

#ifdef __cplusplus
extern "C" {
#endif

    esp_err_t widget_{{NAME}}_draw(lv_obj_t *screen);
    esp_err_t widget_{{NAME}}_erase(void);
    esp_err_t widget_{{NAME}}_update(void);
    esp_err_t widget_{{NAME}}_update_data(void);

#ifdef __cplusplus
}
#endif

#endif
