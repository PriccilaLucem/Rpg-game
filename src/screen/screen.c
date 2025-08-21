#include <stdlib.h>
#include "./screen.h"

void init_libs(){
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        SDL_Log("TTF initialization failed: %s", TTF_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
} 

SDL_Window* init_window(){
    // Create window
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

SDL_Renderer* init_renderer(SDL_Window* window){
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return renderer;
}

void cleanup(SDL_Renderer* renderer, SDL_Window* window){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}