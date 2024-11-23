#include "HTTP_server.h"

/* Read the content of an HTTP request dynamically. */
/* @param req Pointer to the HTTP request. */
/* @Parameters: */
/*     - content Pointer to a char* to store the dynamically allocated content. */
/* @Return: */
/*     - ESP_OK: Successfully read the content. */
/*     - ESP_FAIL: Failed to read the content or allocate memory. */
esp_err_t read_http_request_content(httpd_req_t *req, char **content)
{
    if (!req || !content) 
        return ESP_FAIL;

    *content = calloc(req->content_len + 1, sizeof(char));
    if (!*content)
    {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Memory allocation failed");
        return ESP_FAIL;
    }

    char buf[BUF_SIZE];
    int received = 0, ret;
    while (received < req->content_len)
    {
        ret = httpd_req_recv(req, buf, MIN(req->content_len - received, sizeof(buf)));
        if (ret <= 0)
        {
            if (ret == HTTPD_SOCK_ERR_TIMEOUT)
                continue;

            free(*content);
            *content = NULL;
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, esp_err_to_name(ret));
            return ESP_FAIL;
        }

        memcpy(*content + received, buf, ret);
        received += ret;
    }

    return ESP_OK;
}
