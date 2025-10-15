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
    float x, y, z;      // Posição da câmera no mundo
    float zoom;         // Zoom da câmera
    float rotation;     // Rotação horizontal (em radianos)
    float tilt;         // Inclinação vertical (em radianos)
} IsoCamera;

// Inicialização da câmera
void IsoCamera_Init(IsoCamera* cam, float x, float y, float z);

// Converte coordenadas do mundo para a tela (isometria)
void IsoCamera_Init(IsoCamera* cam, float x, float y, float z);

// Renderiza um modelo 3D em isometria
void OBJ_Render_Isometric(SDL_Renderer* renderer, OBJ_Model* model, IsoCamera* cam);

// Processa input de movimento e rotação da câmera
void HandleCameraInput(IsoCamera* cam, const Uint8* keyboard_state);

#endif