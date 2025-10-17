#include "HTTPS_request.h"
#include "esp_crt_bundle.h"
#include "esp_err.h"
#include "esp_http_client.h"
#include "esp_log.h"

static const char *TAG = "HTTPS_request";

esp_err_t https_get_dyn(const char *url, char **out_buf, int *out_status, int *out_len)
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

    esp_http_client_set_method(client, HTTP_METHOD_GET);

    esp_err_t ret = esp_http_client_open(client, 0);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(ret));
        goto cleanup;
    }

    if (esp_http_client_fetch_headers(client) < 0)
    {
        ESP_LOGE(TAG, "HTTP client fetch headers failed");
        ret = ESP_FAIL;
        goto cleanup;
    }

    int content_length = esp_http_client_get_content_length(client);
    int total_read = 0;

    if (content_length > 0)
    {
        // Content-Length connu
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
        //  cas chunked ou sans content-length : realloc par blocs
        const int chunk_size = 1024;
        char tmp[chunk_size];

        while (42)
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
                break; // fin
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

    ret = ESP_OK;

cleanup:
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
    return ret;
}


esp_err_t https_get(const char *url, char *out_buf, size_t max_len, int *out_status, int *out_len)
{
    if (!url || !out_buf || max_len == 0)
        return ESP_ERR_INVALID_ARG;

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

    esp_http_client_set_method(client, HTTP_METHOD_GET);

    esp_err_t ret = esp_http_client_open(client, 0);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(ret));
    }
    else
    {
        if (esp_http_client_fetch_headers(client) < 0)
        {
            ESP_LOGE(TAG, "HTTP client fetch headers failed");
            ret = ESP_FAIL;
        }
        else
        {
            int read_len = esp_http_client_read_response(client, out_buf, max_len - 1);
            if (read_len < 0)
            {
                ESP_LOGE(TAG, "Failed to read response");
                ret = ESP_FAIL;
            }
            else
            {
                out_buf[read_len < max_len ? read_len : max_len - 1] = '\0';
                if (out_status)
                    *out_status = esp_http_client_get_status_code(client);

                if (out_len)
                    *out_len = read_len;
            }
        }
    }

    esp_http_client_close(client);
    esp_http_client_cleanup(client);
    return ret;
}


esp_err_t https_post(const char *url, const char *post_data, size_t post_len, char *out_buf, size_t max_len, int *out_status, int *out_len)
{
    if (!url || !post_data || !out_buf || max_len == 0)
    {
        return ESP_ERR_INVALID_ARG;
    }

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

    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_header(client, "Content-Type", "application/json");

    esp_err_t ret = esp_http_client_open(client, post_len);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(ret));
    }
    else
    {
        // Écrire le body
        int written = esp_http_client_write(client, post_data, post_len);
        if (written < 0)
        {
            ESP_LOGE(TAG, "Failed to write POST data");
            ret = ESP_FAIL;
        }
        else
        {
            // Lire la réponse
            if (esp_http_client_fetch_headers(client) < 0)
            {
                ESP_LOGE(TAG, "HTTP client fetch headers failed");
                ret = ESP_FAIL;
            }
            else
            {
                int read_len = esp_http_client_read_response(client, out_buf, max_len - 1);
                if (read_len < 0)
                {
                    ESP_LOGE(TAG, "Failed to read response");
                    ret = ESP_FAIL;
                }
                else
                {
                    out_buf[read_len < max_len ? read_len : max_len - 1] = '\0';
                    if (out_status)
                        *out_status = esp_http_client_get_status_code(client);

                    if (out_len)
                        *out_len = read_len;
                }
            }
        }
    }

    esp_http_client_close(client);
    esp_http_client_cleanup(client);
    return ret;
}

