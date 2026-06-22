#include "HTTPS_request.h"
#include "esp_crt_bundle.h"
#include "esp_log.h"
#include <string.h>
#include <stdlib.h>

static const char *TAG = "HTTPS_request_raw";

/**
 * @brief Generic HTTPS request: custom method, headers, and body.
 *        Response read dynamically (malloc/realloc), handles both the
 *        chunked case (no Content-Length) and the known Content-Length case.
 *
 * @param url           Full URL (https://...)
 * @param method        HTTP method (GET, POST, PROPFIND, REPORT, ...)
 * @param headers       Array of custom headers (can be NULL)
 * @param header_count  Number of headers in the array
 * @param body          Request body (can be NULL if none)
 * @param body_len      Body size (0 if body is NULL)
 * @param out_buf       Dynamically allocated output buffer (to be free()'d by the caller)
 * @param out_status    HTTP status code of the response (can be NULL)
 * @param out_len       Size of the response read (can be NULL)
 */
esp_err_t https_request_raw(const char *url,
        esp_http_client_method_t method,
        const http_header_t *headers,
        size_t header_count,
        const char *body,
        size_t body_len,
        char **out_buf,
        int *out_status,
        int *out_len)
{
    if (!url || !out_buf)
        return ESP_ERR_INVALID_ARG;

    *out_buf = NULL;
    if (out_status)
        *out_status = -1;
    if (out_len)
        *out_len = 0;

    esp_http_client_config_t config = {
        .url = url,
        .crt_bundle_attach = esp_crt_bundle_attach,
        .timeout_ms = 10000,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    if (!client)
    {
        ESP_LOGE(TAG, "Failed to init http client");
        return ESP_FAIL;
    }

    esp_err_t ret = ESP_OK;

    esp_http_client_set_method(client, method);

    // Headers custom (Authorization, Content-Type, etc.)
    for (size_t i = 0; i < header_count; i++)
    {
        if (headers[i].key && headers[i].value)
        {
            esp_http_client_set_header(client, headers[i].key, headers[i].value);
        }
    }

    ret = esp_http_client_open(client, body ? body_len : 0);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(ret));
        goto cleanup;
    }

    if (body && body_len > 0)
    {
        int written = esp_http_client_write(client, body, body_len);
        if (written < 0)
        {
            ESP_LOGE(TAG, "Failed to write request body");
            ret = ESP_FAIL;
            goto cleanup;
        }
    }

    if (esp_http_client_fetch_headers(client) < 0)
    {
        ESP_LOGE(TAG, "HTTP client fetch headers failed");
        ret = ESP_FAIL;
        goto cleanup;
    }

    {
        int content_length = esp_http_client_get_content_length(client);
        int total_read = 0;

        if (content_length > 0)
        {
            *out_buf = malloc(content_length + 1);
            if (!*out_buf)
            {
                ESP_LOGE(TAG, "malloc failed for content_length=%d", content_length);
                ret = ESP_ERR_NO_MEM;
                goto cleanup;
            }

            int read_len = esp_http_client_read_response(client, *out_buf, content_length);
            if (read_len < 0)
            {
                ESP_LOGE(TAG, "Failed to read response");
                ret = ESP_FAIL;
                goto cleanup;
            }

            (*out_buf)[read_len] = '\0';
            total_read = read_len;
        }
        else
        {
            // Cas chunked (typiquement notre réponse CalDAV iCloud)
            const int chunk_size = 1024;
            char tmp[chunk_size];

            while (1)
            {
                int read_len = esp_http_client_read(client, tmp, chunk_size);
                if (read_len < 0)
                {
                    ESP_LOGE(TAG, "Read error");
                    ret = ESP_FAIL;
                    goto cleanup;
                }
                if (read_len == 0)
                {
                    break;
                }

                char *new_buf = realloc(*out_buf, total_read + read_len + 1);
                if (!new_buf)
                {
                    ESP_LOGE(TAG, "realloc failed at %d bytes", total_read + read_len);
                    free(*out_buf);
                    *out_buf = NULL;
                    ret = ESP_ERR_NO_MEM;
                    goto cleanup;
                }
                *out_buf = new_buf;

                memcpy(*out_buf + total_read, tmp, read_len);
                total_read += read_len;
                (*out_buf)[total_read] = '\0';
            }
        }

        if (out_status)
            *out_status = esp_http_client_get_status_code(client);
        if (out_len)
            *out_len = total_read;
    }

cleanup:
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
    return ret;
}
