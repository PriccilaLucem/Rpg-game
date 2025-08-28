#include "main_menu.h"
#include <stdio.h>

static void handle_start_button(void* data){
    change_state(STATE_GAME);
    printf("Entering game");
}
static void handle_option_button(void* data){
    change_state(STATE_OPTIONS);
    printf("opening options");
}
static void handle_exit_button(void* data){
    printf("exiting game");
    change_state(STATE_EXIT);
    exit(0);
}
static void handle_load_game_button(void* data){
    printf("loading game");
}

Menu* init_menu(int screen_width, int screen_height, int font_size) {
    Menu* menu = malloc(sizeof(Menu));
    if (menu == NULL) {
        return NULL;
    }
    menu->id = get_id_gen();
    menu->screen_size_w = screen_width;
    menu->screen_size_h = screen_height;
    menu->font_size = font_size;
    
    menu->title = TTF_OpenFont(MENU_FONT_PATH, font_size * 2); 
    
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

static void render_menu_title(Menu* menu, SDL_Renderer* renderer, const char* title_text) {
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

void render_menu(Menu* menu, SDL_Renderer* renderer){
    if(!menu || !renderer){
        printf("Menu or renderer is NULL\n");
        exit(EXIT_FAILURE);
    }

    render_menu_title(menu, renderer, "Game menu");

    render_button(menu->start_game, renderer);
    render_button(menu->load_game,renderer);
    render_button(menu->options,renderer);
    render_button(menu->exit,renderer);
}



void handle_menu_input(Menu* menu, SDL_Event* event) {
    if (!menu || !event) return;

    int mouse_x, mouse_y;
    int total_buttons = 4; // start, load, options, exit

    switch (event->type) {
        // ---------------- MOUSE ----------------
        case SDL_MOUSEMOTION:
            mouse_x = event->motion.x;
            mouse_y = event->motion.y;

            check_button_hover(menu->start_game, mouse_x, mouse_y);
            check_button_hover(menu->load_game, mouse_x, mouse_y);
            check_button_hover(menu->options, mouse_x, mouse_y);
            check_button_hover(menu->exit, mouse_x, mouse_y);
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                mouse_x = event->button.x;
                mouse_y = event->button.y;

                if (check_button_click(menu->start_game, mouse_x, mouse_y) && menu->start_game->onClick)
                    menu->start_game->onClick(menu);
                if (check_button_click(menu->load_game, mouse_x, mouse_y) && menu->load_game->onClick)
                    menu->load_game->onClick(menu);
                if (check_button_click(menu->options, mouse_x, mouse_y) && menu->options->onClick)
                    menu->options->onClick(menu);
                if (check_button_click(menu->exit, mouse_x, mouse_y) && menu->exit->onClick)
                    menu->exit->onClick(menu);
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if (event->button.button == SDL_BUTTON_LEFT) {
                if (menu->start_game) menu->start_game->isClicked = false;
                if (menu->load_game)  menu->load_game->isClicked = false;
                if (menu->options)    menu->options->isClicked = false;
                if (menu->exit)       menu->exit->isClicked = false;
            }
            break;

        // ---------------- KEYBOARD ----------------
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
            case SDLK_UP:
                menu->selected_index--;
                if (menu->selected_index < 0)
                    menu->selected_index = 3; // último botão
                break;

            case SDLK_DOWN:
                menu->selected_index++;
                if (menu->selected_index > 3)
                    menu->selected_index = 0; // primeiro botão
                break;

            case SDLK_RETURN:
            case SDLK_SPACE:
                if (menu->selected_index == 0 && menu->start_game->onClick)
                    menu->start_game->onClick(menu);
                else if (menu->selected_index == 1 && menu->load_game->onClick)
                    menu->load_game->onClick(menu);
                else if (menu->selected_index == 2 && menu->options->onClick)
                    menu->options->onClick(menu);
                else if (menu->selected_index == 3 && menu->exit->onClick)
                    menu->exit->onClick(menu);
                break;
        }

    // Atualiza o "hover" baseado no índice
    menu->start_game->isHovered = (menu->selected_index == 0);
    menu->load_game->isHovered  = (menu->selected_index == 1);
    menu->options->isHovered    = (menu->selected_index == 2);
    menu->exit->isHovered       = (menu->selected_index == 3);
    break;

    }
}

void update_main_menu(Menu* menu) {
    // Placeholder for future updates (animations, etc.)
    // Currently, no dynamic elements to update
}

void free_main_menu(Menu* menu) {
    if (menu) {
        if (menu->title) TTF_CloseFont(menu->title);
        if (menu->start_game) free_button(menu->start_game);
        if (menu->load_game) free_button(menu->load_game);
        if (menu->options) free_button(menu->options);
        if (menu->exit) free_button(menu->exit);
        free(menu);
    }
}
