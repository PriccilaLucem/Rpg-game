// states.h
#ifndef STATES_H
#define STATES_H

#include <SDL.h>
#include "../constants/constants.h"

typedef struct Menu Menu;
typedef struct Options Options;
typedef struct OBJ_Model OBJ_Model;
typedef struct Game Game;
typedef struct InitialScreen InitialScreen;

extern Menu* main_menu;
extern GameState current_state;
extern Options* options;
extern SDL_Window* window;
extern OBJ_Model* obj_model;
extern Game* game;
extern InitialScreen* screen;

int get_id_gen();
void change_state(GameState new_state);
void handle_state_input(SDL_Event* event);
void update_state(Menu* main_menu, Options* options, Game* game);
void render_state(SDL_Renderer* renderer, Menu* main_menu, Options* options, Game* game);
void init_states(GameState initial_state);
void cleanup_states(Menu* main_menu, Options* options, Game* game);
void cleanup_current_state();
void load_state_resources(GameState new_state);

#endif