#ifndef INIT_GAME_H
#define INIT_GAME_H

#include <SDL.h>
#include <stdbool.h>
#include "../../structs/character/basic_character.h"
#include "../floor/floor.h"

typedef struct {
    BasicCharacter* main_character;
    Floor* floor;
} InitialGame;

void render_init_game(SDL_Renderer* renderer);
#endif