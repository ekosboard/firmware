set(PROVIDER_SOURCES "provider_manager.c")

if(CONFIG_PROVIDER_BATTERY)
    list(APPEND PROVIDER_SOURCES "providers/battery_adc.c")
endif()

if(CONFIG_PROVIDER_BME280)
    list(APPEND PROVIDER_SOURCES "providers/bme280/bme280.c")
    list(APPEND PROVIDER_SOURCES "providers/bme280/bme280_provider.c")
endif()

if(CONFIG_PROVIDER_BME680)
    list(APPEND PROVIDER_SOURCES "providers/bme680/bme68x.c")
    list(APPEND PROVIDER_SOURCES "providers/bme680/bme680_provider.c")
endif()


set(PROVIDER_INCLUDE_DIRS "include" "include/providers")

if(CONFIG_PROVIDER_BME280)
    list(APPEND PROVIDER_INCLUDE_DIRS "include/providers/bme280")
endif()

if(CONFIG_PROVIDER_BME680)
    list(APPEND PROVIDER_INCLUDE_DIRS "include/providers/bme680")
endif()

idf_component_register(
    SRCS
    ${PROVIDER_SOURCES}

    INCLUDE_DIRS
    ${PROVIDER_INCLUDE_DIRS}

    REQUIRES
    esp_adc
    esp_timer
    i2c_manager
)
