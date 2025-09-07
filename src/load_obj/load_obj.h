#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern SDL_Window* window;

typedef struct {
    float x, y, z;
} Vertex;

typedef struct {
    int v1, v2, v3;
    int vt1, vt2, vt3;
    int vn1, vn2, vn3;
} Face;

typedef struct OBJ_Model {
    Vertex* vertices;
    Face* faces;
    int vertex_count;
    int face_count;
    float scale;
    float rotation_x, rotation_y, rotation_z;
    float position_x, position_y, position_z;
    SDL_Color color;
} OBJ_Model;

OBJ_Model* OBJ_Load(const char* filename);
void OBJ_Free(OBJ_Model* model);
void OBJ_Render(SDL_Renderer* renderer, OBJ_Model* model);
void OBJ_Rotate(OBJ_Model* model, float dx, float dy, float dz);
void OBJ_Translate(OBJ_Model* model, float dx, float dy, float dz);
void OBJ_Scale(OBJ_Model* model, float factor);
void OBJ_SetColor(OBJ_Model* model, SDL_Color color);
SDL_Rect toRect(const OBJ_Model* model);
void OBJ_RenderAt(SDL_Renderer* renderer, OBJ_Model* model, int offset_x, int offset_y);

#endif