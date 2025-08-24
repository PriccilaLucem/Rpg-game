#ifndef INIT_LIBS_H
#define INIT_LIBS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../constants/constants.h"

typedef struct InitialScreen
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;    

    void (*clear)(struct InitialScreen* screen);

} InitialScreen;

InitialScreen* init_initial_screen();

#endif