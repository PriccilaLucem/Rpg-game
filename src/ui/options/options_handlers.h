#ifndef OPTIONS_HANDLERS_H
#define OPTIONS_HANDLERS_H

#include "options.h"

// Input handlers
void handle_mouse_motion(Options* options, int mouse_x, int mouse_y);
void handle_mouse_click(Options* options, int mouse_x, int mouse_y);
void handle_dropdown_click(Options* options, int mouse_x, int mouse_y);

// Button handlers
void handle_fullscreen_toggle(Options* options);
void handle_vsync_toggle(Options* options);
void handle_sound_toggle(Options* options);
void handle_volume_click(Options* options);
void handle_antialiasing_click(Options* options);
void handle_music_volume_click(Options* options);
void handle_effects_volume_click(Options* options);
void handle_voice_volume_click(Options* options);
void handle_save_click(Options* options);
void handle_reset_click(Options* options);
void handle_back_to_main_menu();

#endif