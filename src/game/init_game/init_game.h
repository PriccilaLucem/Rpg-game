#ifndef INIT_GAME_H
#define INIT_GAME_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../constants/constants.h"
#include "../../structs/charater/charater.h"
#include "../../load_obj/load_obj.h"
#include "../iso_camera/iso_camera.h"
#include "../floor/floor.h"
#include "../physics/physics.h"

void render_initial_game(SDL_Renderer* renderer, MainCharater* main_charater,  Floor* floor);


#endif