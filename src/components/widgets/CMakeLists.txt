set(GEN_SCRIPT   ${CMAKE_CURRENT_LIST_DIR}/scripts/gen_widgets.py)
set(GEN_HEADER   ${CMAKE_CURRENT_LIST_DIR}/include/widget_autogen.h)
set(GEN_SOURCE   ${CMAKE_CURRENT_LIST_DIR}/widget_autogen.c)
set(KCONFIG_FILE ${CMAKE_CURRENT_LIST_DIR}/Kconfig.projbuild)
set(SDKCONFIG    ${CMAKE_CURRENT_LIST_DIR}/../../sdkconfig)

# ── Phase CONFIGURE : génère Kconfig.projbuild depuis les .c détectés
execute_process(
    COMMAND python3 ${GEN_SCRIPT} --kconfig-only
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    RESULT_VARIABLE GEN_KCONFIG_RESULT
    ERROR_VARIABLE  GEN_KCONFIG_ERROR
)
if(NOT GEN_KCONFIG_RESULT EQUAL 0)
    message(FATAL_ERROR "gen_widgets.py --kconfig-only failed:\n${GEN_KCONFIG_ERROR}")
endif()

# ── Lecture de sdkconfig pour filtrer les sources widget
file(GLOB ALL_WIDGET_SOURCES "${CMAKE_CURRENT_LIST_DIR}/widget/*.c")
file(GLOB WIDGET_HEADERS     "${CMAKE_CURRENT_LIST_DIR}/include/widget/*.h")

set(WIDGET_SOURCES "")

if(EXISTS ${SDKCONFIG})
    file(STRINGS ${SDKCONFIG} SDKCONFIG_LINES)
    foreach(SRC ${ALL_WIDGET_SOURCES})
        get_filename_component(WIDGET_NAME ${SRC} NAME_WE)   # ex: stock_chart
        string(TOUPPER ${WIDGET_NAME} WIDGET_NAME_UPPER)     # ex: STOCK_CHART
        set(CONFIG_KEY "CONFIG_WIDGET_${WIDGET_NAME_UPPER}=y")
        if(${CONFIG_KEY} IN_LIST SDKCONFIG_LINES)
            list(APPEND WIDGET_SOURCES ${SRC})
        endif()
    endforeach()
else()
    # sdkconfig absent (premier configure après fullclean) :
    # on inclut tout, le premier build après menuconfig corrigera
    message(WARNING "sdkconfig not found — including all widget sources as fallback")
    set(WIDGET_SOURCES ${ALL_WIDGET_SOURCES})
endif()

message(STATUS "EKOS widgets enabled: ${WIDGET_SOURCES}")

idf_component_register(
    SRCS
    ${WIDGET_SOURCES}
    "widget_autogen.c"
    "widget_schedule.c"
    "widget_utils/widget_json.c"
    "widget_utils/widget_list.c"
    "widget_utils/widget_list_json.c"
    "widget_utils/widget_template_loader.c"
    "widget_utils/widget_config_list.c"
    "widget_utils/widget_template_interval.c"

    INCLUDE_DIRS
    "include"

    REQUIRES
    UI
    lvgl
    filesystem_interface
    json
    screen_manager
    data_providers
    caldav
)

add_custom_command(
    OUTPUT  ${GEN_SOURCE} ${GEN_HEADER}
    COMMAND python3 ${GEN_SCRIPT} --codegen-only
    DEPENDS ${ALL_WIDGET_SOURCES} ${WIDGET_HEADERS} ${GEN_SCRIPT}
    ${CMAKE_CURRENT_LIST_DIR}/../../littlefs/template
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    COMMENT "Generating widget_autogen.h/.c"
)

add_custom_target(gen-widgets ALL DEPENDS ${GEN_SOURCE} ${GEN_HEADER})
add_dependencies(${COMPONENT_LIB} gen-widgets)
