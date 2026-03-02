#ifndef HTTPS_REQUEST_H
#define HTTPS_REQUEST_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

    /* Performs an HTTPS GET request and retrieves the full response into a dynamically allocated buffer. */
    /* The caller is responsible for freeing the allocated buffer with free(). */
    /* @Parameters: */
    /*     - url: Target URL to send the GET request to. */
    /*     - out_buf: Pointer to a char* that will receive the allocated buffer containing the response body. */
    /*                Must not be NULL. On success, *out_buf will point to a null-terminated string. */
    /*     - out_status: Pointer to an integer where the HTTP status code will be written (can be NULL). */
    /*     - out_len: Pointer to an integer where the number of bytes read will be written (can be NULL). */
    /* @Return: */
    /*     - ESP_OK if the request was successful and the response was read. */
    /*     - ESP_FAIL if the client could not be initialized, request failed, or response could not be read. */
    /*     - ESP_ERR_INVALID_ARG if invalid arguments are provided. */
    /*     - ESP_ERR_NO_MEM if memory allocation fails. */
    esp_err_t https_get_dyn(const char *url, char **out_buf, int *out_status, int *out_len);

    /* Performs an HTTPS GET request and retrieves the response. */
    /* @Parameters: */
    /*     - url: Target URL to send the GET request to. */
    /*     - out_buf: Pointer to a buffer where the response body will be stored. */
    /*     - max_len: Maximum size of the response buffer (including null terminator). */
    /*     - out_status: Pointer to an integer where the HTTP status code will be written (can be NULL). */
    /*     - out_len: Pointer to an integer where the number of bytes read will be written (can be NULL). */
    /* @Return: */
    /*     - ESP_OK if the request was successful and the response was read. */
    /*     - ESP_FAIL if the client could not be initialized, request failed, or response could not be read. */
    /*     - ESP_ERR_INVALID_ARG if invalid arguments are provided. */
    esp_err_t https_get(const char *url, char *out_buf, size_t max_len, int *out_status, int *out_len);

    /* Performs an HTTPS POST request with a JSON payload and retrieves the response. */
    /* @Parameters: */
    /*     - url: Target URL to send the POST request to. */
    /*     - post_data: Pointer to the POST data (payload) to be sent in the request body. */
    /*     - post_len: Length of the POST data in bytes. */
    /*     - out_buf: Pointer to a buffer where the response body will be stored. */
    /*     - max_len: Maximum size of the response buffer (including null terminator). */
    /*     - out_status: Pointer to an integer where the HTTP status code will be written (can be NULL). */
    /*     - out_len: Pointer to an integer where the number of bytes read will be written (can be NULL). */
    /* @Return: */
    /*     - ESP_OK if the request was successful and the response was read. */
    /*     - ESP_FAIL if the client could not be initialized, request failed, or response could not be read. */
    /*     - ESP_ERR_INVALID_ARG if invalid arguments are provided. */
    esp_err_t https_post(const char *url, const char *post_data, size_t post_len, char *out_buf, size_t max_len, int *out_status, int *out_len);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
