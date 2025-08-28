#include "states.h"
#include "../config/config.h"
#include "../ui/main_menu/main_menu.h"
#include "../ui/options/options.h"
#include "../input/input.h"
#include "../load_obj/load_obj.h"
#include <stdio.h>

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
            if (event->type == SDL_KEYDOWN) {
                input(event);
            }
            break;
        case STATE_EXIT:
            break;
    }
}

void update_state(Menu* main_menu, Options* options) {
    switch (current_state) {
        case STATE_MAIN_MENU:
            if (main_menu) update_main_menu(main_menu);
            break;
        case STATE_OPTIONS:
            if (options) update_options(options);
            break;
        case STATE_GAME:
            // Atualizações do jogo podem ser feitas aqui
            break;
        case STATE_EXIT:
            cleanup_states(main_menu, options);
            break;
    }
}

void render_state(SDL_Renderer* renderer, Menu* menu, Options* options) {
    // Limpar a tela
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
            int current_width, current_height;
            SDL_GetWindowSize(window, &current_width, &current_height);
            OBJ_Render(renderer, obj_model, current_width, current_height);
            break;
        case STATE_EXIT:
            break;
    }
}

void init_states(GameState initial_state) {
    current_state = initial_state;
    
}

void cleanup_states(Menu* main_menu, Options* options) {
    if (main_menu) {
        free_main_menu(main_menu);
    }
    if (options) {
        free_options(options);
    }
    if (obj_model) {
        OBJ_Free(obj_model);
        obj_model = NULL;
    }
}