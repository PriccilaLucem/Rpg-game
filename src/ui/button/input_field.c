#include "./button.h"
#include "./button.h"
#include <string.h>
#include <stdlib.h>

InputField* init_input_field(int x, int y, int width, int height, TTF_Font* font, SDL_Color textColor) {
    InputField* field = malloc(sizeof(InputField));
    if(!field){
        printf("Failed to initialize input field");
        exit(EXIT_FAILURE);
    }
    field->x = x;
    field->y = y;
    field->width = width;
    field->height = height;
    field->font = font;
    field->textColor = textColor;
    field->rect = (SDL_Rect){x, y, width, height};
    field->text[0] = '\0';
    field->isActive = false;
    field->texture = NULL;
    return field;
}

void render_input_field(InputField* field, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &field->rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderDrawRect(renderer, &field->rect);

    if (strlen(field->text) > 0) {
        SDL_Surface* surface = TTF_RenderText_Solid(field->font, field->text, field->textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect textRect = {field->x + 5, field->y + 5, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &textRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}

void handle_input_event(InputField* field, SDL_Event* e, SDL_Renderer* renderer) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int mx = e->button.x;
        int my = e->button.y;
        field->isActive = (mx >= field->x && mx <= field->x + field->width &&
                           my >= field->y && my <= field->y + field->height);
    }
    else if (e->type == SDL_TEXTINPUT && field->isActive) {
        size_t current_len = strlen(field->text);
        size_t input_len = strlen(e->text.text);
        if (current_len + input_len < MAX_INPUT_LENGTH - 1) {
            strncat(field->text, e->text.text, MAX_INPUT_LENGTH - current_len - 1);
            field->text[MAX_INPUT_LENGTH - 1] = '\0';
        }
    }
    else if (e->type == SDL_KEYDOWN && field->isActive) {
        if (e->key.keysym.sym == SDLK_BACKSPACE && strlen(field->text) > 0) {
            field->text[strlen(field->text) - 1] = '\0';
        }
    }
}

void free_input_field(InputField* field) {
    if (field) {
        if (field->texture) SDL_DestroyTexture(field->texture);
        free(field);
    }
}
