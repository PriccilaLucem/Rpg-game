#include "states.h"
#include "../config/config.h"
#include "../ui/main_menu/main_menu.h"
#include "../ui/options/options.h"
#include "../game/game.h"

int id_generator = 0;



int get_id_gen() {
    return id_generator++;
}

void change_state(GameState new_state) {
    printf("Changing state from %d to %d\n", current_state, new_state);
    current_state = new_state;
}

void handle_state_input(SDL_Event* event) {
    switch (current_state) {
        case STATE_MAIN_MENU:
            if (main_menu) handle_menu_input(main_menu, event);
            break;
        case STATE_OPTIONS:
            if (options) handle_options_input(event, options);
            break;
        case STATE_GAME:
            if (game) handle_game_events(game, event);
            break;
        case STATE_EXIT:
            break;
    }
}

void update_state(Menu* main_menu, Options* options, Game* game) {
    switch (current_state) {
        case STATE_OPTIONS:
            if (options) update_options(options);
            break;
        case STATE_EXIT:
            cleanup_states(main_menu, options, game);
            break;
    }
}

void render_state(SDL_Renderer* renderer, Menu* menu, Options* options, Game* game) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    switch (current_state) {
        case STATE_MAIN_MENU:
            if (menu) render_menu(menu, renderer);
            break;
        case STATE_OPTIONS:
            if (options) render_options(options, renderer);
            break;
        case STATE_GAME:
            if(game) render_game(game, renderer);
            break;
        case STATE_EXIT:
            break;
    }
}

void init_states(GameState initial_state) {
    current_state = initial_state;
    
}

void cleanup_states(Menu* main_menu, Options* options, Game* game) {
    if (main_menu) {
        free_main_menu(main_menu);
    }
    if (options) {
        free_options(options);
    }
    if(game){
        free_game(game);
    }
}