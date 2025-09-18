#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../music/music.h"
#include "../button/button.h"
#include "../button/button.h"
#include "../../constants/constants.h"
#include "../../states/states.h"
typedef struct Menu {
    int id;
    Music* music;
    TTF_Font* title;
    int selected_index;
    int font_size;
    int screen_size_h;
    int screen_size_w;
    int* selected_button; 
    Button* start_game;
    Button* load_game;
    Button* options;
    Button* exit;
} Menu;

Menu* init_menu(int screen_width, int screen_height, int font_size);
void render_menu(Menu* menu, SDL_Renderer* renderer);
void handle_menu_input(Menu* menu, SDL_Event* event);
void free_main_menu(Menu* menu);
void update_main_menu(Menu* menu);
void handle_menu_input(Menu* menu, SDL_Event* event);
#endif