#include "./config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Config* load_config(){
    Config* config = malloc(sizeof(Config));
    if(config == NULL){
        printf("Failed to allocate memory for Config\n");
        exit(EXIT_FAILURE);
    }
    FILE* file = fopen("config.conf", "r");
    if(file == NULL){
        perror("Could not open config file");
        free(config);
        printf("Using default configuration\n");
        exit(EXIT_FAILURE);
    }
    char key[50];
    char value[50];
    while(fscanf(file, "%49[^=]=%49[^\n]\n", key, value) == 2){
        if(strcmp(key, "screen_width") == 0){
            printf("CONFIG WIDTH");
            config->screen_width = atoi(value);
        } else if(strcmp(key, "screen_height") == 0){
            printf("CONFIG HEIGHT");
            config->screen_height = atoi(value);
        } else if(strcmp(key, "fullscreen") == 0){
            config->fullscreen = (strcmp(value, "true") == 0);
        } else if(strcmp(key, "vsync") == 0){
            config->vsync = (strcmp(value, "true") == 0);
        } else if(strcmp(key, "sound_enabled") == 0){
            config->sound_enabled = (strcmp(value, "true") == 0);
        } else if(strcmp(key, "volume_level") == 0){
            config->volume_level = atoi(value);
        } else if(strcmp(key, "antialiasing") == 0){
            config->antialiasing = (strcmp(value, "true") == 0);
        } else if(strcmp(key, "music_volume") == 0){
            config->music_volume = atoi(value);
        } else if(strcmp(key, "effects_volume") == 0){
            config->effects_volume = atoi(value);
        } else if(strcmp(key, "voice_volume") == 0){
            config->voice_volume = atoi(value);
        }
    }
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