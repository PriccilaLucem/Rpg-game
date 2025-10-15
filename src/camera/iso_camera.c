#include "iso_camera.h"
#include <math.h>
#include <SDL2/SDL.h>

// Inicializa a câmera
void IsoCamera_Init(IsoCamera* cam, float x, float y, float z) {
    cam->x = x;
    cam->y = y;
    cam->z = z;
    cam->zoom = 1.0f;
    cam->angle = 45.0f;
    cam->elevation = 30.0f;
}

// Converte coordenadas 3D -> 2D com projeção isométrica
void WorldToScreen(IsoCamera* cam, float world_x, float world_y, float world_z, int* sx, int* sy, int screen_width, int screen_height) {
    // --- Translação pela câmera ---
    float dx = world_x - cam->x;
    float dy = world_y - cam->y;
    float dz = world_z - cam->z;

    // --- Rotação horizontal (em torno do eixo Y) ---
    float angle_rad = cam->angle * M_PI / 180.0f;
    float cosR = cosf(angle_rad);
    float sinR = sinf(angle_rad);

    float rx = dx * cosR - dz * sinR;
    float rz = dx * sinR + dz * cosR;

    // --- Projeção isométrica clássica ---
    float elevation_rad = cam->elevation * M_PI / 180.0f;
    float cosT = cosf(elevation_rad);
    float sinT = sinf(elevation_rad);

    float iso_x = (rx - rz) * cosT * cam->zoom;
    float iso_y = ((rx + rz) * sinT - dy) * cam->zoom;

    // --- Centraliza na tela ---
    *sx = (int)(iso_x + screen_width / 2);
    *sy = (int)(iso_y + screen_height / 2);
}


// Renderiza modelo em projeção isométrica
void OBJ_Render_Isometric(SDL_Renderer* renderer, OBJ_Model* model, IsoCamera* cam) {
    if (!model || !renderer || !cam) return;

    int screen_width, screen_height;
    SDL_GetWindowSize(SDL_RenderGetWindow(renderer), &screen_width, &screen_height);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < model->face_count; i++) {
        Face face = model->faces[i];

        if (face.v1 < 0 || face.v1 >= model->vertex_count ||
            face.v2 < 0 || face.v2 >= model->vertex_count ||
            face.v3 < 0 || face.v3 >= model->vertex_count)
            continue;

        Vertex v[3];
        v[0] = model->vertices[face.v1];
        v[1] = model->vertices[face.v2];
        v[2] = model->vertices[face.v3];

        // Aplica escala e posição do modelo
        for (int j = 0; j < 3; j++) {
            v[j].x = v[j].x * model->scale + model->position_x;
            v[j].y = v[j].y * model->scale + model->position_y;
            v[j].z = v[j].z * model->scale + model->position_z;
        }

        // Converte para coordenadas de tela usando a câmera isométrica
        int sx[3], sy[3];
        WorldToScreen(cam, v[0].x, v[0].y, v[0].z, &sx[0], &sy[0], screen_width, screen_height);
        WorldToScreen(cam, v[1].x, v[1].y, v[1].z, &sx[1], &sy[1], screen_width, screen_height);
        WorldToScreen(cam, v[2].x, v[2].y, v[2].z, &sx[2], &sy[2], screen_width, screen_height);

        // Desenha arestas
        SDL_RenderDrawLine(renderer, sx[0], sy[0], sx[1], sy[1]);
        SDL_RenderDrawLine(renderer, sx[1], sy[1], sx[2], sy[2]);
        SDL_RenderDrawLine(renderer, sx[2], sy[2], sx[0], sy[0]);
    }
}

// Controle da câmera via teclado (apenas rotação)
void HandleCameraInput(IsoCamera* cam, const Uint8* keyboard_state) {
    if (keyboard_state[SDL_SCANCODE_Q]) cam->angle += 2.0f;
    if (keyboard_state[SDL_SCANCODE_E]) cam->angle -= 2.0f;
    
    if (keyboard_state[SDL_SCANCODE_R]) cam->zoom *= 1.05f;
    if (keyboard_state[SDL_SCANCODE_F]) cam->zoom *= 0.95f;
}

// Função para câmera seguir personagem
void FollowCharacter(IsoCamera* cam, float char_x, float char_y, float char_z) {
    cam->x = char_x;
    cam->y = char_y;
    cam->z = char_z;
}
