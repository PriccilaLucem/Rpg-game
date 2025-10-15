#include "iso_camera.h"
#include <math.h>
#include <SDL2/SDL.h>

// Inicializa a câmera
void IsoCamera_Init(IsoCamera* cam, float x, float y, float z) {
    cam->x = x;
    cam->y = y;
    cam->z = z;
    cam->zoom = 1.0f;
    cam->rotation = 45.0f * (M_PI / 180.0f); // 45 graus em radianos
    cam->tilt = 35.264f * (M_PI / 180.0f);   // ângulo clássico de isometria
}

// Converte coordenadas 3D -> 2D com projeção isométrica
SDL_Point WorldToScreen(float world_x, float world_y, float world_z, IsoCamera* cam) {
    // --- Translação pela câmera ---
    float dx = world_x - cam->x;
    float dy = world_y - cam->y;
    float dz = world_z - cam->z;

    // --- Rotação horizontal (em torno do eixo Y) ---
    float cosR = cosf(cam->rotation);
    float sinR = sinf(cam->rotation);

    float rx = dx * cosR - dz * sinR;
    float rz = dx * sinR + dz * cosR;

    // --- Projeção isométrica clássica ---
    // usa ângulo de 35.264° (tilt padrão), mas de forma estável
    float cosT = cosf(cam->tilt);
    float sinT = sinf(cam->tilt);

    float iso_x = (rx - rz) * cosT * cam->zoom;
    float iso_y = (rx + rz) * sinT - dy * cam->zoom;

    // --- Centraliza na tela (ajuste conforme resolução) ---
    SDL_Point screen;
    screen.x = (int)(iso_x + 640);  // metade da largura
    screen.y = (int)(iso_y + 360);  // metade da altura
    return screen;
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
        SDL_Point p1 = WorldToScreen(v[0].x, v[0].y, v[0].z, cam);
        SDL_Point p2 = WorldToScreen(v[1].x, v[1].y, v[1].z, cam);
        SDL_Point p3 = WorldToScreen(v[2].x, v[2].y, v[2].z, cam);


        // Desenha arestas
        SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
        SDL_RenderDrawLine(renderer, p2.x, p2.y, p3.x, p3.y);
        SDL_RenderDrawLine(renderer, p3.x, p3.y, p1.x, p1.y);
    }
}

// Controle da câmera via teclado
void HandleCameraInput(IsoCamera* cam, const Uint8* keyboard_state) {
    float move_speed = 10.0f;
    float angle_rad = cam->rotation; // usa o mesmo ângulo da projeção

    if (keyboard_state[SDL_SCANCODE_W]) {
        cam->x += cosf(angle_rad) * move_speed;
        cam->z += sinf(angle_rad) * move_speed;
    }
    if (keyboard_state[SDL_SCANCODE_S]) {
        cam->x -= cosf(angle_rad) * move_speed;
        cam->z -= sinf(angle_rad) * move_speed;
    }
    if (keyboard_state[SDL_SCANCODE_A]) {
        cam->x += sinf(angle_rad) * move_speed;
        cam->z -= cosf(angle_rad) * move_speed;
    }
    if (keyboard_state[SDL_SCANCODE_D]) {
        cam->x -= sinf(angle_rad) * move_speed;
        cam->z += cosf(angle_rad) * move_speed;
    }

    if (keyboard_state[SDL_SCANCODE_Q]) cam->zoom *= 1.05f;
    if (keyboard_state[SDL_SCANCODE_E]) cam->zoom *= 0.95f;

    if (keyboard_state[SDL_SCANCODE_R]) cam->rotation += 0.05f;
    if (keyboard_state[SDL_SCANCODE_F]) cam->rotation -= 0.05f;
}
