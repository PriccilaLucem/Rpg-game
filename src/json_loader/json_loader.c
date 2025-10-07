#include "json_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

bool load_json_file(const char* filename, char **buffer, size_t *size) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening %s: %s\n", filename, strerror(errno));
        return false;
    }

    struct stat st;
    if (stat(filename, &st) != 0) {
        printf("Error getting size of %s: %s\n", filename, strerror(errno));
        fclose(file);
        return false;
    }

    *size = st.st_size;
    *buffer = malloc(*size + 1);
    if (!*buffer) {
        printf("Failed to allocate memory.\n");
        fclose(file);
        return false;
    }

    size_t read_size = fread(*buffer, 1, *size, file);
    (*buffer)[*size] = '\0';
    fclose(file);

    if (read_size != *size) {
        printf("Error reading %s.\n", filename);
        free(*buffer);
        return false;
    }

    return true;
}

void free_json_buffer(char* buffer) {
    if (buffer) free(buffer);
}


cJSON* load_json(const char *filename) {
    char *buffer = NULL;
    size_t size = 0;

    if (!load_json_file(filename, &buffer, &size))
        return NULL;

    cJSON *json = cJSON_Parse(buffer);
    free_json_buffer(buffer);

    if (!json) {
        printf("Error parsing JSON: %s\n", filename);
        return NULL;
    }

    return json;
}