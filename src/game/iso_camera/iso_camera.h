#ifndef ISO_CAMERA_H
#define ISO_CAMERA_H

#include <SDL.h>
#include <math.h>
#include "../../load_obj/load_obj.h"

#define M_PI 3.14159265358979323846

// Estrutura para a câmera isométrica
typedef struct {
    float x, y, z;       // Posição da câmera
    float angle;         // Ângulo de rotação (0, 90, 180, 270 graus)
    float zoom;          // Nível de zoom
    float elevation;     // Altura/ângulo de elevação
} IsoCamera;

// Inicialização da câmera
void IsoCamera_Init(IsoCamera* cam, float x, float y, float z);

// Converte coordenadas 3D do mundo para coordenadas 2D de tela
void WorldToScreen(IsoCamera* cam, float wx, float wy, float wz, int* sx, int* sy, int screen_width, int screen_height);

// Função para renderizar objetos com a câmera isométrica
void OBJ_Render_Isometric(SDL_Renderer* renderer, OBJ_Model* model, IsoCamera* cam);

// Função para manipular a câmera (input do usuário)
void HandleCameraInput(IsoCamera* cam, const Uint8* keyboard_state);

#endif