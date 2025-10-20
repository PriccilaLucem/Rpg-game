#include "./language.h"
// Include condicional para cJSON baseado no sistema
#ifdef _WIN32
    #include "cJSON.h"  // Windows usa o cJSON baixado
#elif __APPLE__
    #include <cjson/cJSON.h>  // macOS usa Homebrew
#else
    #include <cjson/cJSON.h>  // Linux geralmente usa pacote
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static cJSON* current_language_json = NULL;

int load_language(const char* lang_code) {
    char path[256];  // Increased buffer size
#ifdef _WIN32
    snprintf(path, sizeof(path), "assets/lang/%s.json", lang_code);
#else
    snprintf(path, sizeof(path), "./assets/lang/%s.json", lang_code);
#endif

    printf("Loading language file: %s\n", path);  // Debug print

    FILE* file = fopen(path, "rb");
    if (!file) {
        printf("Could not open language file: %s\n", path);
        
        // Try alternative paths
#ifdef _WIN32
        snprintf(path, sizeof(path), "src/assets/lang/%s.json", lang_code);
#else
        snprintf(path, sizeof(path), "./src/assets/lang/%s.json", lang_code);
#endif
        
        printf("Trying alternative path: %s\n", path);
        file = fopen(path, "rb");
        if (!file) {
            printf("Could not open language file at alternative path: %s\n", path);
            return 0;
        }
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buffer = malloc(size + 1);
    if (!buffer) {
        printf("Failed to allocate memory for language file\n");
        fclose(file);
        return 0;
    }

    size_t read_size = fread(buffer, 1, size, file);
    if (read_size != (size_t)size) {
        printf("Failed to read language file\n");
        free(buffer);
        fclose(file);
        return 0;
    }
    
    buffer[size] = '\0';
    fclose(file);

    current_language_json = cJSON_Parse(buffer);
    free(buffer);

    if (!current_language_json) {
        printf("Failed to parse language JSON\n");
        return 0;
    }

    printf("Successfully loaded language: %s\n", lang_code);
    return 1;
}

const char* get_text_from_key(const char* key) {
    if (!current_language_json || !key) {
        printf("No language loaded or null key: %s\n", key);
        return key;
    }

    printf("Looking up key: %s\n", key);  // Debug print

    char key_copy[128];
    strncpy(key_copy, key, sizeof(key_copy) - 1);
    key_copy[sizeof(key_copy) - 1] = '\0';

    char* section = NULL;
    char* subkey = NULL;
    char* dot_pos = strchr(key_copy, '.');
    if (dot_pos) {
        *dot_pos = '\0';
        section = key_copy;
        subkey = dot_pos + 1;
    }

    if (!section || !subkey) {
        printf("Invalid key format: %s\n", key);
        return key;
    }

    cJSON* section_obj = cJSON_GetObjectItemCaseSensitive(current_language_json, section);
    if (!section_obj) {
        printf("Section not found: %s\n", section);
        return key;
    }

    cJSON* value = cJSON_GetObjectItemCaseSensitive(section_obj, subkey);
    if (!value || !cJSON_IsString(value)) {
        printf("Key not found or not string: %s.%s\n", section, subkey);
        return key;
    }

    printf("Found translation: %s -> %s\n", key, value->valuestring);
    return value->valuestring;
}

void free_language() {
    if (current_language_json) {
        cJSON_Delete(current_language_json);
        current_language_json = NULL;
    }
}