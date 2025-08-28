
#include <SDL_ttf.h>
#include <windows.h>
#include <SDL.h>

#include "./screen/screen.h"
#include "./states/states.h"
#include "./constants/constants.h"
#include "./ui/main_menu/main_menu.h"
#include "./config/config.h"
#include "./ui/options/options.h"
#include "./load_obj/load_obj.h"

GameState current_state = STATE_MAIN_MENU;
Config* current_config = NULL;
Options* options = NULL;
Menu* main_menu = NULL;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
OBJ_Model* obj_model = NULL;

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    (void)hInst; (void)hInstPrev; (void)cmdline; (void)cmdshow;
    
    SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "permonitorv2");
    SDL_SetHint(SDL_HINT_WINDOWS_DPI_SCALING, "1");
    
    InitialScreen* screen = init_initial_screen();   
    if(!screen){
        fprintf(stderr, "Failed to initialize screen\n");
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    
    obj_model = OBJ_Load("src/assets/player_assets/cube.obj");
    if (obj_model) {
        printf("Modelo OBJ carregado com sucesso!\n");
        OBJ_Scale(obj_model, 1.0f);
        OBJ_Translate(obj_model, 0, 0, 5);
        OBJ_SetColor(obj_model, (SDL_Color){255, 255, 255, 255});
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
    cleanup_states(main_menu, options);
    screen->clear(screen);
    TTF_Quit();
    SDL_Quit();

    return 0;
}