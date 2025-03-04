idf_component_register(
    SRCS 
    "main.c"
    "widget_manager_task.c"
    "screen_manager_task.c"
    "setup/setup_hardware.c"
    "setup/setup_network.c"
    "setup/setup_ui.c"

    INCLUDE_DIRS 
    "include"

    REQUIRES
    filesystem_interface
    wifi
    HTTP_server
    EPD
    UI
)

littlefs_create_partition_image(widget_fs ../widget_template FLASH_IN_PROJECT)
