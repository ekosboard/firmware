#include "filesystem_interface.h"

/* Reads a JSON file from SPI Flash and parses it into a cJSON object */
/* @Parameters: */
/*     - path: Path to the JSON file stored in SPI Flash. */
/* @Return: */
/*     - A pointer to a cJSON object representing the parsed JSON data, or NULL if an error occurs. */
cJSON *read_json_file(const char *path)
{
    char full_path[128];

    snprintf(full_path, sizeof(full_path), "/spiflash/%s", path);
    FILE *file = fopen(full_path, "rb");
    if (file == NULL)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(len + 1);
    if (data == NULL)
    {
        fclose(file);
        return NULL;
    }

    fread(data, 1, len, file);
    data[len] = '\0';
    fclose(file);

    // 2. Parse le JSON
    cJSON *widget_json = cJSON_Parse(data);
    free(data);
    if (widget_json == NULL)
    {
        return NULL;
    }

    return widget_json;
}
