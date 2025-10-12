#include "./button.h"

ButtonDropdown* init_button_dropdown(int x, int y, int width, int height, int item_count, DropdownItem** dropdown_itens ,const char* text, TTF_Font* font, SDL_Color textColor) {
    ButtonDropdown* dropdown = malloc(sizeof(ButtonDropdown));
    if(!dropdown){
        printf("Failed to initialize button dropdown");
        exit(EXIT_FAILURE);
    }
    dropdown->x = x;
    dropdown->y = y;
    dropdown->width = width;
    dropdown->height = height;
    strncpy(dropdown->text, text, MAX_INPUT_LENGTH - 1);
    dropdown->text[MAX_INPUT_LENGTH - 1] = '\0';
    dropdown->isActive = false;
    dropdown->font = font;
    dropdown->textColor = textColor;
    dropdown->rect = (SDL_Rect){x, y, width, height};
    dropdown->texture = NULL;
    dropdown->items = dropdown_itens;
    dropdown->itemCount = item_count;
    dropdown->selectedItem = NULL;
    return dropdown;
} 

void render_button_dropdown(ButtonDropdown* dropdown, SDL_Renderer* renderer) {
    if (!dropdown || !renderer) return;
    
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &dropdown->rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderDrawRect(renderer, &dropdown->rect);

    if (dropdown->text && strlen(dropdown->text) > 0 && dropdown->font) {
        SDL_Surface* surface = TTF_RenderText_Solid(dropdown->font, dropdown->text, dropdown->textColor);
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture) {
                SDL_Rect textRect = {dropdown->x + 5, dropdown->y + (dropdown->height - surface->h) / 2, surface->w, surface->h};
                SDL_RenderCopy(renderer, texture, NULL, &textRect);
                SDL_DestroyTexture(texture);
            }
            SDL_FreeSurface(surface);
        }
    }
}

void open_button_dropdown(ButtonDropdown* dropdown) {
    dropdown->isActive = true;
}
void close_button_dropdown(ButtonDropdown* dropdown) {
    dropdown->isActive = false;
}

void render_button_dropdown_options(ButtonDropdown* dropdown, SDL_Renderer* renderer){
    if (!dropdown || !renderer || !dropdown->isActive || !dropdown->items || !dropdown->font) return;

    int optionHeight = dropdown->height;
    SDL_Rect optionRect = {dropdown->x, dropdown->y + dropdown->height, dropdown->width, optionHeight};

    for (int i = 0; i < dropdown->itemCount && i < 10; i++) { // Limit to 10 items max
        if (!dropdown->items[i] || !dropdown->items[i]->text) continue;
        
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        SDL_RenderFillRect(renderer, &optionRect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        SDL_RenderDrawRect(renderer, &optionRect);

        if (strlen(dropdown->items[i]->text) > 0) {
            SDL_Surface* surface = TTF_RenderText_Solid(dropdown->font, dropdown->items[i]->text, dropdown->textColor);
            if (surface) {
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (texture) {
                    SDL_Rect textRect = {optionRect.x + 5, optionRect.y + (optionHeight - surface->h) / 2, surface->w, surface->h};
                    SDL_RenderCopy(renderer, texture, NULL, &textRect);
                    SDL_DestroyTexture(texture);
                }
                SDL_FreeSurface(surface);
            }
        }

        optionRect.y += optionHeight;
    }
}

void free_button_dropdown(ButtonDropdown* dropdown) {
    if (!dropdown) return;
    
    if (dropdown->texture) {
        SDL_DestroyTexture(dropdown->texture);
    }
    
    // Free dropdown items
    if (dropdown->items) {
        for (int i = 0; i < dropdown->itemCount; i++) {
            if (dropdown->items[i]) {
                free(dropdown->items[i]);
            }
        }
        free(dropdown->items);
    }
    
    free(dropdown);
}
