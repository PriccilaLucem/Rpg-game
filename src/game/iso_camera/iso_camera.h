#ifndef ISO_CAMERA_H
#define ISO_CAMERA_H

#include <SDL.h>

typedef struct {
    float x, y;   // posição da câmera (em pixels)
    float zoom;   // fator de zoom
} IsoCamera;




void tile_to_screen(int tile_x, int tile_y, IsoCamera* cam, int tile_width, int tile_height, int* screen_x, int* screen_y);
void screen_to_tile(int sx, int sy, IsoCamera *cam, int tile_w, int tile_h, float *out_tx, float *out_ty);

#endif
