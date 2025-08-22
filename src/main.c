#include <windows.h>

#include "./screen/screen.h"
#include "./states/states.h"
#include "./ui/menu/menu.h"


int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    (void)hInst; (void)hInstPrev; (void)cmdline; (void)cmdshow;
    
    InitialScreen* screen = init_initial_screen();   
    if(!screen){
        return 1;
    }
    
    Menu* menu = init_menu(SCREEN_W, SCREEN_H, 20);
    if (!menu) {
        exit(EXIT_FAILURE);
    }
    
    int running = 1;

   while (running) {
        // Process events
        while (SDL_PollEvent(&screen->event)) {
            if (screen->event.type == SDL_QUIT) {
                running = 0;
            }
            handle_menu_input(menu, &screen->event);
            
        }

        // Clear screen
        SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 255);
        SDL_RenderClear(screen->renderer);

        // Render menu
        render_menu(menu, screen->renderer);

        // Update screen
        SDL_RenderPresent(screen->renderer);

        // Cap frame rate
        SDL_Delay(16);
    }

    screen->clear(screen);
    destroy_menu(menu);    

    return 0;
}