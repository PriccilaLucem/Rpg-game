#include "./init_game.h"
#include "../../input/charater_input.h"
#include "../../camera/iso_camera.h"  // certifique-se de incluir o header da câmera

void render_initial_game(SDL_Renderer* renderer, MainCharater* main_charater, Floor* floor) {
    if (!floor) return;

    static IsoCamera cam;
    static int camera_initialized = 0;

    if (!camera_initialized) {
        IsoCamera_Init(&cam, 0, 200, -500); // câmera recuada e levemente acima
        camera_initialized = 1;
    }

    const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);

    // Movimento e rotação da câmera
    HandleCameraInput(&cam, keyboard_state);

    // Atualiza personagem (input e física)
    if (main_charater) {
        HandleCharacterInput(main_charater, keyboard_state);
        ApplyFloorPhysics(main_charater);

        // Gravidade simples
        main_charater->bc->velocity_y -= 0.8f;
        main_charater->bc->position_y += main_charater->bc->velocity_y;

        ApplyFloorPhysics(main_charater);
    }

    // Limpa tela
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // --- Renderização dos pisos (3x3) ---
    if (floor->obj) {
        floor->obj->scale = 200.0f;

        const float floor_size = 300.0f;
        const int grid_radius = 1; // desenha 3x3 (de -1 a 1)

        for (int gx = -grid_radius; gx <= grid_radius; gx++) {
            for (int gz = -grid_radius; gz <= grid_radius; gz++) {
                floor->obj->position_x = gx * floor_size;
                floor->obj->position_y = 0.0f;
                floor->obj->position_z = gz * floor_size;
                OBJ_Render_Isometric(renderer, floor->obj, &cam);
            }
        }
    }

    // --- Renderização da casa ---
    static House* game_house = NULL;
    if (!game_house) {
        game_house = init_house("assets/home/Untitled.obj", 150.0f, 0, 0, 50, (SDL_Color){120, 80, 40, 255});
    }

    if (game_house && game_house->model) {
        game_house->model->position_x = 0.0f;
        game_house->model->position_y = 0.0f;
        game_house->model->position_z = 0.0f;
        OBJ_Render_Isometric(renderer, game_house->model, &cam);
    }

    // --- Renderização do personagem ---
    if (main_charater && main_charater->bc->model) {
        main_charater->bc->model->scale = 200.0f;

        main_charater->bc->model->position_x = main_charater->bc->position_x;
        main_charater->bc->model->position_y = main_charater->bc->position_y;
        main_charater->bc->model->position_z = main_charater->bc->position_z;

        OBJ_Render_Isometric(renderer, main_charater->bc->model, &cam);
    }

    SDL_RenderPresent(renderer);
}
