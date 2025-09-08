#include "./init_game.h"

void render_initial_game(SDL_Renderer* renderer, MainCharater* main_charater, Floor* floor) {
    if (!floor) return;

    static IsoCamera cam;
    static int camera_initialized = 0;
    
    if (!camera_initialized) {
        IsoCamera_Init(&cam, 0, 0, 0);
        camera_initialized = 1;
    }
    
    const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
    HandleCameraInput(&cam, keyboard_state);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (floor->obj) {
        floor->obj->scale = 200;
        floor->obj->position_x = 0;
        floor->obj->position_y = 0;
        floor->obj->position_z = 0;
        OBJ_Render_Isometric(renderer, floor->obj, &cam);
    }

    if (main_charater && main_charater->bc && main_charater->bc->model) {
        OBJ_Render_Isometric(renderer, main_charater->bc->model, &cam);
    }
    
    SDL_RenderPresent(renderer);
}