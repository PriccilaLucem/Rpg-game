#include "iso_camera.h"

// Inicialização da câmera
void IsoCamera_Init(IsoCamera* cam, float x, float y, float z) {
    cam->x = x;
    cam->y = y;
    cam->z = z;
    cam->angle = 45.0f;  // Ângulo inicial de 45 graus
    cam->zoom = 1.0f;
    cam->elevation = 30.0f;  // Ângulo de elevação de 30 graus
}

// Converte coordenadas 3D do mundo para coordenadas 2D de tela (projeção isométrica)
void WorldToScreen(IsoCamera* cam, float wx, float wy, float wz, int* sx, int* sy, int screen_width, int screen_height) {
    // Ângulos em radianos
    float angle_rad = cam->angle * M_PI / 180.0f;
    float elevation_rad = cam->elevation * M_PI / 180.0f;
    
    // Aplica rotação ao redor do eixo Y
    float rx = wx * cosf(angle_rad) - wz * sinf(angle_rad);
    float rz = wx * sinf(angle_rad) + wz * cosf(angle_rad);
    
    // Aplica projeção isométrica com elevação
    float iso_x = (rx - rz) * cosf(elevation_rad);
    float iso_y = wy + (rx + rz) * sinf(elevation_rad);
    
    // Aplica zoom e centraliza na tela
    *sx = (int)((iso_x * cam->zoom) + (screen_width / 2) + cam->x);
    *sy = (int)((iso_y * cam->zoom) + (screen_height / 2) + cam->y);
}

// Função para renderizar objetos com a câmera isométrica
void OBJ_Render_Isometric(SDL_Renderer* renderer, OBJ_Model* model, IsoCamera* cam) {
    if (!model || !renderer || !cam) return;

    int screen_width, screen_height;
    SDL_GetWindowSize(SDL_RenderGetWindow(renderer), &screen_width, &screen_height);

    // Cor branca para debug
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < model->face_count; i++) {
        Face face = model->faces[i];

        if (face.v1 < 0 || face.v1 >= model->vertex_count ||
            face.v2 < 0 || face.v2 >= model->vertex_count ||
            face.v3 < 0 || face.v3 >= model->vertex_count) {
            continue;
        }

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
        for (int j = 0; j < 3; j++) {
            WorldToScreen(cam, v[j].x, v[j].y, v[j].z, &sx[j], &sy[j], screen_width, screen_height);
        }

        // Desenha arestas
        SDL_RenderDrawLine(renderer, sx[0], sy[0], sx[1], sy[1]);
        SDL_RenderDrawLine(renderer, sx[1], sy[1], sx[2], sy[2]);
        SDL_RenderDrawLine(renderer, sx[2], sy[2], sx[0], sy[0]);
    }
}

// Função para manipular a câmera (input do usuário)
void HandleCameraInput(IsoCamera* cam, const Uint8* keyboard_state) {
    // Movimento da câmera com teclas WASD
    float move_speed = 10.0f;
    float angle_rad = cam->angle * M_PI / 180.0f;
    
    if (keyboard_state[SDL_SCANCODE_W]) {
        cam->x -= sinf(angle_rad) * move_speed;
        cam->z -= cosf(angle_rad) * move_speed;
    }
    if (keyboard_state[SDL_SCANCODE_S]) {
        cam->x += sinf(angle_rad) * move_speed;
        cam->z += cosf(angle_rad) * move_speed;
    }
    if (keyboard_state[SDL_SCANCODE_A]) {
        cam->x -= cosf(angle_rad) * move_speed;
        cam->z += sinf(angle_rad) * move_speed;
    }
    if (keyboard_state[SDL_SCANCODE_D]) {
        cam->x += cosf(angle_rad) * move_speed;
        cam->z -= sinf(angle_rad) * move_speed;
    }
    
    // Zoom com teclas Q e E
    if (keyboard_state[SDL_SCANCODE_Q]) {
        cam->zoom *= 1.05f;
        if (cam->zoom > 3.0f) cam->zoom = 3.0f;
    }
    if (keyboard_state[SDL_SCANCODE_E]) {
        cam->zoom *= 0.95f;
        if (cam->zoom < 0.5f) cam->zoom = 0.5f;
    }
    
    // Rotação da câmera com teclas R e F
    if (keyboard_state[SDL_SCANCODE_R]) {
        cam->angle += 2.0f;
        if (cam->angle >= 360.0f) cam->angle -= 360.0f;
    }
    if (keyboard_state[SDL_SCANCODE_F]) {
        cam->angle -= 2.0f;
        if (cam->angle < 0.0f) cam->angle += 360.0f;
    }
}