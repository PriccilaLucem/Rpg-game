#ifndef FLOOR_H
#define FLOOR_H

#include <SDL.h>
#include <stdlib.h>
#include "../../load_obj/load_obj.h"
#include "../iso_camera/iso_camera.h"
#include "../../load_obj/load_obj.h"


typedef struct {
    int width;    
    int height;   
    SDL_Texture*** tiles;
} Floor;

Floor* init_floor_with_white_tiles(SDL_Renderer* renderer, int width, int height, int tile_width, int tile_height);
void render_floor(SDL_Renderer *renderer, Floor* floor,  IsoCamera *cam, int map_w, int map_h, int tile_w, int tile_h);
#endif  