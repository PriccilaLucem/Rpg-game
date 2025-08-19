#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>

#define PATH_TO_FONT "src/assets/fonts/Luckiest_Guy,Playfair_Display/Luckiest_Guy/LuckiestGuy-Regular.ttf"

void render_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);
void button_action(int button_id);
void render_menu(SDL_Renderer* renderer, TTF_Font* font);
void handle_menu_events(SDL_Event* event, int* running, int* game_state);

#endif