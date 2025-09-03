#include <SDL.h>
#include <SDL_ttf.h>
#include "./screen/screen.h"
#if defined(_WIN32) || defined(WIN32)
    #include <windows.h>
#endif
#include "./ui/main_menu/main_menu.h"
#include "./ui/options/options.h"
#include "./load_obj/load_obj.h"


Options* options = NULL;
Menu* main_menu = NULL;
OBJ_Model* obj_model = NULL;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
#if defined(_WIN32) || defined(WIN32)
    int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow){
        (void)hInst; (void)hInstPrev; (void)cmdline; (void)cmdshow;
#else 
    int main(int argc, char* args[]){
        (void)argc; (void)args;
#endif 
    
    SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "permonitorv2");
    SDL_SetHint(SDL_HINT_WINDOWS_DPI_SCALING, "1");
    
    InitialScreen* screen = init_initial_screen();   
    if(!screen){
        fprintf(stderr, "%s", "Failed to initialize screen\n");
        SDL_Quit();
        return 1;
    }
    obj_model = OBJ_Load("src/assets/player_assets/cube.obj");
    if (obj_model) {
        printf("Modelo OBJ carregado com sucesso!\n");
        OBJ_Scale(obj_model, 1.0f);
        OBJ_Translate(obj_model, 0, 0, 5);
        OBJ_SetColor(obj_model, (SDL_Color){255, 255, 255, 255});
    } else {
        fprintf(stderr, "%s", "Failed to load OBJ model\n");
    }

    main_menu = init_menu(screen->screen_width, screen->screen_height,  24);
    options = init_options(screen->screen_width, screen->screen_height, screen->renderer, 24);
    if (!main_menu || !options) {
        fprintf(stderr, "%s", "Failed to initialize main menu or options\n");
        screen->clear(screen);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Inicializar estados
    init_states(STATE_MAIN_MENU);
    int running = 1;
    const int TARGET_FPS = 60;
    const int FRAME_TIME = 1000 / TARGET_FPS;
    Uint32 frame_start;
    int frame_delay;
    while (running && current_state != STATE_EXIT) {
        frame_start = SDL_GetTicks();
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
        frame_delay = FRAME_TIME - (SDL_GetTicks() - frame_start);
        if (frame_delay > 0) {
            SDL_Delay(frame_delay);
        }
    }

    // Cleanup
    cleanup_states(main_menu, options);
    if (obj_model) {
        OBJ_Free(obj_model);
    }
    screen->clear(screen);
    TTF_Quit();
    SDL_Quit();

    return 0;
}