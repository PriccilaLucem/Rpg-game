#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <stdbool.h>

typedef struct  OBJ_Model OBJ_Model;

extern OBJ_Model* obj_model;

void input(SDL_Event* event);

#endif 