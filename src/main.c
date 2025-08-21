#include <windows.h>

#include "./screen/screen.h"
#include "./states/states.h"
#include "./ui/menu/menu.h"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    (void)hInst; (void)hInstPrev; (void)cmdline; (void)cmdshow;
    
    init_libs();

    SDL_Window* window = init_window();
    
    SDL_Renderer* renderer = init_renderer(window);
    
    int running = 1;
    
    Menu* menu = init_menu(SCREEN_W, SCREEN_H, 20);

    while (running) {
        SDL_Event event;    
        render_menu_title(menu, renderer, "MENU TITLE");
    }

    

    return 0;
}