idf_component_register(
    SRCS 
    "screen_schedule.c"
    "screen_scheduler_task.c"
    "./wake_coordinator.c"

    INCLUDE_DIRS
    "include"

    REQUIRES
    UI
    filesystem_interface
    screen_manager
)
