#include "./init_game.h"
#include "../../input/charater_input.h"

void render_initial_game(SDL_Renderer* renderer, MainCharater* main_charater, Floor* floor) {
    if (!floor) return;

    static IsoCamera cam;
    static int camera_initialized = 0;
    
    if (!camera_initialized) {
        IsoCamera_Init(&cam, 0, 0, 0);
        camera_initialized = 1;
    }
    
    const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
    
    // Processar input e física
    HandleCameraInput(&cam, keyboard_state);
    
    if (main_charater) {
        HandleCharacterInput(main_charater, keyboard_state);
        ApplyFloorPhysics(main_charater);
        main_charater->bc->velocity_y -= 0.8f; // Gravidade
        main_charater->bc->position_y += main_charater->bc->velocity_y;
        
        ApplyFloorPhysics(main_charater);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Renderizar os chãos
    if (floor->obj) {
        // Floor principal
        floor->obj->scale = 200;
        floor->obj->position_x = 0;
        floor->obj->position_y = 0;
        floor->obj->position_z = 0;
        OBJ_Render_Isometric(renderer, floor->obj, &cam);
        
        // Floor 2
        floor->obj->position_x = 400;
        floor->obj->position_y = 0;
        OBJ_Render_Isometric(renderer, floor->obj, &cam);
        
        // Floor 3
        floor->obj->position_x = 0;
        floor->obj->position_y = 400;
        OBJ_Render_Isometric(renderer, floor->obj, &cam);
    }
    
    // Renderizar a casa
    static House* game_house = NULL;
    if (!game_house) {
        game_house = init_house("assets/home/Untitled.obj", 200.0f, 200, 200, 0, (SDL_Color){120, 80, 40, 255});
    }
    if (game_house && game_house->model) {
        OBJ_Render_Isometric(renderer, game_house->model, &cam);
    }
    
    // Renderizar o personagem
    if (main_charater && main_charater->bc->model) {
        main_charater->bc->model->scale = 200;
        
        // Usar a posição atual do personagem (a física já garante que está acima do chão)
        main_charater->bc->model->position_x = main_charater->bc->position_x;
        main_charater->bc->model->position_y = main_charater->bc->position_y;
        main_charater->bc->model->position_z = main_charater->bc->position_z;
        
        OBJ_Render_Isometric(renderer, main_charater->bc->model, &cam);
    }
    
    SDL_RenderPresent(renderer);
}