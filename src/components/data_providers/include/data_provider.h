#ifndef DATA_PROVIDER_H
#define DATA_PROVIDER_H

#include "esp_err.h"
#include <stdint.h>
#include <stdbool.h>


#define PROVIDER_MAX_VALUES     8    // Nombre max de valeurs par provider
#define PROVIDER_MAX_STR_LEN    32   // Longueur max d'une valeur string
#define PROVIDER_NAME_MAX_LEN   32   // Longueur max du nom d'un provider

#ifdef __cplusplus
extern "C" {
#endif

    // ─────────────────────────────────────────────────────────────────────────────
    //  Types de valeurs
    // ─────────────────────────────────────────────────────────────────────────────

    typedef enum {
        PROVIDER_VAL_FLOAT,
        PROVIDER_VAL_INT,
        PROVIDER_VAL_STRING,
    } provider_val_type_t;

    // ─────────────────────────────────────────────────────────────────────────────
    //  Statuts d'un provider
    // ─────────────────────────────────────────────────────────────────────────────

    typedef enum {
        PROVIDER_STATUS_OK,
        PROVIDER_STATUS_ERROR_INIT,      // init() a échoué
        PROVIDER_STATUS_ERROR_READ,      // read() a échoué
        PROVIDER_STATUS_UNAVAILABLE,     // Désactivé par Kconfig ou non branché
        PROVIDER_STATUS_STALE,           // Données en cache, lecture hw non disponible
    } provider_status_t;

    // ─────────────────────────────────────────────────────────────────────────────
    //  Une valeur nommée (stockée dans un buffer statique)
    // ─────────────────────────────────────────────────────────────────────────────

    typedef struct {
        char                key[PROVIDER_NAME_MAX_LEN];
        provider_val_type_t type;
        union {
            float   f;
            int32_t i;
            char    s[PROVIDER_MAX_STR_LEN];
        } val;
    } provider_value_t;

    // ─────────────────────────────────────────────────────────────────────────────
    //  Résultat d'un read — ce que consomme le widget
    //  Alloué statiquement par chaque provider (EXT_RAM_BSS_ATTR)
    // ─────────────────────────────────────────────────────────────────────────────

    typedef struct {
        provider_status_t  status;
        provider_value_t   values[PROVIDER_MAX_VALUES];
        uint8_t            count;       // Nombre de valeurs valides dans le tableau
    } provider_data_t;

    // ─────────────────────────────────────────────────────────────────────────────
    //  Struct qu'implémente chaque provider
    // ─────────────────────────────────────────────────────────────────────────────

    typedef struct {
        const char       *name;              // Identifiant unique, ex: "battery", "bme680"
        provider_status_t state;             // Mis à jour par le manager après init/read
        uint32_t          cache_ttl_ms;      // TTL du cache (0 = toujours lire le hw)
        uint32_t          last_read_ms;      // Timestamp du dernier read réussi
        provider_data_t  *cached_data;       // Pointeur vers le buffer statique du provider

        /**
         * @brief Initialise le hardware ou la ressource associée au provider.
         * @return ESP_OK si succès, ESP_FAIL sinon (non bloquant pour le boot).
         */
        esp_err_t (*init)(void);

        /**
         * @brief Lit les données et remplit le buffer statique du provider.
         * @param[out] out Pointeur vers le provider_data_t statique du provider.
         * @return ESP_OK si lecture réussie.
         */
        esp_err_t (*read)(provider_data_t *out);

        /**
         * @brief Callback push optionnel — NULL pour le MVP.
         * Réservé pour les providers événementiels futurs (ex: capteur avec IRQ).
         */
        void (*on_data)(provider_data_t *data);
    } data_provider_t;

    // ─────────────────────────────────────────────────────────────────────────────
    //  Helpers — extraction de valeurs depuis un provider_data_t
    // ─────────────────────────────────────────────────────────────────────────────

    /**
     * @brief Extraire une valeur float depuis un provider_data_t par clé.
     *
     * @param[in]  data  Résultat retourné par provider_get().
     * @param[in]  key   Clé à chercher (ex: "battery_pct", "temperature").
     * @param[out] out   Valeur float si trouvée.
     *
     * @return ESP_OK si trouvé et bon type, ESP_ERR_NOT_FOUND sinon.
     */
    esp_err_t provider_data_get_float(const provider_data_t *data,
            const char *key,
            float *out);

    /**
     * @brief Extraire une valeur int32 depuis un provider_data_t par clé.
     */
    esp_err_t provider_data_get_int(const provider_data_t *data,
            const char *key,
            int32_t *out);

    /**
     * @brief Extraire une valeur string depuis un provider_data_t par clé.
     *
     * @param[out] out     Buffer de destination.
     * @param[in]  out_len Taille du buffer.
     */
    esp_err_t provider_data_get_string(const provider_data_t *data,
            const char *key,
            char *out,
            size_t out_len);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DATA_PROVIDER_H */
