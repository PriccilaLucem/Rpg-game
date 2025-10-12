#include "options.h"
#include "../../states/states.h"

// Button callback functions
void fullscreen_onClick(void* data) {
    Options* options = (Options*)data;
    if (!options || !options->config) return;
    
    options->config->fullscreen = !options->config->fullscreen;
    save_config(options->config);
    update_options(options);
    printf("Fullscreen toggled: %s\n", options->config->fullscreen ? "ON" : "OFF");
}

void vsync_onClick(void* data) {
    Options* options = (Options*)data;
    if (!options || !options->config) return;
    
    options->config->vsync = !options->config->vsync;
    save_config(options->config);
    update_options(options);
    printf("VSync toggled: %s\n", options->config->vsync ? "ON" : "OFF");
}

void sound_onClick(void* data) {
    Options* options = (Options*)data;
    if (!options || !options->config) return;
    
    options->config->sound_enabled = !options->config->sound_enabled;
    save_config(options->config);
    update_options(options);
    printf("Sound toggled: %s\n", options->config->sound_enabled ? "ON" : "OFF");
}

void volume_onClick(void* data) {
    Options* options = (Options*)data;
    if (!options || !options->config) return;
    
    options->config->volume_level += 10;
    if (options->config->volume_level > 100) {
        options->config->volume_level = 0;
    }
    save_config(options->config);
    update_options(options);
    printf("Volume set to: %d\n", options->config->volume_level);
}

void antialiasing_onClick(void* data) {
    Options* options = (Options*)data;
    if (!options || !options->config) return;
    
    options->config->antialiasing = !options->config->antialiasing;
    save_config(options->config);
    update_options(options);
    printf("Antialiasing toggled: %s\n", options->config->antialiasing ? "ON" : "OFF");
}

void music_volume_onClick(void* data) {
    Options* options = (Options*)data;
    if (!options || !options->config) return;
    
    options->config->music_volume += 10;
    if (options->config->music_volume > 100) {
        options->config->music_volume = 0;
    }
    save_config(options->config);
    update_options(options);
    printf("Music volume set to: %d\n", options->config->music_volume);
}

void effects_volume_onClick(void* data) {
    Options* options = (Options*)data;
    if (!options || !options->config) return;
    
    options->config->effects_volume += 10;
    if (options->config->effects_volume > 100) {
        options->config->effects_volume = 0;
    }
    save_config(options->config);
    update_options(options);
    printf("Effects volume set to: %d\n", options->config->effects_volume);
}

void voice_volume_onClick(void* data) {
    Options* options = (Options*)data;
    if (!options || !options->config) return;
    
    options->config->voice_volume += 10;
    if (options->config->voice_volume > 100) {
        options->config->voice_volume = 0;
    }
    save_config(options->config);
    update_options(options);
    printf("Voice volume set to: %d\n", options->config->voice_volume);
}

void save_onClick(void* data) {
    Options* options = (Options*)data;
    if (!options || !options->config) return;
    
    save_config(options->config);
    printf("Configuration saved!\n");
}

void reset_onClick(void* data) {
    Options* options = (Options*)data;
    if (!options || !options->config) return;
    
    reset_config_to_defaults(options->config);
    save_config(options->config);
    update_options(options);
    printf("Configuration reset to defaults!\n");
}

void back_to_main_menu_onClick(void* data) {
    printf("Returning to main menu\n");
    change_state(STATE_MAIN_MENU);
}