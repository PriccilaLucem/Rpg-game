#include <stdlib.h>
#include "./screen.h"

static void init_libs(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    if (TTF_Init() == -1) {
        SDL_Log("TTF initialization failed: %s", TTF_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
} 

static SDL_Window* init_window(void) {
    SDL_Window* window = SDL_CreateWindow("SDL2 Game",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        SCREEN_W, SCREEN_H,
                                        SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return window;
}

static SDL_Renderer* init_renderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
                                               SDL_RENDERER_ACCELERATED | 
                                               SDL_RENDERER_PRESENTVSYNC);
    
    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return renderer;
}

void cleanup(InitialScreen* screen) {
    if (screen) {
        if (screen->renderer) {
            SDL_DestroyRenderer(screen->renderer);
        }
        if (screen->window) {
            SDL_DestroyWindow(screen->window);
        }
        TTF_Quit();
        SDL_Quit();
        free(screen);
    }
}


InitialScreen* init_initial_screen() {
    InitialScreen* screen = malloc(sizeof(InitialScreen));
    if (!screen) {
        exit(EXIT_FAILURE);        
    }
    
    init_libs();
    screen->window = init_window();
    screen->renderer = init_renderer(screen->window);
    screen->clear = cleanup;
    
    return screen;
}

