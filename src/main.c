#include "states/states.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "./ui/main_menu/main_menu.h"
#include "./ui/options/options.h"
#include "./config/config.h"
#include "./screen/screen.h"

GameState current_state = STATE_MAIN_MENU;
Config* current_config = NULL;
Options* options = NULL;
Menu* main_menu = NULL;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
#if defined(_WIN32)

#include <windows.h>
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    (void)hInst; (void)hInstPrev; (void)cmdline; (void)cmdshow;
#else
int main(int argc, char* argv[]) {
    (void)argc; (void)argv;
#endif

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    
    InitialScreen* screen = init_initial_screen();   
    if(!screen){
        fprintf(stderr, "Failed to initialize screen\n");
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    
    renderer = screen->renderer;
    window = screen->window;
    main_menu = init_menu(screen->screen_width, screen->screen_height,  24);
    options = init_options(screen->screen_width, screen->screen_height, screen->renderer, 24);
    if (!main_menu || !options) {
        fprintf(stderr, "Failed to initialize main menu or options\n");
        screen->clear(screen);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Inicializar estados
    init_states(STATE_MAIN_MENU);
    int running = 1;
    while (running && current_state != STATE_EXIT) {
        while (SDL_PollEvent(&screen->event)) {
            if (screen->event.type == SDL_QUIT) {
                running = 0;
            }
            handle_state_input(&screen->event);
        }

        // Clear screen
        SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 255);
        SDL_RenderClear(screen->renderer);

        // Render do estado atual
        render_state(screen->renderer, main_menu, options);

        // Update screen
        SDL_RenderPresent(screen->renderer);

        // Cap frame rate
        SDL_Delay(16);
    }

    // Cleanup
    cleanup_states(main_menu, NULL);
    screen->clear(screen);
    TTF_Quit();
    SDL_Quit();

    return 0;
}