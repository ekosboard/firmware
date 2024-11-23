idf_component_register(
    SRCS 
    "filesystem_interface.c"
    "fat/fat_init.c"
    "fat/fat_json_utils.c"
    "nvs/nvs_init.c"
    "nvs/nvs_wifi.c"
    "nvs/nvs_setup_state.c"

    INCLUDE_DIRS 
    "include"

    REQUIRES
    nvs_flash
    fatfs
    vfs
    json
)
