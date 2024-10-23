idf_component_register(
    SRCS 
    "filesystem_interface.c"
    "nvs/nvs_init.c"
    "nvs/nvs_wifi.c"

    INCLUDE_DIRS 
    "include"

    REQUIRES
    nvs_flash
)
