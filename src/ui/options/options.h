#ifndef OPTIONS_H
#define OPTIONS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../button/button.h"
#include "../../config/config.h"

typedef struct {
    Button* button;
    const char* format;
    union {
        const char* string_value;
        int int_value;
    };
    int value_type;
} ButtonConfig;

#define STRING_VALUE 0
#define INT_VALUE 1

typedef struct Options {
    Config* config;
    TTF_Font* screen_title_font;
    TTF_Font* button_font;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    
    // Left column buttons
    Button* screen_size_left_arrow;
    Button* screen_size;
    Button* screen_size_right_arrow;
    Button* full_screen;
    Button* vsync;
    Button* sound;
    Button* volume;
    Button* antialiasing;
    Button* music_volume;
    Button* effects_volume;
    Button* voice_volume;
    
    // Right column buttonsX
    Button* save;
    Button* load;
    Button* reset;
    Button* back_to_main_menu;
} Options;

// Public functions
Options* init_options(int width, int height, SDL_Renderer* renderer, int font_size);
void free_options(Options* options);
void update_options(Options* options);
void update_screen_size_button_text(Options* options, SDL_Renderer* renderer);
void handle_options_input(SDL_Event* event, Options* options);
void render_options(Options* options, SDL_Renderer* renderer, int screen_width);
void apply_resolution(Options* options);
void update_button_geometry(Options* options, int screen_width, int screen_height);

#endif