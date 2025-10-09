#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <stdbool.h>
#include "cJSON.h"

int load_language(const char* lang_code);
const char* get_text_from_key(const char* key);
void free_language();

#endif
