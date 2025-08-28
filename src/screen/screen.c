#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "./screen.h"
#include "../config/config.h"

static void init_libs(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        printf("SDL initialization failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    if (TTF_Init() == -1) {
        SDL_Log("TTF initialization failed: %s", TTF_GetError());
        SDL_Quit();
        printf("TTF initialization failed: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
} 

static SDL_Window* init_window(int SCREEN_W, int SCREEN_H, bool fullscreen) {
    SDL_Window* window = SDL_CreateWindow("SDL2 Game",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        SCREEN_W, SCREEN_H,
                                        fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        printf("Window creation failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}

static SDL_Renderer* init_renderer(SDL_Window* window, bool vsync) {
    if (!window) {
        SDL_Log("Error: Cannot create renderer for NULL window");
        return NULL;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
                                               vsync ? SDL_RENDERER_PRESENTVSYNC : SDL_RENDERER_ACCELERATED );
    
    // Fallback to software renderer if hardware acceleration fails
    if (!renderer) {
        SDL_Log("Hardware accelerated renderer failed: %s", SDL_GetError());
        SDL_Log("Attempting software renderer...");
        
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        
        if (!renderer) {
            SDL_Log("Software renderer also failed: %s", SDL_GetError());
            return NULL;
        }
        
        SDL_Log("Using software renderer as fallback");
    } else {
        SDL_Log("Hardware accelerated renderer created successfully");
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    SDL_RendererInfo renderer_info;
    if (SDL_GetRendererInfo(renderer, &renderer_info) == 0) {
        SDL_Log("Renderer: %s", renderer_info.name);
        SDL_Log("Renderer flags: %s%s%s%s",
               (renderer_info.flags & SDL_RENDERER_SOFTWARE) ? "SOFTWARE " : "",
               (renderer_info.flags & SDL_RENDERER_ACCELERATED) ? "ACCELERATED " : "",
               (renderer_info.flags & SDL_RENDERER_PRESENTVSYNC) ? "VSYNC " : "",
               (renderer_info.flags & SDL_RENDERER_TARGETTEXTURE) ? "TARGET_TEXTURE " : "");
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
        printf("Failed to initialize screen!");
        exit(EXIT_FAILURE);        
    }
    Config* config = load_config();
    if(!config){
        free(screen);
        printf("Failed to initialize config!");
        exit(EXIT_FAILURE);
    }
    printf("%d", config->screen_width);
    init_libs();
    screen->screen_width = config->screen_width;
    screen->screen_height = config->screen_height;
    screen->window = init_window(screen->screen_width, screen->screen_height, config->fullscreen);
    screen->renderer = init_renderer(screen->window, config->vsync);
    screen->clear = cleanup;
    
    return screen;
}

