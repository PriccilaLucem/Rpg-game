#include "./init_game.h"

void render_initial_game(SDL_Renderer* renderer, MainCharater* main_charater, Floor* floor){
    static IsoCamera cam = { .x = 400, .y = 200, .zoom = 1.0f };
    const int tile_width = 128;
    const int tile_height = 64;

    render_floor(renderer, floor , &cam, 0, 0, tile_width, tile_height);

    int sx, sy;
    tile_to_screen(main_charater->tile_x, main_charater->tile_y, &cam, tile_width, tile_height, &sx, &sy);

    main_charater->bc->model->position_x = sx;
    main_charater->bc->model->position_y = sy;

    OBJ_Render(renderer, main_charater->bc->model);
}
