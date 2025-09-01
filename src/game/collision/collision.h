#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "../../structs/character/basic_character.h"

bool check_collision(SDL_Rect a, SDL_Rect b);

#endif