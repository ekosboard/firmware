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
#include "HTTPS_request.h"
#include "UI.h"
#include "EPD.h"
#include "filesystem_interface.h"

// Bit mask for power manager notif
#define TIMER_MASK       (~WIFI_REQUIRED)  // Masque pour isoler la valeur du timer

// Default timeout value for setup_timeout_task
#define DEFAULT_TIMEOUT_MS (60 * 60 * 1000) // 60 min par défaut

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
void        notify_screen_manager(uint8_t action, uint8_t screen_id);

void        power_manager_task(void *pvParameters);
void        update_manager_task(void *pvParameters);

#endif
