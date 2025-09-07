#include "./iso_camera.h"

// void tile_to_iso(float tx, float ty, int tile_w, int tile_h, float *out_x, float *out_y) {
//     *out_x = (tx - ty) * (tile_w * 0.5f);
//     *out_y = (tx + ty) * (tile_h * 0.5f);
// }

void tile_to_screen(int tile_x, int tile_y, IsoCamera* cam, int tile_width, int tile_height, int* screen_x, int* screen_y) {
    float half_w = tile_width / 2.0f;
    float half_h = tile_height / 2.0f;

    // cálculo isométrico
    float x = (tile_x - tile_y) * half_w;
    float y = (tile_x + tile_y) * half_h;

    // aplica posição da câmera
    x -= cam->x;
    y -= cam->y;

    // aplica zoom
    x *= cam->zoom;
    y *= cam->zoom;

    *screen_x = (int)x;
    *screen_y = (int)y;
}


// Converte coordenadas da tela para tile considerando câmera e zoom
void screen_to_tile(int sx, int sy, IsoCamera *cam,
                    int tile_w, int tile_h,
                    float *out_tx, float *out_ty) {
    // Remove zoom primeiro
    float dx = sx / cam->zoom;
    float dy = sy / cam->zoom;

    // Reposiciona com a câmera
    dx += cam->x;
    dy += cam->y;

    // Inversão da fórmula isométrica
    float A = (2.0f * dx) / tile_w;
    float B = (2.0f * dy) / tile_h;

    *out_tx = (A + B) * 0.5f;
    *out_ty = (B - A) * 0.5f;
}
