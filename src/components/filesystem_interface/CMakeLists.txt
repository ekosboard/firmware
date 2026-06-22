idf_component_register(
    SRCS 
    "filesystem_interface.c"
    "fs_json_utils.c"
    "fat/fat_init.c"
    "nvs/nvs_init.c"
    "nvs/nvs_wifi.c"
    "nvs/nvs_setup_state.c"
    "nvs/nvs_device_info.c"
    "lfs/lfs_init.c"
    "lfs/lfs_utils.c"

    INCLUDE_DIRS 
    "include"

    REQUIRES
    nvs_flash
    fatfs
    vfs
    littlefs
    cjson
)
