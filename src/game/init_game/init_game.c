#include "./init_game.h"


static Floor* initial_floor_of_main_screen(){

    Floor* floor = init_floor("src/assets/floor/floor.obj");
    return floor;
}

void render_init_game(SDL_Renderer* renderer){
    
    BasicCharacter* mc = init_basic_character_as_main("Hero", "The main character", "src/assets/player_assets/cube.obj");
    Floor* floor = initial_floor_of_main_screen();

    if (mc && mc->model) {
        OBJ_Render(renderer, mc->model);
    }
    
    if (floor && floor->model) {
        OBJ_Render(renderer, floor->model);
    }


}

