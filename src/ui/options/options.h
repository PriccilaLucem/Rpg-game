// options.h
#ifndef OPTIONS_H
#define OPTIONS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../../config/config.h"
#include "../button/button.h"
#include "../../constants/constants.h"
#include "../../states/states.h"

extern Config* current_config;
extern SDL_Window* window;
extern SDL_Renderer* renderer;

typedef struct Options {
    int id;
    TTF_Font* font;
    Config* config;
    
    SDL_Renderer* renderer;
    // Screen title
    char* screen_title;
    
    // Option buttons
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
    Button* load;
    Button* reset;
    Button* back_to_main_menu;
} Options;

Options* init_options(int x, int y, int width, int height, SDL_Renderer* renderer);
void free_options(Options* options);
void handle_options_input(SDL_Event* event, Options* options);
void render_options(Options* options, SDL_Renderer* renderer);
void update_screen_size_button_text(Options* options, SDL_Renderer* renderer);
void apply_resolution(Options* options);
SDL_Texture* create_text_texture(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color);
void update_options(Options* options);
void screen_size_left_arrow_onClick(void* data);
void screen_size_right_arrow_onClick(void* data);
void update_state(Menu* main_menu, Options* options);
void cleanup_states(Menu* main_menu, Options* options);
void change_state(GameState new_state);
void apply_resolution(Options* options);
void render_options(Options* options, SDL_Renderer* renderer);

#endif