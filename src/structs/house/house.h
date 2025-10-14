#ifndef HOUSE_H
#define HOUSE_H

#include "../../load_obj/load_obj.h"

typedef struct House {
    OBJ_Model* model;
    float scale;
    float position_x, position_y, position_z;
    SDL_Color color;
} House;

House* init_house(const char* obj_filepath, float scale, float pos_x, float pos_y, float pos_z, SDL_Color color);
void render_house(House* house, SDL_Renderer* renderer, float camera_x, float camera_y, float camera_z);
void free_house(House* house);
#endif