
#include <SDL_ttf.h>
#include <windows.h>
#include <SDL.h>

#include "./screen/screen.h"
#include "./states/states.h"
#include "./constants/constants.h"
#include "./ui/main_menu/main_menu.h"
#include "./config/config.h"

SDL_Window* window = NULL;
GameState current_state = STATE_MAIN_MENU;
Config* current_config = NULL;

Menu* main_menu = NULL;


int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    (void)hInst; (void)hInstPrev; (void)cmdline; (void)cmdshow;
    
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    
    // Criar janela (usando sua estrutura screen ou criando diretamente)
    InitialScreen* screen = init_initial_screen();   
    if(!screen){
        fprintf(stderr, "Failed to initialize screen\n");
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    
    // Configurar a janela global
    window = screen->window;
    main_menu = init_menu(SCREEN_W, SCREEN_H,  24);
    // Carregar fonte
    TTF_Font* font = TTF_OpenFont(MENU_FONT_PATH, 24);
    if (!font) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        // Tentar fallback para fonte padrão
        font = TTF_OpenFont("arial.ttf", 24);
        if (!font) {
            fprintf(stderr, "Failed to load fallback font\n");
            screen->clear(screen);
            TTF_Quit();
            SDL_Quit();
            return 1;
        }
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
        render_state(screen->renderer, main_menu);

        // Update screen
        SDL_RenderPresent(screen->renderer);

        // Cap frame rate
        SDL_Delay(16);
    }

    // Cleanup
    TTF_CloseFont(font);
    cleanup_states(main_menu);
    screen->clear(screen);
    TTF_Quit();
    SDL_Quit();

    return 0;
}