#ifndef PROVIDER_MANAGER_H
#define PROVIDER_MANAGER_H

#include "data_provider.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

    // ─────────────────────────────────────────────────────────────────────────────
    //  Initialisation — appelée une fois dans INIT_SETUP_HW
    // ─────────────────────────────────────────────────────────────────────────────

    /**
     * @brief Initialise tous les providers compilés (selon Kconfig).
     *
     * Parcourt le registre statique des providers, appelle leur init(),
     * et stocke le résultat dans provider->state. Un provider qui échoue
     * passe en PROVIDER_STATUS_ERROR_INIT — le boot continue quoi qu'il arrive.
     *
     * Appelé dans state_init_handler.c, case INIT_SETUP_HW.
     */
    void provider_manager_init(void);

    // ─────────────────────────────────────────────────────────────────────────────
    //  API consommée par les widgets dans update_data_function()
    // ─────────────────────────────────────────────────────────────────────────────

    /**
     * @brief Récupère les données d'un provider par nom.
     *
     * Comportement :
     * - Si le provider est en erreur → retourne ses données avec status ERROR.
     * - Si le cache est frais (now - last_read < cache_ttl) → retourne le cache.
     * - Sinon → appelle read(), met à jour le cache, retourne les nouvelles données.
     *
     * @param[in]  name  Nom du provider (ex: "battery", "bme680").
     * @param[out] out   Pointeur qui sera pointé vers le buffer statique du provider.
     *                   Ne pas stocker ce pointeur — il pointe vers de la mémoire statique
     *                   qui peut être mise à jour au prochain appel.
     *
     * @return ESP_OK si le provider existe (même en cas d'erreur de lecture).
     *         ESP_ERR_NOT_FOUND si le provider n'est pas dans le registre.
     */
    esp_err_t provider_get(const char *name, const provider_data_t **out);

    /**
     * @brief Force une lecture hardware, bypass le cache TTL.
     *
     * Utile pour un widget qui a besoin d'une valeur fraîche au moment
     * d'un événement particulier (ex: affichage au wake-up).
     *
     * @param[in]  name  Nom du provider.
     * @param[out] out   Pointeur vers le buffer statique mis à jour.
     *
     * @return ESP_OK si lecture réussie, ESP_FAIL si read() a échoué,
     *         ESP_ERR_NOT_FOUND si provider inconnu.
     */
    esp_err_t provider_force_read(const char *name, const provider_data_t **out);

    /**
     * @brief Retourne l'état courant d'un provider.
     *
     * Permet à un widget de vérifier si son provider est disponible
     * avant d'essayer de lire des données.
     *
     * @param[in]  name    Nom du provider.
     * @param[out] status  État courant.
     *
     * @return ESP_OK si provider trouvé, ESP_ERR_NOT_FOUND sinon.
     */
    esp_err_t provider_get_status(const char *name, provider_status_t *status);

    // ─────────────────────────────────────────────────────────────────────────────
    //  Registration — utilisée par provider_manager.c uniquement
    //  (et par gen_providers.py à terme)
    // ─────────────────────────────────────────────────────────────────────────────

    /**
     * @brief Enregistre un provider dans le registre global.
     *
     * Appelé dans provider_manager_init() via le tableau statique des providers.
     * Ne pas appeler directement depuis un widget.
     *
     * @param[in] provider Pointeur vers la struct statique du provider.
     *
     * @return ESP_OK si enregistré, ESP_ERR_NO_MEM si le registre est plein.
     */
    esp_err_t provider_register(data_provider_t *provider);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PROVIDER_MANAGER_H */
