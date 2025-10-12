#ifndef OPTIONS_H
#define OPTIONS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../../config/config.h"
#include "../button/button.h"

typedef struct ScreenResolution {
    int width;
    int height;
} ScreenResolution;

typedef struct LanguageOption {
    char code[8];
    char name[32];
} LanguageOption;

typedef struct Options {
    Config* config;
    SDL_Renderer* renderer;
    TTF_Font* screen_title_font;
    TTF_Font* button_font;
    SDL_Texture* texture;
    
    // Buttons
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
    ButtonDropdown* resolution_dropdown;
    ButtonDropdown* language_dropdown;
} Options;

// Public functions
Options* init_options(int width, int height, SDL_Renderer* renderer, int font_size);
void free_options(Options* options);
void handle_options_input(SDL_Event* event, Options* options);
void render_options(Options* options, SDL_Renderer* renderer);
void update_options(Options* options);
void update_resolution_dropdown_text(Options* options);
void update_button_geometry(Options* options, int screen_width, int screen_height);
void apply_resolution(Options* options);
void change_language(Options* options, const char* lang_code);

// Dropdown functions
ButtonDropdown* init_button_dropdown(int x, int y, int width, int height, int item_count, DropdownItem** dropdown_itens, const char* text, TTF_Font* font, SDL_Color textColor);
void render_button_dropdown(ButtonDropdown* dropdown, SDL_Renderer* renderer);
void render_button_dropdown_options(ButtonDropdown* dropdown, SDL_Renderer* renderer);
void free_button_dropdown(ButtonDropdown* dropdown);
void open_button_dropdown(ButtonDropdown* dropdown);
void close_button_dropdown(ButtonDropdown* dropdown);
void init_resolution_dropdown(Options* options);
void init_language_dropdown(Options* options);
void handle_dropdown_click(Options* options, int mouse_x, int mouse_y);

// Missing function declarations
void render_title(Options* options, SDL_Renderer* renderer, int screen_width);
void render_all_buttons(Options* options, SDL_Renderer* renderer);
void create_title_texture(Options* options, SDL_Renderer* renderer);
void initialize_buttons_textures(Options* options);
void update_all_buttons_textures(Options* options);
void handle_mouse_motion(Options* options, int mouse_x, int mouse_y);
void handle_mouse_click(Options* options, int mouse_x, int mouse_y);
void update_button_texture(Button* button, SDL_Renderer* renderer, TTF_Font* font);

// Button callbacks
void fullscreen_onClick(void* data);
void vsync_onClick(void* data);
void sound_onClick(void* data);
void volume_onClick(void* data);
void antialiasing_onClick(void* data);
void music_volume_onClick(void* data);
void effects_volume_onClick(void* data);
void voice_volume_onClick(void* data);
void save_onClick(void* data);
void reset_onClick(void* data);
void back_to_main_menu_onClick(void* data);
void handle_dropdown_click_dropdown(Options* options, int mouse_x, int mouse_y);
#endif