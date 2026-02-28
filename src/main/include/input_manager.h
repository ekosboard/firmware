#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "esp_err.h"
#include "soc/gpio_num.h"
#include <stdbool.h>
#include <stdint.h>

// FIXME: utiliser config!
#define SWITCH_1_GPIO   GPIO_NUM_3
#define SWITCH_2_GPIO   GPIO_NUM_4

#define MAX_INPUT_EVENT_QUEUE 4

typedef enum {
    INPUT_SOURCE_NONE,
    INPUT_SOURCE_SWITCH_1,
    INPUT_SOURCE_SWITCH_2,
} input_source_t;

typedef enum {
    INPUT_EVENT_PRESS,
    INPUT_EVENT_RELEASE,
    INPUT_EVENT_SHORT,
    INPUT_EVENT_LONG,
    INPUT_EVENT_LONG_LONG,
} input_event_type_t;

typedef struct input_event_s {
    input_source_t      source;
    input_event_type_t  type;
    uint32_t            duration_ms;
} input_event_t;

typedef struct input_switch_ctx_s {
    input_source_t      source;
    gpio_num_t          gpio;
    input_event_type_t  event_type;
    input_event_type_t  prev_event_type;
    uint32_t            press_start_ms;
} input_switch_ctx_t;

esp_err_t init_input_manager_task(void);
void suspend_input_manager_task(void);
void resume_input_manager_task(void);

#endif
