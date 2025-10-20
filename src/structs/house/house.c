#include "./house.h"
#include <stdlib.h>
#include <stdio.h>

House* init_house(const char* obj_filepath, float scale, float pos_x, float pos_y, float pos_z, SDL_Color color) {
    House* house = malloc(sizeof(House));
    if (!house) {
        return NULL;
    }
    
    house->model = OBJ_Load(obj_filepath);
    if (!house->model) {
        free(house);
        return NULL;
    }
    
    house->scale = scale;
    house->position_x = pos_x;
    house->position_y = pos_y;
    house->position_z = pos_z;
    house->color = color;
    
    OBJ_Scale(house->model, scale);
    OBJ_Translate(house->model, pos_x, pos_y, pos_z);
    OBJ_SetColor(house->model, color);
    
    return house;
}

void render_house(House* house, SDL_Renderer* renderer, float camera_x, float camera_y, float camera_z) {
    if (!house || !house->model) return;
    OBJ_Render(renderer, house->model, camera_x, camera_y, camera_z);
}

void free_house(House* house) {
    if (house) {
        if (house->model) {
            OBJ_Free(house->model);
        }
        free(house);
    }
}