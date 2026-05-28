#ifndef API_UI_H
#define API_UI_H

#include "HTTP_server.h"


#ifdef __cplusplus
extern "C" {
#endif

    ////////////////////////////////////////////////////////////////////////////////
    //  SCREENS
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    //
    //  /api/ui/screen*
    //
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t screens_dispatcher;
    void            register_screens_dispatcher_uri(httpd_handle_t server);
    void            unregister_screens_dispatcher_uri(httpd_handle_t server);
    esp_err_t       screens_dispatcher_handler(httpd_req_t *req);

    esp_err_t       get_screens_handler(httpd_req_t *req);
    esp_err_t       get_active_screen_handler(httpd_req_t *req);
    esp_err_t       get_screens_layout_handler(httpd_req_t *req);
    esp_err_t       post_active_screen_handler(httpd_req_t *req);
    esp_err_t       post_refresh_screen_handler(httpd_req_t *req);


    ////////////////////////////////////////////////////////////////////////////////
    //  WIDGETS
    //  /api/ui/widgets
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t widgets_uri;
    void            register_widgets(httpd_handle_t server);
    void            unregister_widgets(httpd_handle_t server);
    esp_err_t       widgets_put_handler(httpd_req_t *req);

    ////////////////////////////////////////////////////////////////////////////////
    //
    //  /api/ui/widgets/*
    //
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t widgets_dispatcher;
    void            register_widgets_dispatcher_uri(httpd_handle_t server);
    void            unregister_widgets_dispatcher_uri(httpd_handle_t server);
    esp_err_t       widgets_dispatcher_handler(httpd_req_t *req);

    ////////////////////////////////////////////////////////////////////////////////
    //
    //  /api/ui/widgets/available
    //
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t available_widgets;
    void            register_available_widgets_uri(httpd_handle_t server);
    void            unregister_available_widgets_uri(httpd_handle_t server);
    esp_err_t       get_available_widgets_handler(httpd_req_t *req);

    ////////////////////////////////////////////////////////////////////////////////
    //
    //  /api/ui/widgets/layout
    //
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t widgets_layout;
    void            register_widgets_layout_uri(httpd_handle_t server);
    void            unregister_widgets_layout_uri(httpd_handle_t server);
    esp_err_t       get_widgets_layout_handler(httpd_req_t *req);

    ////////////////////////////////////////////////////////////////////////////////
    //
    //  /api/ui/widgets/{name}
    //
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t widget_template;
    void            register_widget_template_uri(httpd_handle_t server);
    void            unregister_widget_template_uri(httpd_handle_t server);
    esp_err_t       get_widget_template_handler(httpd_req_t *req);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
