// states.h
#ifndef STATES_H
#define STATES_H

#include <SDL.h>
#include "../constants/constants.h"


typedef struct Menu Menu;

extern Menu* main_menu;
extern GameState current_state;


int get_id_gen();
void change_state(GameState new_state);
void handle_state_input(SDL_Event* event);
void update_state(Menu* main_menu);
void render_state(SDL_Renderer* renderer, Menu* main_menu);
void init_states(GameState initial_state);
void cleanup_states(Menu* main_menu);
void change_state(GameState new_state);

#endif