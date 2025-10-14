#ifndef VILLAGE_MACCARENA_H
#define VILLAGE_MACCARENA_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../structs/house/house.h"
#include "../../structs/floor/floor.h"
#include "../../load_obj/load_obj.h"
#include "../../camera/iso_camera.h"
#include "../../structs/charater/charater.h"

typedef struct {
    House* house;
    Floor** floors;
    int num_floors;
    int current_floor;
    IsoCamera* camera;
    MainCharater* main_charater;
} VillageMaccarena;

VillageMaccarena* init_village_maccarena(SDL_Renderer* renderer);
void render_village_maccarena(SDL_Renderer* renderer, VillageMaccarena* village);
void destroy_village_maccarena(VillageMaccarena* village);



#endif