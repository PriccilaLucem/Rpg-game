#ifndef JSON_LOADER_H
#define JSON_LOADER_H

#include <stddef.h>
#include <stdbool.h>
#include "cJSON.h"

bool load_json_file(const char *filename, char **buffer, size_t *size);
void free_json_buffer(char *buffer);
cJSON* load_json(const char *filename);

#endif
