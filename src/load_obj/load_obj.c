#include "load_obj.h"

static Vertex project_vertex(Vertex v, int screen_width, int screen_height, float fov_rad, float aspect_ratio);

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
                char* token = strtok(line + 2, " \t\n");
                int vertex_indices[4] = {0};
                int vertex_count = 0;
                
                while (token != NULL && vertex_count < 4) {
                    int v;
                    if (sscanf(token, "%d", &v) == 1) {
                        vertex_indices[vertex_count++] = v;
                    }
                    // Avançar para próximo token
                    char* slash = strchr(token, '/');
                    if (slash) *slash = '\0';
                    token = strtok(NULL, " \t\n");
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

void OBJ_Free(OBJ_Model* model) {
    if (model) {
        free(model->vertices);
        free(model->faces);
        free(model);
    }
}

void OBJ_Render(SDL_Renderer* renderer, OBJ_Model* model) {
    if (!model || !renderer) {
        printf("Erro: Modelo ou renderer nulo\n");
        return;
    }
    int screen_width, screen_height;
    SDL_GetWindowSize(window, &screen_width, &screen_height);
    SDL_SetRenderDrawColor(renderer, model->color.r, model->color.g, model->color.b, model->color.a);

    for (int i = 0; i < model->face_count; i++) {
        Face face = model->faces[i];
        
        // Verificar índices válidos
        if (face.v1 < 0 || face.v1 >= model->vertex_count ||
            face.v2 < 0 || face.v2 >= model->vertex_count ||
            face.v3 < 0 || face.v3 >= model->vertex_count) {
            continue;
        }
        
        Vertex v1 = model->vertices[face.v1];
        Vertex v2 = model->vertices[face.v2];
        Vertex v3 = model->vertices[face.v3];

        v1.x *= model->scale; v1.y *= model->scale; v1.z *= model->scale;
        v2.x *= model->scale; v2.y *= model->scale; v2.z *= model->scale;
        v3.x *= model->scale; v3.y *= model->scale; v3.z *= model->scale;

        v1.x += model->position_x; v1.y += model->position_y; v1.z += model->position_z;
        v2.x += model->position_x; v2.y += model->position_y; v2.z += model->position_z;
        v3.x += model->position_x; v3.y += model->position_y; v3.z += model->position_z;

        float z_near = 0.1f;
        float z_far = 100.0f;
        float fov = 60.0f;
        
        float aspect_ratio = (float)screen_width / (float)screen_height;
        float fov_rad = 1.0f / tanf(fov * 0.5f * 3.14159f / 180.0f);
        
                
        Vertex p1 = project_vertex(v1, screen_width, screen_height, fov_rad, aspect_ratio);
        Vertex p2 = project_vertex(v2, screen_width, screen_height, fov_rad, aspect_ratio);
        Vertex p3 = project_vertex(v3, screen_width, screen_height, fov_rad, aspect_ratio);

        if (p1.z > -4.9f && p2.z > -4.9f && p3.z > -4.9f) {
            SDL_RenderDrawLine(renderer, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
            SDL_RenderDrawLine(renderer, (int)p2.x, (int)p2.y, (int)p3.x, (int)p3.y);
            SDL_RenderDrawLine(renderer, (int)p3.x, (int)p3.y, (int)p1.x, (int)p1.y);
        }
    }
}
static Vertex project_vertex(Vertex v, int screen_width, int screen_height, float fov_rad, float aspect_ratio) {
    Vertex result;
    result.z = v.z;

    float z = v.z + 5.0f;
    if (z > 0.1f) {
        result.x = (v.x * fov_rad / aspect_ratio) / z;
        result.y = (v.y * fov_rad) / z;

        result.x = (result.x + 1.0f) * 0.5f * screen_width;
        result.y = (1.0f - result.y) * 0.5f * screen_height;
    }
    return result;
}

void OBJ_RenderAt(SDL_Renderer* renderer, OBJ_Model* model, int offset_x, int offset_y) {
    if (!model || !renderer) return;

    int screen_width, screen_height;
    SDL_GetWindowSize(window, &screen_width, &screen_height);

    SDL_SetRenderDrawColor(renderer,
                           model->color.r, model->color.g,
                           model->color.b, model->color.a);

    float aspect_ratio = (float)screen_width / (float)screen_height;
    float fov = 60.0f;
    float fov_rad = 1.0f / tanf(fov * 0.5f * 3.14159f / 180.0f);

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

        for (int j = 0; j < 3; j++) {
            // Aplica escala
            v[j].x *= model->scale;
            v[j].y *= model->scale;
            v[j].z *= model->scale;

            // Aplica posição original + offset do tile
            v[j].x += model->position_x + offset_x;
            v[j].y += model->position_y + offset_y;
            v[j].z += model->position_z;
        }

        // Projeção simples perspectiva
        Vertex p[3];
        for (int j = 0; j < 3; j++) {
            float z = v[j].z + 5.0f;
            p[j].z = v[j].z;

            if (z > 0.1f) {
                p[j].x = (v[j].x * fov_rad / aspect_ratio) / z;
                p[j].y = (v[j].y * fov_rad) / z;

                p[j].x = (p[j].x + 1.0f) * 0.5f * screen_width;
                p[j].y = (1.0f - p[j].y) * 0.5f * screen_height;
            }
        }

        // Desenha linhas se estiverem visíveis
        if (p[0].z > -4.9f && p[1].z > -4.9f && p[2].z > -4.9f) {
            SDL_RenderDrawLine(renderer, (int)p[0].x, (int)p[0].y, (int)p[1].x, (int)p[1].y);
            SDL_RenderDrawLine(renderer, (int)p[1].x, (int)p[1].y, (int)p[2].x, (int)p[2].y);
            SDL_RenderDrawLine(renderer, (int)p[2].x, (int)p[2].y, (int)p[0].x, (int)p[0].y);
        }
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
SDL_Rect toRect(const OBJ_Model* model){
    SDL_Rect rect;
    int screen_width, screen_height;
    SDL_GetWindowSize(window, &screen_width, &screen_height);

    rect.x = (int)(model->position_x - model->scale/2);
    rect.y = (int)(model->position_y - model->scale/2);
    rect.w = (int) model->scale;
    rect.h = (int) model->scale;
    rect.x += screen_width/2;
    rect.y += screen_height/2;

}