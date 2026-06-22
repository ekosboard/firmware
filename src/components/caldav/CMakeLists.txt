idf_component_register(
    SRCS
    "caldav_xml.c"
    "caldav_ical.c"

    INCLUDE_DIRS
    "include"

    REQUIRES
    expat
    HTTPS_request
)
