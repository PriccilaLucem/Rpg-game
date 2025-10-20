#ifndef JSON_LOADER_H
#define JSON_LOADER_H

#include <stddef.h>
#include <stdbool.h>
// Include condicional para cJSON baseado no sistema
#ifdef _WIN32
    #include "cJSON.h"  // Windows usa o cJSON baixado
#elif __APPLE__
    #include <cjson/cJSON.h>  // macOS usa Homebrew
#else
    #include <cjson/cJSON.h>  // Linux geralmente usa pacote
#endif

bool load_json_file(const char *filename, char **buffer, size_t *size);
void free_json_buffer(char *buffer);
cJSON* load_json(const char *filename);

#endif
