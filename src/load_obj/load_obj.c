#include "./load_obj.h"

static Vertex rotateVertex(Vertex v, float rx, float ry, float rz) {
    // Rotate around X axis
    float cos_x = cosf(rx), sin_x = sinf(rx);
    float y = v.y * cos_x - v.z * sin_x;
    float z = v.y * sin_x + v.z * cos_x;
    v.y = y; v.z = z;
    
    // Rotate around Y axis
    float cos_y = cosf(ry), sin_y = sinf(ry);
    float x = v.x * cos_y + v.z * sin_y;
    z = -v.x * sin_y + v.z * cos_y;
    v.x = x; v.z = z;
    
    // Rotate around Z axis
    float cos_z = cosf(rz), sin_z = sinf(rz);
    x = v.x * cos_z - v.y * sin_z;
    y = v.x * sin_z + v.y * cos_z;
    v.x = x; v.y = y;
    
    return v;
}

static Vertex translateVertex(Vertex v, float dx, float dy, float dz) {
    v.x += dx; v.y += dy; v.z += dz;
    return v;
}

static Vertex scaleVertex(Vertex v, float scale) {
    v.x *= scale; v.y *= scale; v.z *= scale;
    return v;
}

static Vertex toScreen(Vertex v) {
    // Simple perspective projection with safety checks
    float fov = 500.0f;
    if (v.z > 0.1f) {
        v.x = (v.x * fov) / v.z + 400; // Screen center X
        v.y = (v.y * fov) / v.z + 300; // Screen center Y
    } else {
        // Clamp vertices behind camera
        v.x = 400; v.y = 300;
    }
    
    // Clamp to reasonable screen bounds
    if (v.x < -1000) v.x = -1000;
    if (v.x > 2000) v.x = 2000;
    if (v.y < -1000) v.y = -1000;
    if (v.y > 2000) v.y = 2000;
    
    return v;
}

static void fillTriangle(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3) {
    // Sort vertices by y coordinate
    if (y1 > y2) { int tx = x1, ty = y1; x1 = x2; y1 = y2; x2 = tx; y2 = ty; }
    if (y2 > y3) { int tx = x2, ty = y2; x2 = x3; y2 = y3; x3 = tx; y3 = ty; }
    if (y1 > y2) { int tx = x1, ty = y1; x1 = x2; y1 = y2; x2 = tx; y2 = ty; }
    
    // Fill triangle using scanline algorithm
    for (int y = y1; y <= y3; y++) {
        int xa, xb;
        
        if (y < y2) {
            // Upper part
            if (y2 != y1) xa = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
            else xa = x1;
            if (y3 != y1) xb = x1 + (x3 - x1) * (y - y1) / (y3 - y1);
            else xb = x1;
        } else {
            // Lower part
            if (y3 != y2) xa = x2 + (x3 - x2) * (y - y2) / (y3 - y2);
            else xa = x2;
            if (y3 != y1) xb = x1 + (x3 - x1) * (y - y1) / (y3 - y1);
            else xb = x1;
        }
        
        if (xa > xb) { int temp = xa; xa = xb; xb = temp; }
        SDL_RenderDrawLine(renderer, xa, y, xb, y);
    }
}


OBJ_Model* OBJ_Load(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir arquivo: %s\n", filename);
        return NULL;
    }

    OBJ_Model* model = malloc(sizeof(OBJ_Model));
    if (!model) {
        fclose(file);
        return NULL;
    }

    model->vertices = NULL;
    model->faces = NULL;
    model->vertex_count = 0;
    model->face_count = 0;
    model->scale = 1.0f;
    model->rotation_x = model->rotation_y = model->rotation_z = 0.0f;
    model->position_x = model->position_y = model->position_z = 0.0f;
    model->color = (SDL_Color){255, 255, 255, 255};

    // Primeira passagem: contar vértices e faces
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n') continue;
        
        if (line[0] == 'v' && line[1] == ' ') {
            model->vertex_count++;
        } else if (line[0] == 'f' && line[1] == ' ') {
            model->face_count++;
        }
    }

    if (model->vertex_count == 0 || model->face_count == 0) {
        printf("Arquivo OBJ vazio ou formato inválido: %s\n", filename);
        free(model);
        fclose(file);
        return NULL;
    }

    model->vertices = malloc(model->vertex_count * sizeof(Vertex));
    model->faces = malloc(model->face_count * sizeof(Face));

    if (!model->vertices || !model->faces) {
        printf("Failed to allocate memory to model\n");
        if (model->vertices) free(model->vertices);
        if (model->faces) free(model->faces);
        free(model);
        fclose(file);
        return NULL;
    }

    rewind(file);

    int v_index = 0;
    int f_index = 0;

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n') continue;
        
        if (line[0] == 'v' && line[1] == ' ') {
            if (v_index < model->vertex_count) {
                if (sscanf(line, "v %f %f %f", 
                           &model->vertices[v_index].x,
                           &model->vertices[v_index].y,
                           &model->vertices[v_index].z) == 3) {
                    v_index++;
                }
            }
        } else if (line[0] == 'f' && line[1] == ' ') {
            if (f_index < model->face_count) {
                // Parse face line safely without strtok
                char face_line[256];
                strncpy(face_line, line + 2, sizeof(face_line) - 1);
                face_line[sizeof(face_line) - 1] = '\0';
                
                int vertex_indices[4] = {0};
                int vertex_count = 0;
                char* ptr = face_line;
                
                while (*ptr && vertex_count < 4) {
                    // Skip whitespace
                    while (*ptr == ' ' || *ptr == '\t') ptr++;
                    if (!*ptr) break;
                    
                    int v;
                    if (sscanf(ptr, "%d", &v) == 1) {
                        vertex_indices[vertex_count++] = v;
                    }
                    
                    // Move to next token
                    while (*ptr && *ptr != ' ' && *ptr != '\t' && *ptr != '\n') ptr++;
                }
                
                if (vertex_count >= 3) {
                    // Primeiro triângulo
                    model->faces[f_index].v1 = abs(vertex_indices[0]) - 1;
                    model->faces[f_index].v2 = abs(vertex_indices[1]) - 1;
                    model->faces[f_index].v3 = abs(vertex_indices[2]) - 1;
                    f_index++;
                    
                    if (vertex_count == 4 && f_index < model->face_count) {
                        model->faces[f_index].v1 = abs(vertex_indices[0]) - 1;
                        model->faces[f_index].v2 = abs(vertex_indices[2]) - 1;
                        model->faces[f_index].v3 = abs(vertex_indices[3]) - 1;
                        f_index++;
                    }
                }
            }
        }
    }

    fclose(file);
    return model;
}



