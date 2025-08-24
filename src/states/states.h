// states.h
#ifndef STATES_H
#define STATES_H

#include <SDL.h>
#include "../constants/constants.h"


typedef struct Menu Menu;
typedef struct Options Options;

extern Menu* main_menu;
extern GameState current_state;
extern Options* options;

int get_id_gen();
void change_state(GameState new_state);
void handle_state_input(SDL_Event* event);
void update_state(Menu* main_menu, Options* options);
void render_state(SDL_Renderer* renderer, Menu* main_menu, Options* options);
void init_states(GameState initial_state);
void cleanup_states(Menu* main_menu, Options* options);
void change_state(GameState new_state);

#endif