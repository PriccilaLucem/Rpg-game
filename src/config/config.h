#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <SDL.h>
#include "../constants/constants.h"
typedef struct Config {
    int screen_width;
    int screen_height;
    int master_volume;

    bool fullscreen;
    bool vsync;
    bool sound_enabled;
    int volume_level;
    int  antialiasing;
    int music_volume;
    int effects_volume;
    int voice_volume;
} Config;

Config* load_config();
void save_config(Config* config);
void free_config(Config* config);
void reset_config_to_defaults(Config* config);

#endif