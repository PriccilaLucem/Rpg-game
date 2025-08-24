// states.c
#include "states.h"
#include "../config/config.h"
#include "../ui/main_menu/main_menu.h"
#include "../ui/options/options.h"
#include <stdio.h>

int  id_generator = 0;

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
            if(options) handle_options_input(event, options);
        break;
        case STATE_GAME:
            // Handle game input
            // break;
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
            if(options) update_options(options);
        case STATE_EXIT:
            cleanup_states(main_menu, options);
            break;
    }
}

void render_state(SDL_Renderer* renderer, Menu* main_menu, Options* options) {
    switch (current_state) {
        case STATE_MAIN_MENU:
        
            if (main_menu) render_menu(main_menu, renderer);
            break;

        case STATE_OPTIONS:
            int current_width, current_height;
            SDL_GetWindowSize(window, &current_width, &current_height);
            if(options) render_options(options, renderer, current_width);
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
    if (options){
        free_options(options);
    }
}

