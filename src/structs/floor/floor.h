#ifndef FLOOR_H
#define FLOOR_H

#include <SDL.h>
#include <stdlib.h>
#include "../../load_obj/load_obj.h"
#include "../../camera/iso_camera.h"
#include "../../load_obj/load_obj.h"


typedef struct {
    int width;    
    int height;   
    SDL_Texture*** tiles;
    OBJ_Model* obj;
} Floor;

Floor* init_floor_from_obj(SDL_Renderer* renderer, const char* path, int tile_width, int tile_height);
void render_floor(SDL_Renderer *renderer, Floor* floor,  IsoCamera *cam, int map_w, int map_h, int tile_w, int tile_h);
void free_floor(Floor* floor);

#endif  