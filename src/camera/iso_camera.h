#ifndef ISO_CAMERA_H
#define ISO_CAMERA_H

#include <SDL.h>
#include <math.h>
#include "../load_obj/load_obj.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Estrutura para a câmera isométrica
typedef struct {
    float x, y, z;       // Posição da câmera
    float angle;         // Ângulo de rotação (0, 90, 180, 270 graus)
    float zoom;          // Nível de zoom
    float elevation;     // Altura/ângulo de elevação
} IsoCamera;

void IsoCamera_Init(IsoCamera* cam, float x, float y, float z);
void WorldToScreen(IsoCamera* cam, float world_x, float world_y, float world_z, int* sx, int* sy, int screen_width, int screen_height);
void OBJ_Render_Isometric(SDL_Renderer* renderer, OBJ_Model* model, IsoCamera* cam);
void HandleCameraInput(IsoCamera* cam, const Uint8* keyboard_state);
void FollowCharacter(IsoCamera* cam, float char_x, float char_y, float char_z);

#endif