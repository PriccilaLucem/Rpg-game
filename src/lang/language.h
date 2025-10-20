#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <stdbool.h>

// Include condicional para cJSON baseado no sistema
#ifdef _WIN32
    #include "cJSON.h"  // Windows usa o cJSON baixado
#elif __APPLE__
    #include <cjson/cJSON.h>  // macOS usa Homebrew
#else
    #include <cjson/cJSON.h>  // Linux geralmente usa pacote
#endif

int load_language(const char* lang_code);
const char* get_text_from_key(const char* key);
void free_language();

#endif
