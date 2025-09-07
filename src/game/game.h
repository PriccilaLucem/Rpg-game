#ifndef GAME_H
#define GAME_H 

#include <SDL.h>
#include <SDL_ttf.h>
#include "./iso_camera/iso_camera.h"
#include "./init_game/init_game.h"
#include "../structs/charater/charater.h"
#include "./ui/charater_build.h"
#include "../ui/button/button.h"
#include "./floor/floor.h"

typedef enum ScreenEnum {
    INITIAL_SCREEN,
    GAME_SCREEN,
} ScreenEnum;

typedef struct Game {
    charaterBuild* char_build;
    SDL_Renderer* renderer;
    Floor* floor;
    TTF_Font* font;
    MainCharater* main_charater;
    ScreenEnum game_enum;
} Game;

Game* init_game(int screen_width, int screen_height, SDL_Renderer* renderer, int font_size);
void render_game(Game* game, SDL_Renderer* renderer);
void free_game(Game* game);
void handle_game_events(Game* game, SDL_Event* event);

#endif
