file(GLOB PROVIDER_SOURCES "providers/*.c")

idf_component_register(
    SRCS
    "provider_manager.c"
    ${PROVIDER_SOURCES}

    INCLUDE_DIRS
    "include"
    "providers"

    REQUIRES
    esp_adc
    esp_timer
)
