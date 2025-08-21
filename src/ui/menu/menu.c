#include "menu.h"
#include <stdio.h>

void handle_start_button(){
    printf("Start button");
}
void handle_option_button(){
    printf("Option button");
}
void handle_exit_button(){
    printf("exiting game");
    exit(0);
}
void handle_load_game_button(){
    printf("loading game");
}

Menu* init_menu(int screen_width, int screen_height, int font_size) {
    Menu* menu = malloc(sizeof(Menu));
    if (menu == NULL) {
        return NULL;
    }
    
    menu->screen_size_w = screen_width;
    menu->screen_size_h = screen_height;
    menu->font_size = font_size;
    
    menu->title = TTF_OpenFont(MENU_FONT_PATH, font_size * 2); // Title font is larger
    
    if (menu->title == NULL) {
        printf("Failed to load title font: %s\n", TTF_GetError());
        free(menu);
        return NULL;
    }
    
    TTF_Font* button_font = TTF_OpenFont(MENU_FONT_PATH, font_size);
    if (button_font == NULL) {
        printf("Failed to load button font: %s\n", TTF_GetError());
        TTF_CloseFont(menu->title);
        free(menu);
        return NULL;
    }
    
    int button_width = screen_width / 4;
    int button_height = 60;
    int button_spacing = 20;
    int total_menu_height = (button_height * 4) + (button_spacing * 3);
    int start_y = (screen_height - total_menu_height) / 2;
    int start_x = (screen_width - button_width) / 2;
    
    // Initialize buttons
    int current_y = start_y;
    
    menu->start_game = init_button(start_x, current_y, button_width, button_height, 
                                  "Start Game", false, false, button_font);
    menu->start_game->onClick = handle_start_button;
    current_y += button_height + button_spacing;
    
    menu->load_game = init_button(start_x, current_y, button_width, button_height, 
                                 "Load Game", false, false, button_font);
    menu->load_game->onClick = handle_load_game_button;
    
    current_y += button_height + button_spacing;
    
    menu->options = init_button(start_x, current_y, button_width, button_height, 
                               "Options", false, false, button_font);
    menu->options->onClick = handle_option_button;
    
    current_y += button_height + button_spacing;
    
    menu->exit = init_button(start_x, current_y, button_width, button_height, 
                            "Exit", false, false, button_font);
    
    menu->exit->onClick = handle_exit_button;

    if (!menu->start_game || !menu->load_game || !menu->options || !menu->exit) {
        TTF_CloseFont(menu->title);
        TTF_CloseFont(button_font);
        if (menu->start_game) free(menu->start_game);
        if (menu->load_game) free(menu->load_game);
        if (menu->options) free(menu->options);
        if (menu->exit) free(menu->exit);
        free(menu);
        return NULL;
    }
    
    return menu;
}

void render_menu_title(Menu* menu, SDL_Renderer* renderer, const char* title_text) {
    SDL_Color color = {255, 255, 255, 255}; // White color
    SDL_Surface* surface = TTF_RenderText_Solid(menu->title, title_text, color);
    if (surface) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture) {
            int title_x = (menu->screen_size_w - surface->w) / 2;
            int title_y = (menu->screen_size_h / 4) - (surface->h / 2);
            SDL_Rect dstrect = {title_x, title_y, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, NULL, &dstrect);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(surface);
    }
}

