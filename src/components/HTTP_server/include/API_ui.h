#ifndef API_UI_H
#define API_UI_H

#include "HTTP_server.h"


#ifdef __cplusplus
extern "C" {
#endif

    ////////////////////////////////////////////////////////////////////////////////
    //  WIDGETS
    ////////////////////////////////////////////////////////////////////////////////
    extern const    httpd_uri_t widgets_uri;
    void            register_widgets(httpd_handle_t server);
    void            unregister_widgets(httpd_handle_t server);
    esp_err_t       widgets_put_handler(httpd_req_t *req);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
