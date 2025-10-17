idf_component_register(
    SRCS 
    "main.c"
    "widget_manager_task.c"
    "screen_manager_task.c"
    "power_manager_task.c"
    "update_manager_task.c"
    "setup/setup_persistent_state.c"
    "setup/setup_ui_tasks.c"
    "setup/state_manager.c"
    "setup/setup_timeout.c"
    "state_handler/state_init_handler.c"
    "state_handler/state_config_handler.c"
    "state_handler/state_idle_handler.c"

    INCLUDE_DIRS 
    "include"

    REQUIRES
    filesystem_interface
    wifi
    HTTP_server
    HTTPS_request
    EPD
    UI
)

#littlefs_create_partition_image(littlefs ../littlefs FLASH_IN_PROJECT)
#idf.py littlefs-flash
littlefs_create_partition_image(littlefs ../littlefs)
