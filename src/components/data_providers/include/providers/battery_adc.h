#ifndef BATTERY_ADC_H
#define BATTERY_ADC_H

#include "data_provider.h"

#define BATTERY_ADC_UNIT        ADC_UNIT_1
#define BATTERY_ADC_CHANNEL     ADC_CHANNEL_0       // GPIO1
#define BATTERY_ADC_ATTEN       ADC_ATTEN_DB_0      // Plage 0–0.95V

// Pont diviseur : 680kΩ / 150kΩ → ratio = 150 / (680 + 150)
#define BATTERY_DIVIDER_RATIO   (150.0f / (680.0f + 150.0f))   // ≈ 0.1807

// LiPo 1S
#define BATTERY_V_MIN           3.0f    // Tension vide (0%)
#define BATTERY_V_MAX           4.2f    // Tension pleine (100%)

// Nombre de lectures moyennées pour réduire le bruit ADC
#define BATTERY_ADC_SAMPLES     8

// Cache TTL
#define BATTERY_CACHE_TTL_MS    (30 * 1000)   // 30 secondes

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Retourne le pointeur vers le provider batterie statique.
     *
     * Appelé par provider_manager_init() si CONFIG_PROVIDER_BATTERY est activé.
     * Ne pas appeler directement depuis un widget — passer par provider_get("battery").
     *
     * Valeurs exposées :
     *   - "battery_pct"     (FLOAT)  : pourcentage de charge (0.0 – 100.0)
     *   - "battery_voltage" (FLOAT)  : tension mesurée en Volts (ex: 3.85)
     *
     * Matériel :
     *   - GPIO1 / ADC1_CH0
     *   - Pont diviseur : 680kΩ (série BAT+) / 150kΩ (série GND)
     *   - Ratio : 150 / (680 + 150) ≈ 0.1807
     *   - LiPo 1S : 3.0V (vide) → 4.2V (plein)
     */
    data_provider_t *battery_adc_get_provider(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BATTERY_ADC_H */
