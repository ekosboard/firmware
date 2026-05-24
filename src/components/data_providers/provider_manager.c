#include "provider_manager.h"
#include "data_provider.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "sdkconfig.h"
#include <string.h>

// ─────────────────────────────────────────────────────────────────────────────
//  Includes conditionnels des providers compilés
// ─────────────────────────────────────────────────────────────────────────────

#ifdef CONFIG_PROVIDER_BATTERY
#include "providers/battery_adc.h"
#endif

#ifdef CONFIG_PROVIDER_BME680
#include "providers/bme680.h"
#endif

static const char *TAG = "PROVIDER_MANAGER";

// ─────────────────────────────────────────────────────────────────────────────
//  Registre global des providers
// ─────────────────────────────────────────────────────────────────────────────

#define PROVIDER_REGISTRY_MAX 16

static data_provider_t *s_registry[PROVIDER_REGISTRY_MAX];
static uint8_t          s_registry_count = 0;

// ─────────────────────────────────────────────────────────────────────────────
//  Helpers internes
// ─────────────────────────────────────────────────────────────────────────────

static data_provider_t *find_provider(const char *name)
{
    for (uint8_t i = 0; i < s_registry_count; i++)
    {
        if (strcmp(s_registry[i]->name, name) == 0)
            return s_registry[i];
    }
    return NULL;
}

