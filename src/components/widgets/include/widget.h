#ifndef WIDGET_H
#define WIDGET_H

#include <stdbool.h>
#include <stdint.h>
#include "cJSON.h"
#include "esp_err.h"
#include "lvgl.h"
#include "misc/lv_color.h"
#include "misc/lv_types.h"
#include "sdkconfig.h"
#include "widget_autogen.h"
#include "widget_config_list.h"
#include "widget_template_interval.h"

#define WIFI_REQUIRED    (1U << 31)  // Bit 31 à 1 pour activer le WiFi

typedef enum { 
    WIDGET_ACTION_DRAW,
    WIDGET_ACTION_ERASE,
    WIDGET_ACTION_UPDATE,
} widget_action_t;

typedef struct widget_s {
    widget_type_t   type;
    lv_obj_t        *lv_obj;
    void            *child;
    uint16_t        pos_x;
    uint16_t        pos_y;
    uint16_t        height;
    uint16_t        width;
    uint32_t        flag;
    esp_err_t       (*draw_function)(lv_obj_t *screen);
    esp_err_t       (*erase_function)(void);
    esp_err_t       (*update_function)(void);
    esp_err_t       (*update_data_function)(void);
    uint32_t        update_data_interval_ms;
    uint32_t        update_data_timestamp;
    widget_config_t *config;
} widget_t;

typedef struct widget_update_s {
    widget_type_t   type;
    widget_action_t action;
    uint16_t        pos_x;
    uint16_t        pos_y;
    uint16_t        width;
    uint16_t        height;
    uint32_t        flag;
    uint32_t        update_data_interval_ms;
    widget_config_t *config;
} widget_update_t;

typedef struct widget_node_s {
    widget_t                *widget;
    struct widget_node_s    *prev;
    struct widget_node_s    *next;
} widget_node_t;

typedef struct widget_container_s {
    widget_node_t       *widget;
} widget_container_t;


extern widget_t widget_info_list[WIDGET_COUNT];
extern uint8_t size_widget_info_list;

#ifdef __cplusplus
extern "C" {
#endif

    ////////////////////////////////////////////////////////////////////////////////
    //  WIDGET MAIN
    ////////////////////////////////////////////////////////////////////////////////
    void                init_widget_list(void);
    const widget_t      *get_widget_list(uint8_t *size);
    esp_err_t           get_widget_by_id(const char *id, const widget_t **widget_info);
    esp_err_t           get_widget_by_type(const widget_type_t type, widget_t **widget_info);
    const char          *get_widget_type_to_string(widget_type_t type);
    esp_err_t           update_widget_info(const widget_update_t *update);
    widget_node_t       *create_widget_display_list_node(widget_node_t *head, widget_t *widget);

    bool                check_widget_type_by_id(const char *id, widget_type_t type);
    bool                check_widget_exists_in_display_list(widget_type_t type);

    /**
     * @brief Initializes a widget instance from its template.
     *
     * Loads the specified widget template from LittleFS and ensures
     * a corresponding instance file exists. If not, it creates one
     * from the template. The widget structure is then populated with
     * the instance data.
     *
     * @param[in,out] widget Pointer to the widget to initialize.
     * @param[in] json_path  Template filename or relative path.
     *
     * @return
     * - ESP_OK on success
     * - ESP_FAIL on read, validation, or creation error
     */
    esp_err_t           init_widget_from_template(widget_t *widget, const char *template_path);

    ////////////////////////////////////////////////////////////////////////////////
    //  WIDGET UTILS
    ////////////////////////////////////////////////////////////////////////////////
    void                init_widget_display_list_from_file(widget_node_t **head, const char *json_path);
    void                update_widget_json_from_struct(widget_t *widget);
    esp_err_t           update_widget_display_list_json(widget_node_t *head, uint8_t screen_id);
    void                update_widget_struct_from_template(widget_t *widget, cJSON *widget_json);


#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif
