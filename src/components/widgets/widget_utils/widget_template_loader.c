#include "cJSON.h"
#include "esp_err.h"
#include "esp_log.h"
#include "filesystem_interface.h"
#include "widget.h"
#include <fcntl.h>
#include <string.h>
#include <sys/param.h>

static esp_err_t validate_template_json(cJSON *root);
static esp_err_t create_instance_from_template(cJSON *tmpl, const char *instance_path);

esp_err_t init_widget_from_template(widget_t *widget, const char *json_path)
{
    if (!widget || !json_path) 
        return ESP_FAIL;

    cJSON *tmpl = NULL;
    char template_path[MAX_PATH_LEN];
    lfs_get_template_path(json_path, template_path, sizeof(template_path));
    tmpl = read_json_file(template_path, READ_LFS);
    if (!tmpl)
    {
        ESP_LOGE("init_widget_from_template", "Failed to read template %s", json_path);
        return ESP_FAIL;
    }

    if (validate_template_json(tmpl) == ESP_FAIL)
    {
        ESP_LOGE("init_widget_from_template", "Failed to validate template %s", json_path);
        cJSON_Delete(tmpl);
        return ESP_FAIL;
    }

    char instance_path[MAX_PATH_LEN];
    lfs_get_instance_path(json_path, instance_path, sizeof(instance_path));

    // If instance does not exist -> create it (copy template + ensure config/data/flag)
    if (check_file_lfs(instance_path) != ESP_OK)
    {
        if (create_instance_from_template(tmpl, instance_path) != ESP_OK)
        {
            ESP_LOGE("init_widget_from_template", "Failed to create instance for template %s", json_path);
            cJSON_Delete(tmpl);
            return ESP_FAIL;
        }
        update_widget_struct_from_template(widget, tmpl);
        cJSON_Delete(tmpl);
    }
    else
    {
        // Fill widget_t using your existing loader (reads instance file and updates struct)
        ESP_LOGI("init_widget_from_template", "Instance already exists: %s", json_path);
        cJSON *widget_json = read_json_file(instance_path, READ_LFS);
        if (widget_json != NULL)
        {
            update_widget_struct_from_template(widget, widget_json);
            ESP_LOGI("init_widget_from_template", "Instance: %s", cJSON_Print(widget_json));
        }
        cJSON_Delete(widget_json);
    }

    return ESP_OK;
}

/**
 * @brief Validates the structure of a widget template JSON.
 *
 * Ensures required fields (type, size, position, flag, config, etc.)
 * are present and correctly formatted in the template.
 *
 * @param[in] root Pointer to the cJSON root object of the template.
 *
 * @return
 * - ESP_OK if the template is valid
 * - ESP_FAIL if required fields are missing or invalid
 */
static esp_err_t validate_template_json(cJSON *root)
{
    if (!cJSON_IsObject(root))
    {
        ESP_LOGE("validate_template_json", "root is not an objet");
        return ESP_FAIL;
    }

    // widget_type (string)
    cJSON *wtype = cJSON_GetObjectItem(root, "widget_type");
    if (!cJSON_IsString(wtype) || wtype->valuestring == NULL)
    {
        ESP_LOGE("validate_template_json", "missing or invalid 'widget_type");
        return ESP_FAIL;
    }

    // width (number)
    cJSON *width = cJSON_GetObjectItem(root, "width");
    if (!cJSON_IsNumber(width) || width->valueint <= 0)
    {
        ESP_LOGE("validate_template_json", "missing or invalid 'width'");
        return ESP_FAIL;
    }

    // height (number)
    cJSON *height = cJSON_GetObjectItem(root, "height");
    if (!cJSON_IsNumber(height) || height->valueint <= 0)
    {
        ESP_LOGE("validate_template_json", "missing or invalid 'height'");
        return ESP_FAIL;
    }

    // position.x / position.y
    cJSON *pos = cJSON_GetObjectItem(root, "position");
    if (!cJSON_IsObject(pos))
    {
        ESP_LOGE("validate_template_json", "missing 'position' objet");
        return ESP_FAIL;
    }

    cJSON *px = cJSON_GetObjectItem(pos, "x");
    cJSON *py = cJSON_GetObjectItem(pos, "y");
    if (!cJSON_IsNumber(px) || !cJSON_IsNumber(py))
    {
        ESP_LOGE("validate_template_json", "position.x / position.y must be numbers");
        return ESP_FAIL;
    }

    // flag
    cJSON *flag = cJSON_GetObjectItem(root, "flag");
    if (!cJSON_IsNumber(flag))
    {
        ESP_LOGE("validate_template_json", "missing or invalid 'flag'");
        return ESP_FAIL;
    }

    return ESP_OK;
}

/**
 * @brief Creates a widget instance file from a template.
 *
 * Generates a deep copy of the template JSON, removes non-instance
 * fields, and writes it to the specified path in LittleFS.
 *
 * @param[in] tmpl           Pointer to the template JSON object.
 * @param[in] instance_path  Full path to the instance file to create.
 *
 * @return
 * - ESP_OK on success
 * - ESP_FAIL if creation or write fails
 */
static esp_err_t create_instance_from_template(cJSON *tmpl, const char *instance_path)
{
    cJSON *inst = NULL;
    char *out = NULL;

    if (!tmpl || !instance_path)
        return ESP_FAIL;

    // deep copy
    inst = cJSON_Duplicate(tmpl, 1);
    if (!inst)
        return ESP_FAIL;

    cJSON_DeleteItemFromObject(inst, "label");
    cJSON_DeleteItemFromObject(inst, "iconType");
    cJSON_DeleteItemFromObject(inst, "layout");
    cJSON_DeleteItemFromObject(inst, "elements");

    out = cJSON_Print(inst);
    if (!out)
    {
        cJSON_Delete(inst);
        return ESP_FAIL;
    }

    esp_err_t wr = write_file_lfs(instance_path, out);
    if (wr != ESP_OK)
    {
        ESP_LOGE("create_instance_from_template", "Failed to write instance file '%s'", instance_path);
    }
    else
    {
        ESP_LOGI("create_instance_from_template", "Instance created: %s", instance_path);
        ESP_LOGI("create_instance_from_template", "%s", out);
    }

    free(out);
    cJSON_Delete(inst);
    return wr;
}
