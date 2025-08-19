#include "menu.h"
#include <stdio.h>

void render_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    if (!surface) {
        printf("Failed to render text: %s\n", TTF_GetError());
        return;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    
    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void button_action(int button_id) {
    // Implement specific button actions
    switch(button_id) {
        case 0: // Start Game
            printf("Starting game...\n");
            break;
        case 1: // Options
            printf("Opening options...\n");
            break;
        case 2: // Exit
            printf("Exiting game...\n");
            break;
    }
}

void render_menu(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
    
    // Render menu items
    render_text(renderer, font, "Main Menu", 300, 50, white);
    render_text(renderer, font, "Start Game", 350, 200, white);
    render_text(renderer, font, "Options", 350, 250, white);
    render_text(renderer, font, "Exit", 350, 300, red);
    
    SDL_RenderPresent(renderer);
}   

void handle_menu_events(SDL_Event* event, int* running, int* game_state) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            *running = 0;
        }
        
        if (event->type == SDL_MOUSEBUTTONDOWN) {
            int x = event->button.x;
            int y = event->button.y;
            
            // Check button clicks (simplified example)
            if (x >= 350 && x <= 450) {
                if (y >= 200 && y <= 220) { // Start Game
                    *game_state = 1; // Switch to game state
                    button_action(0);
                }
                else if (y >= 250 && y <= 270) { // Options
                    button_action(1);
                }
                else if (y >= 300 && y <= 320) { // Exit
                    *running = 0;
                    button_action(2);
                }
            }
        }
    }
}