static bool cache_is_valid(const data_provider_t *provider)
{
    if (provider->cache_ttl_ms == 0)
        return false;

    if (provider->last_read_ms == 0)
        return false;

    uint32_t now_ms = (uint32_t)(esp_timer_get_time() / 1000);
    return (now_ms - provider->last_read_ms) < provider->cache_ttl_ms;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Initialisation
// ─────────────────────────────────────────────────────────────────────────────

void provider_manager_init(void)
{
    ESP_LOGI(TAG, "Initializing data providers...");

    // Enregistrement des providers activés par Kconfig
#ifdef CONFIG_PROVIDER_BATTERY
    provider_register(battery_adc_get_provider());
#endif

#ifdef CONFIG_PROVIDER_BME680
    provider_register(bme680_get_provider());
#endif

    // Init de chaque provider enregistré
    for (uint8_t i = 0; i < s_registry_count; i++)
    {
        data_provider_t *p = s_registry[i];

        if (p->init == NULL)
        {
            p->state = PROVIDER_STATUS_UNAVAILABLE;
            ESP_LOGW(TAG, "[%s] No init function — marked UNAVAILABLE", p->name);
            continue;
        }

        esp_err_t err = p->init();
        if (err == ESP_OK)
        {
            p->state = PROVIDER_STATUS_OK;
            ESP_LOGI(TAG, "[%s] Init OK", p->name);
        }
        else
        {
            p->state = PROVIDER_STATUS_ERROR_INIT;
            ESP_LOGE(TAG, "[%s] Init FAILED (err=0x%x) — provider will return error status", p->name, err);
        }
    }

    ESP_LOGI(TAG, "Provider manager ready (%d provider(s) registered)", s_registry_count);
}

// ─────────────────────────────────────────────────────────────────────────────
//  API publique
// ─────────────────────────────────────────────────────────────────────────────

esp_err_t provider_get(const char *name, const provider_data_t **out)
{
    if (!name || !out)
        return ESP_ERR_INVALID_ARG;

    data_provider_t *p = find_provider(name);
    if (p == NULL)
    {
        ESP_LOGW(TAG, "provider_get: unknown provider \"%s\"", name);
        return ESP_ERR_NOT_FOUND;
    }

    // Provider en erreur d'init — on retourne quand même le buffer
    // (status = ERROR_INIT) pour que le widget puisse afficher "--"
    if (p->state == PROVIDER_STATUS_ERROR_INIT ||
            p->state == PROVIDER_STATUS_UNAVAILABLE)
    {
        p->cached_data->status = p->state;
        *out = p->cached_data;
        return ESP_OK;
    }

    // Cache valide → retour immédiat
    if (cache_is_valid(p))
    {
        ESP_LOGD(TAG, "[%s] Returning cached data", p->name);
        *out = p->cached_data;
        return ESP_OK;
    }

    // Cache expiré ou TTL=0 → lecture hardware
    esp_err_t err = p->read(p->cached_data);
    if (err == ESP_OK)
    {
        p->state          = PROVIDER_STATUS_OK;
        p->last_read_ms   = (uint32_t)(esp_timer_get_time() / 1000);
        p->cached_data->status = PROVIDER_STATUS_OK;
        ESP_LOGD(TAG, "[%s] Read OK", p->name);
    }
    else
    {
        p->state               = PROVIDER_STATUS_ERROR_READ;
        p->cached_data->status = PROVIDER_STATUS_ERROR_READ;
        ESP_LOGE(TAG, "[%s] Read FAILED (err=0x%x)", p->name, err);
    }

    *out = p->cached_data;
    return ESP_OK;
}

esp_err_t provider_force_read(const char *name, const provider_data_t **out)
{
    if (!name || !out)
        return ESP_ERR_INVALID_ARG;

    data_provider_t *p = find_provider(name);
    if (p == NULL)
    {
        ESP_LOGW(TAG, "provider_force_read: unknown provider \"%s\"", name);
        return ESP_ERR_NOT_FOUND;
    }

    if (p->read == NULL || p->state == PROVIDER_STATUS_UNAVAILABLE)
    {
        p->cached_data->status = p->state;
        *out = p->cached_data;
        return ESP_FAIL;
    }

    esp_err_t err = p->read(p->cached_data);
    if (err == ESP_OK)
    {
        p->state               = PROVIDER_STATUS_OK;
        p->last_read_ms        = (uint32_t)(esp_timer_get_time() / 1000);
        p->cached_data->status = PROVIDER_STATUS_OK;
    }
    else
    {
        p->state               = PROVIDER_STATUS_ERROR_READ;
        p->cached_data->status = PROVIDER_STATUS_ERROR_READ;
        ESP_LOGE(TAG, "[%s] Force read FAILED (err=0x%x)", p->name, err);
    }

    *out = p->cached_data;
    return err;
}

esp_err_t provider_get_status(const char *name, provider_status_t *status)
{
    if (!name || !status)
        return ESP_ERR_INVALID_ARG;

    data_provider_t *p = find_provider(name);
    if (p == NULL)
        return ESP_ERR_NOT_FOUND;

    *status = p->state;
    return ESP_OK;
}

esp_err_t provider_register(data_provider_t *provider)
{
    if (provider == NULL)
        return ESP_ERR_INVALID_ARG;

    if (s_registry_count >= PROVIDER_REGISTRY_MAX)
    {
        ESP_LOGE(TAG, "Registry full — cannot register \"%s\"", provider->name);
        return ESP_ERR_NO_MEM;
    }

    s_registry[s_registry_count++] = provider;
    ESP_LOGD(TAG, "Registered provider: %s", provider->name);
    return ESP_OK;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Helpers — extraction de valeurs
// ─────────────────────────────────────────────────────────────────────────────

esp_err_t provider_data_get_float(const provider_data_t *data,
        const char *key,
        float *out)
{
    if (!data || !key || !out)
        return ESP_ERR_INVALID_ARG;

    for (uint8_t i = 0; i < data->count; i++)
    {
        if (strcmp(data->values[i].key, key) == 0)
        {
            if (data->values[i].type != PROVIDER_VAL_FLOAT)
                return ESP_ERR_INVALID_ARG;
            *out = data->values[i].val.f;
            return ESP_OK;
        }
    }
    return ESP_ERR_NOT_FOUND;
}

esp_err_t provider_data_get_int(const provider_data_t *data,
        const char *key,
        int32_t *out)
{
    if (!data || !key || !out)
        return ESP_ERR_INVALID_ARG;

    for (uint8_t i = 0; i < data->count; i++)
    {
        if (strcmp(data->values[i].key, key) == 0)
        {
            if (data->values[i].type != PROVIDER_VAL_INT)
                return ESP_ERR_INVALID_ARG;
            *out = data->values[i].val.i;
            return ESP_OK;
        }
    }
    return ESP_ERR_NOT_FOUND;
}

esp_err_t provider_data_get_string(const provider_data_t *data,
        const char *key,
        char *out,
        size_t out_len)
{
    if (!data || !key || !out || out_len == 0)
        return ESP_ERR_INVALID_ARG;

    for (uint8_t i = 0; i < data->count; i++)
    {
        if (strcmp(data->values[i].key, key) == 0)
        {
            if (data->values[i].type != PROVIDER_VAL_STRING)
                return ESP_ERR_INVALID_ARG;
            strncpy(out, data->values[i].val.s, out_len - 1);
            out[out_len - 1] = '\0';
            return ESP_OK;
        }
    }
    return ESP_ERR_NOT_FOUND;
}
