#ifndef GAME_H
#define GAME_H 

#include <SDL.h>
#include <SDL_ttf.h>
#include "./init_game/init_game.h"
#include "../structs/character/basic_character.h"
#include "./ui/character_build.h"

typedef enum {
    INITIAL_SCREEN,
    GAME_SCREEN,
}ScreenEnum;


typedef struct Game {
    
    SDL_Renderer* renderer;
    TTF_Font* font;
    MainCharacter* main_character;
    ScreenEnum game_enum;
    
    union 
    {
        CharacterBuild* char_build;
    } InitGame;
    
    
} Game;

Game* init_game(int screen_width, int screen_height, SDL_Renderer* renderer, int font_size);
void render_game(Game* game, SDL_Renderer* event);
void free_game(Game* game);
void handle_game_events(Game* game, SDL_Event* event);

#endif