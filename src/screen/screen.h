#ifndef INIT_LIBS_H
#define INIT_LIBS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../states/states.h"

void init_libs();
SDL_Window* init_window();
SDL_Renderer* init_renderer(SDL_Window* window);
void cleanup(SDL_Renderer* renderer, SDL_Window* window);

#endif