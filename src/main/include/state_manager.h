#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "esp_event.h"
#include "esp_event_base.h"
#include "freertos/idf_additions.h"

extern esp_event_loop_handle_t state_manager_loop;

ESP_EVENT_DECLARE_BASE(INIT_EVENT);
ESP_EVENT_DECLARE_BASE(CONFIG_EVENT);
ESP_EVENT_DECLARE_BASE(IDLE_EVENT);

typedef enum {
    INIT_BEGIN,       // Démarrer l'init
    INIT_CLEAR,       // Réinitialiser / forcer l'init

    INIT_SETUP_HW,    // Initialiser le hardware
    INIT_SETUP_UI,    // Initialiser l'interface utilisateur
    INIT_SETUP_NET,   // Initialiser le réseau

    INIT_WIFI_CHECK,  // Verifier si le wifi doit etre lancer
    INIT_END          // Fin de l'init, passage à CONFIG
} init_state_event_t;

typedef enum {
    CONFIG_BEGIN,     // Entrée en mode config
    CONFIG_BEGIN_ISR, // Entrée en mode config depuis un ISR
    CONFIG_SAVE,      // Sauvegarde de la config
    CONFIG_APPLY,     // Appliquer la config
    CONFIG_EXIT       // Quitter CONFIG vers IDLE
} config_state_event_t;

typedef enum {
    IDLE_ENTER,       // Passer en IDLE
    IDLE_WAKEUP,
    IDLE_WIFI_START,
    IDLE_WIFI_STOP,
    IDLE_EXIT,        // Sortir de l'IDLE
} idle_state_event_t;

void state_manager_init(TaskHandle_t *setup_task_handle);

void state_init_handler(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data);
void state_config_handler(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data);
void state_idle_handler(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data);

#endif
