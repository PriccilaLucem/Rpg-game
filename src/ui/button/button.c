#include "./button.h"

Button* init_button(int x, int y, int width, int height,
     const char* label, bool isClicked, bool isHovered, TTF_Font* font) {
    Button* button = malloc(sizeof(Button));
    if (button == NULL) {
        fprintf(stderr, "Failed to allocate memory for Button\n");
        return NULL;
    }
    
    button->x = x;
    button->y = y;
    button->width = width;
    button->height = height;
    
    strncpy(button->label, label, MAX_BUTTON_LENGTH - 1);
    button->label[MAX_BUTTON_LENGTH - 1] = '\0'; 
    
    button->isHovered = isHovered;
    button->isClicked = isClicked;
    button->font = font;
    button->onClick = NULL;
    button->texture = NULL;
    button->rect = (SDL_Rect){x, y, width, height};
    
    return button;
}

void render_button(Button* button, SDL_Renderer* renderer) {
    if (!button || !renderer) return;
    
    // Create button background
    SDL_Rect button_rect = {button->x, button->y, button->width, button->height};
    
    // Set button color based on state
    if (button->isHovered) {
        SDL_SetRenderDrawColor(renderer, 100, 100, 200, 255); // Blue when hovered
    } else if (button->isClicked) {
        SDL_SetRenderDrawColor(renderer, 200, 100, 100, 255); // Red when clicked
    } else {
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Gray normal state
    }
    
    // Draw button background
    SDL_RenderFillRect(renderer, &button_rect);
    
    // Draw button border
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &button_rect);
    
    // Render button text
    if (button->font) {
        SDL_Color text_color = {255, 255, 255, 255};
        SDL_Surface* text_surface = TTF_RenderText_Solid(button->font, button->label, text_color);
        if (text_surface) {
            SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
            if (text_texture) {
                // Center text on button
                int text_x = button->x + (button->width - text_surface->w) / 2;
                int text_y = button->y + (button->height - text_surface->h) / 2;
                SDL_Rect text_rect = {text_x, text_y, text_surface->w, text_surface->h};
                
                SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
                SDL_DestroyTexture(text_texture);
            }
            SDL_FreeSurface(text_surface);
        }
    }
}

void check_button_hover(Button* button, int mouse_x, int mouse_y) {
    if (!button) return;
    
    button->isHovered = (mouse_x >= button->x && mouse_x <= button->x + button->width &&
                         mouse_y >= button->y && mouse_y <= button->y + button->height);
}

bool check_button_click(Button* button, int mouse_x, int mouse_y) {
    if (!button) return false;
    
    bool is_inside = (mouse_x >= button->x && mouse_x <= button->x + button->width &&
                      mouse_y >= button->y && mouse_y <= button->y + button->height);
    
    if (is_inside) {
        button->isClicked = true;
        return true;
    }
    return false;
}

void render_arrow_button(SDL_Renderer* renderer, int x, int y, int size, int direction) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    SDL_Point points[4];
    
    switch(direction) {
        case ARROW_LEFT:
            points[0] = (SDL_Point){x + size, y};
            points[1] = (SDL_Point){x, y + size/2};
            points[2] = (SDL_Point){x + size, y + size};
            points[3] = (SDL_Point){x + size, y}; 
            break;
            
        case ARROW_RIGHT:
            points[0] = (SDL_Point){x, y};
            points[1] = (SDL_Point){x + size, y + size/2};
            points[2] = (SDL_Point){x, y + size};
            points[3] = (SDL_Point){x, y};
            break;

    }
}

    void free_button(Button* button){
    if(button){
        free(button);
    }
}