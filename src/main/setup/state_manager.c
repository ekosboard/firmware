#include "state_manager.h"


esp_event_loop_handle_t state_manager_loop;

ESP_EVENT_DEFINE_BASE(INIT_EVENT);
ESP_EVENT_DEFINE_BASE(CONFIG_EVENT);
ESP_EVENT_DEFINE_BASE(IDLE_EVENT);

void state_manager_init(TaskHandle_t *setup_task_handle)
{
    esp_event_loop_args_t state_manager_args = {
        .queue_size = 4,
        .task_name = "state_manager_loop",
        .task_priority = 10,
        .task_stack_size = 4096,
        .task_core_id = 0
    };

    esp_event_loop_create(&state_manager_args, &state_manager_loop);

    esp_event_handler_register_with(state_manager_loop, INIT_EVENT, ESP_EVENT_ANY_ID, state_init_handler, setup_task_handle);
    esp_event_handler_register_with(state_manager_loop, CONFIG_EVENT, ESP_EVENT_ANY_ID, state_config_handler, setup_task_handle);
    esp_event_handler_register_with(state_manager_loop, IDLE_EVENT, ESP_EVENT_ANY_ID, state_idle_handler, NULL);
}
