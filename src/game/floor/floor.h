#ifndef FLOOR_H
#define FLOOR_H

#include <SDL.h>
#include "../../load_obj/load_obj.h"
#include <stdlib.h>

typedef struct {
    OBJ_Model* model;
    SDL_Rect rect;
} Floor;

Floor* init_floor(const char* path);

#endif