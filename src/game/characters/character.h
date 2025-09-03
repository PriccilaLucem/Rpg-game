#ifndef GAME_CHAR_H
#define GAME_CHAR_H


#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include "../../structs/character/basic_character.h"
#include "../../ui/button/button.h"
#include "../../load_obj/load_obj.h"

extern OBJ_Model* obj_model;


void input(SDL_Event* event);



#endif