#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "esp_err.h"
#include "filesystem_interface.h"
#include "esp_log.h"

#include "wifi.h"
#include "HTTP_server.h"
#include "UI.h"
#include "EPD.h"
#include "filesystem_interface.h"

// Bit masks for screen actions
#define SCREEN_ID_MASK          0x000000FF
#define SCREEN_ACTION_MASK      0x0000FF00

// Action value
#define SCREEN_ACTION_NONE                   0x00
#define SCREEN_ACTION_CLEAR                  0x01
#define SCREEN_ACTION_CLEAR_DRIVER           0x02
#define SCREEN_ACTION_DRAW                   0x04
#define SCREEN_ACTION_SWITCH                 0x08

// Composite actions
#define SCREEN_ACTION_CLEAR_ONLY             (SCREEN_ACTION_CLEAR)
#define SCREEN_ACTION_CLEAR_WITH_DRIVER      (SCREEN_ACTION_CLEAR | SCREEN_ACTION_CLEAR_DRIVER)
#define SCREEN_ACTION_DRAW_ONLY              (SCREEN_ACTION_DRAW)
#define SCREEN_ACTION_DRAW_WITH_DRIVER       (SCREEN_ACTION_DRAW | SCREEN_ACTION_CLEAR_DRIVER)
#define SCREEN_ACTION_SWITCH_ONLY            (SCREEN_ACTION_SWITCH)
#define SCREEN_ACTION_SWITCH_AND_CLEAR       (SCREEN_ACTION_SWITCH | SCREEN_ACTION_CLEAR)

// Bit mask for power manager notif
#define WIFI_REQUIRED    (1U << 31)  // Bit 31 à 1 pour activer le WiFi
#define TIMER_MASK       (~WIFI_REQUIRED)  // Masque pour isoler la valeur du timer

#define DEFAULT_TIMEOUT_MS (10 * 60 * 1000) // 10 min par défaut

typedef enum {
    SETUP_UI_TASK = 0,
    SETUP_TIMEOUT_TASK,
    POWER_MANAGER_TASK,
    UPDATE_MANAGER_TASK,
    SETUP_TASK_COUNT // Nombre total de tâches
} setup_task_index_t;

void        app_start(void *pvParameters);
esp_err_t   setup_persistent_state(void);
void        setup_ui_tasks(void *pvParameters);
void        setup_network(void *pvParameters);
void        setup_timeout_task(void *pvParameter);

void        widget_manager_task(void *pvParameters);
void        screen_manager_task(void *pvParameters);
void        notify_screen_manager(uint8_t action, uint8_t screen_id);

void        power_manager_task(void *pvParameters);
void        update_manager_task(void *pvParameters);

#endif
