#include "options_handlers.h"
#include "../button/button.h"
#include "../../states/states.h"
#include "../../config/config.h"
#include <SDL.h>

extern SDL_Window* window;

/* ===== INPUT HANDLERS ===== */

void handle_mouse_motion(Options* options, int mouse_x, int mouse_y) {
    Button* buttons[] = {
        options->screen_size_left_arrow, options->screen_size_right_arrow, options->screen_size,
        options->full_screen, options->vsync, options->sound, options->volume,
        options->antialiasing, options->music_volume, options->effects_volume,
        options->voice_volume, options->save, options->reset,
        options->back_to_main_menu, NULL
    };

    for (int i = 0; buttons[i] != NULL; i++) {
        check_button_hover(buttons[i], mouse_x, mouse_y);
    }
}

void handle_mouse_click(Options* options, int mouse_x, int mouse_y) {
    // Handle resolution buttons
    if (check_button_click(options->screen_size_left_arrow, mouse_x, mouse_y)) {
        screen_size_left_arrow_onClick(options);
        return;
    }
    if (check_button_click(options->screen_size_right_arrow, mouse_x, mouse_y)) {
        screen_size_right_arrow_onClick(options);
        return;
    }

    // Handle configuration buttons
    if (check_button_click(options->full_screen, mouse_x, mouse_y)) {
        handle_fullscreen_toggle(options);
    }
    else if (check_button_click(options->vsync, mouse_x, mouse_y)) {
        handle_vsync_toggle(options);
    }
    else if (check_button_click(options->sound, mouse_x, mouse_y)) {
        handle_sound_toggle(options);
    }
    else if (check_button_click(options->volume, mouse_x, mouse_y)) {
        handle_volume_click(options);
    }
    else if (check_button_click(options->antialiasing, mouse_x, mouse_y)) {
        handle_antialiasing_click(options);
    }
    else if (check_button_click(options->music_volume, mouse_x, mouse_y)) {
        handle_music_volume_click(options);
    }
    else if (check_button_click(options->effects_volume, mouse_x, mouse_y)) {
        handle_effects_volume_click(options);
    }
    else if (check_button_click(options->voice_volume, mouse_x, mouse_y)) {
        handle_voice_volume_click(options);
    }
    else if (check_button_click(options->save, mouse_x, mouse_y)) {
        handle_save_click(options);
    }
    else if (check_button_click(options->reset, mouse_x, mouse_y)) {
        handle_reset_click(options);
    }
    else if (check_button_click(options->back_to_main_menu, mouse_x, mouse_y)) {
        handle_back_to_main_menu();
    }
}

/* ===== BUTTON HANDLER FUNCTIONS ===== */

void handle_fullscreen_toggle(Options* options) {
    options->config->fullscreen = !options->config->fullscreen;
    SDL_SetWindowFullscreen(window, options->config->fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
    update_options(options);
}

void handle_vsync_toggle(Options* options) {
    options->config->vsync = !options->config->vsync;
    update_options(options);
}

void handle_sound_toggle(Options* options) {
    options->config->sound_enabled = !options->config->sound_enabled;
    update_options(options);
}

void handle_volume_click(Options* options) {
    options->config->volume_level = (options->config->volume_level + 10) % 110;
    if (options->config->volume_level == 0) options->config->volume_level = 10;
    update_options(options);
}

void handle_antialiasing_click(Options* options) {
    if (options->config->antialiasing == 0) options->config->antialiasing = 2;
    else if (options->config->antialiasing == 2) options->config->antialiasing = 4;
    else if (options->config->antialiasing == 4) options->config->antialiasing = 8;
    else options->config->antialiasing = 0;
    update_options(options);
}

void handle_music_volume_click(Options* options) {
    options->config->music_volume = (options->config->music_volume + 10) % 110;
    if (options->config->music_volume == 0) options->config->music_volume = 10;
    update_options(options);
}

void handle_effects_volume_click(Options* options) {
    options->config->effects_volume = (options->config->effects_volume + 10) % 110;
    if (options->config->effects_volume == 0) options->config->effects_volume = 10;
    update_options(options);
}

void handle_voice_volume_click(Options* options) {
    options->config->voice_volume = (options->config->voice_volume + 10) % 110;
    if (options->config->voice_volume == 0) options->config->voice_volume = 10;
    update_options(options);
}

void handle_save_click(Options* options) {
    save_config(options->config);
}

void handle_reset_click(Options* options) {
    reset_config_to_defaults(options->config);
    save_config(options->config);
    update_options(options);
}

void handle_back_to_main_menu() {
    change_state(STATE_MAIN_MENU);
}