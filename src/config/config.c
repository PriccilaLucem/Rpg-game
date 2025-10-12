#include "./config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Config* global_config = NULL;

Config* get_config() {
    if (global_config == NULL) {
        global_config = load_config();
    }
    return global_config;
}

void unload_config() {
    if (global_config != NULL) {
        free_config(global_config);
        global_config = NULL;
    }
}

Config* load_config(){
    Config* config = malloc(sizeof(Config));
    if(config == NULL){
        printf("Failed to allocate memory for Config\n");
        return NULL;
    }
    
    
    FILE* file = fopen("config.conf", "r");
    if(file == NULL){
        printf("Config file not found, using defaults\n");
        reset_config_to_defaults(config);
        return config; // Retorna config com valores padrão
    }
    char key[50];
    char value[50];
    char *endptr;
    long parsed_value;
    
    // Initialize with defaults first
    reset_config_to_defaults(config);
    
    while(fscanf(file, "%49[^=]=%49[^\n]\n", key, value) == 2){
        if(strcmp(key, "screen_width") == 0){
            parsed_value = strtol(value, &endptr, 10);
            if(*endptr == '\0' && parsed_value > 0 && parsed_value <= 7680) {
                config->screen_width = (int)parsed_value;
            }
        } else if(strcmp(key, "screen_height") == 0){
            parsed_value = strtol(value, &endptr, 10);
            if(*endptr == '\0' && parsed_value > 0 && parsed_value <= 4320) {
                config->screen_height = (int)parsed_value;
            }
        } else if(strcmp(key, "fullscreen") == 0){
            config->fullscreen = (strcmp(value, "true") == 0);
        } else if(strcmp(key, "vsync") == 0){
            config->vsync = (strcmp(value, "true") == 0);
        } else if(strcmp(key, "sound_enabled") == 0){
            config->sound_enabled = (strcmp(value, "true") == 0);
        } else if(strcmp(key, "volume_level") == 0){
            parsed_value = strtol(value, &endptr, 10);
            if(*endptr == '\0' && parsed_value >= 0 && parsed_value <= 100) {
                config->volume_level = (int)parsed_value;
            }
        } else if(strcmp(key, "antialiasing") == 0){
            config->antialiasing = (strcmp(value, "true") == 0);
        } else if(strcmp(key, "music_volume") == 0){
            parsed_value = strtol(value, &endptr, 10);
            if(*endptr == '\0' && parsed_value >= 0 && parsed_value <= 100) {
                config->music_volume = (int)parsed_value;
            }
        } else if(strcmp(key, "effects_volume") == 0){
            parsed_value = strtol(value, &endptr, 10);
            if(*endptr == '\0' && parsed_value >= 0 && parsed_value <= 100) {
                config->effects_volume = (int)parsed_value;
            }
        } else if(strcmp(key, "voice_volume") == 0){
            parsed_value = strtol(value, &endptr, 10);
            if(*endptr == '\0' && parsed_value >= 0 && parsed_value <= 100) {
                config->voice_volume = (int)parsed_value;
            }
        } else if (strcmp(key, "font_size") == 0){
            parsed_value = strtol(value, &endptr, 10);
            if(*endptr == '\0' && parsed_value >= 8 && parsed_value <= 72) {
                config->font_size = (int)parsed_value;
            }
        } else if (strcmp(key, "language") == 0) {
            strncpy(config->language, value, sizeof(config->language) - 1);
            config->language[sizeof(config->language) - 1] = '\0';
        }
    }
    fclose(file);
    return config;
}

void save_config(Config* config){
    FILE* file = fopen("config.conf", "w");
    if(file == NULL){
        perror("Could not open config file for writing");
        return;
    }
    fprintf(file, "screen_width=%d\n", config->screen_width);
    fprintf(file, "screen_height=%d\n", config->screen_height);
    fprintf(file, "fullscreen=%s\n", config->fullscreen ? "true" : "false");
    fprintf(file, "vsync=%s\n", config->vsync ? "true" : "false");
    fprintf(file, "sound_enabled=%s\n", config->sound_enabled ? "true" : "false");
    fprintf(file, "volume_level=%d\n", config->volume_level);
    fprintf(file, "antialiasing=%s\n", config->antialiasing ? "true" : "false");
    fprintf(file, "music_volume=%d\n", config->music_volume);
    fprintf(file, "effects_volume=%d\n", config->effects_volume);
    fprintf(file, "voice_volume=%d\n", config->voice_volume);
    fclose(file);
}

void free_config(Config* config){
    if(config != NULL){
        free(config);
    }
}


void reset_config_to_defaults(Config* config){
    if(config == NULL){
        return;
    }
    config->screen_width = 1920;
    config->screen_height = 1080;
    config->fullscreen = 1;
    config->vsync = 1;
    config->sound_enabled = 1;
    config->volume_level = 70;
    config->antialiasing = 1;
    config->music_volume = 60;
    config->effects_volume = 70;
    config->voice_volume = 80;
}