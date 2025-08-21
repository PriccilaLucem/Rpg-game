#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../button/button.h"


typedef struct {
    TTF_Font* title;
    int font_size;
    int screen_size_h;
    int screen_size_w;
    Button* start_game;
    Button* load_game;
    Button* options;
    Button* exit;
} Menu;

Menu* init_menu(int screen_width, int screen_height, int font_size);
void render_menu_title(Menu* menu, SDL_Renderer* renderer, const char* title_text);
void handle_start_button();
void handle_option_button();
void handle_exit_button();
void handle_load_game_button();


#endif