void OBJ_Render(SDL_Renderer* renderer, OBJ_Model* model, float camera_x, float camera_y, float camera_z) {
    if (!model || !renderer || !model->vertices || model->vertex_count <= 0) return;
    
    for (int i = 0; i < model->face_count; i++) {
        Face face = model->faces[i];
        if (face.v1 >= model->vertex_count || face.v2 >= model->vertex_count || face.v3 >= model->vertex_count) continue;
        
        Vertex v1 = model->vertices[face.v1];
        Vertex v2 = model->vertices[face.v2];
        Vertex v3 = model->vertices[face.v3];

        // Apply transformations
        v1 = rotateVertex(v1, model->rotation_x, model->rotation_y, model->rotation_z);
        v2 = rotateVertex(v2, model->rotation_x, model->rotation_y, model->rotation_z);
        v3 = rotateVertex(v3, model->rotation_x, model->rotation_y, model->rotation_z);

        v1 = translateVertex(v1, model->position_x, model->position_y, model->position_z);
        v2 = translateVertex(v2, model->position_x, model->position_y, model->position_z);
        v3 = translateVertex(v3, model->position_x, model->position_y, model->position_z);

        v1 = scaleVertex(v1, model->scale);
        v2 = scaleVertex(v2, model->scale);
        v3 = scaleVertex(v3, model->scale);

        // Apply camera transformation
        v1 = translateVertex(v1, -camera_x, -camera_y, -camera_z);
        v2 = translateVertex(v2, -camera_x, -camera_y, -camera_z);
        v3 = translateVertex(v3, -camera_x, -camera_y, -camera_z);

        // Skip faces behind camera
        if (v1.z <= 0 && v2.z <= 0 && v3.z <= 0) continue;

        // Convert to screen coordinates
        v1 = toScreen(v1);
        v2 = toScreen(v2);
        v3 = toScreen(v3);

        // Simple lighting based on face orientation
        float light = 0.5f + 0.5f * ((v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x)) / 10000.0f;
        light = fmaxf(0.3f, fminf(1.0f, light));
        
        // Apply lighting to color
        Uint8 r = (Uint8)(model->color.r * light);
        Uint8 g = (Uint8)(model->color.g * light);
        Uint8 b = (Uint8)(model->color.b * light);
        
        // Fill triangle
        SDL_SetRenderDrawColor(renderer, r, g, b, model->color.a);
        fillTriangle(renderer, (int)v1.x, (int)v1.y, (int)v2.x, (int)v2.y, (int)v3.x, (int)v3.y);
        
        // Draw wireframe
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawLine(renderer, (int)v1.x, (int)v1.y, (int)v2.x, (int)v2.y);
        SDL_RenderDrawLine(renderer, (int)v2.x, (int)v2.y, (int)v3.x, (int)v3.y);
        SDL_RenderDrawLine(renderer, (int)v3.x, (int)v3.y, (int)v1.x, (int)v1.y);
    }
}

void OBJ_Rotate(OBJ_Model* model, float dx, float dy, float dz) {
    if (model) {
        model->rotation_x += dx;
        model->rotation_y += dy;
        model->rotation_z += dz;
    }
}

void OBJ_Translate(OBJ_Model* model, float dx, float dy, float dz) {
    if (model) {
        model->position_x += dx;
        model->position_y += dy;
        model->position_z += dz;
    }
}

void OBJ_Scale(OBJ_Model* model, float factor) {
    if (model) {
        model->scale *= factor;
    }
}

void OBJ_SetColor(OBJ_Model* model, SDL_Color color) {
    if (model) {
        model->color = color;
    }
}


void OBJ_Free(OBJ_Model* model) {
    if (model) {
        free(model->vertices);
        free(model->faces);
        free(model);
    }
}