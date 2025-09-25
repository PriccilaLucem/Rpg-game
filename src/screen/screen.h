#ifndef INIT_LIBS_H
#define INIT_LIBS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../constants/constants.h"

typedef struct Options Options;
typedef struct Menu Menu;

extern Options* options;
extern Menu* main_menu;


typedef struct InitialScreen
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event; 
    int screen_width;   
    int screen_height;
    void (*clear)(struct InitialScreen* screen);
} InitialScreen;

InitialScreen* init_initial_screen();
void apply_resolution_change(InitialScreen* screen, int new_width, int new_height);
void toggle_fullscreen(SDL_Window* window, bool* fullscreen);

#endif