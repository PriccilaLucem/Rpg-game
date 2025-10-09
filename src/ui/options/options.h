#ifndef OPTIONS_H
#define OPTIONS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../../config/config.h"
#include "../button/button.h"

typedef struct Options {
    Config* config;
    SDL_Renderer* renderer;
    TTF_Font* screen_title_font;
    TTF_Font* button_font;
    SDL_Texture* texture;
    
    // Buttons
    Button* screen_size_left_arrow;
    Button* screen_size_right_arrow;
    Button* screen_size;
    Button* full_screen;
    Button* vsync;
    Button* sound;
    Button* volume;
    Button* antialiasing;
    Button* music_volume;
    Button* effects_volume;
    Button* voice_volume;
    Button* save;
    Button* reset;
    Button* back_to_main_menu;
} Options;

// Public functions
Options* init_options(int width, int height, SDL_Renderer* renderer, int font_size);
void free_options(Options* options);
void handle_options_input(SDL_Event* event, Options* options);
void render_options(Options* options, SDL_Renderer* renderer);
void update_options(Options* options);
void update_screen_size_button_text(Options* options, SDL_Renderer* renderer);
void update_button_geometry(Options* options, int screen_width, int screen_height);
void apply_resolution(Options* options);

// Button callbacks
void screen_size_left_arrow_onClick(void* data);
void screen_size_right_arrow_onClick(void* data);

#endif