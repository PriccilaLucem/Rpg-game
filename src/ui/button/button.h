#ifndef BUTTON_H
#define BUTTON_H

#include <SDL_ttf.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../constants/constants.h"

typedef struct {
   int x;
    int y;
    int width;
    int height;
    char text[MAX_INPUT_LENGTH];
    bool isActive;       
    TTF_Font* font;
    SDL_Color textColor;
    SDL_Rect rect;
    SDL_Texture* texture;

}InputField;

typedef struct Button{
    int id;
    int x;
    int y;
    int width;
    int height;
    char label[MAX_BUTTON_LENGTH];
    bool isHovered;
    bool isClicked;
    TTF_Font* font;
    SDL_Rect rect;
    SDL_Texture* texture;
    void (*onClick)(void*);
    void* onClickData;
} Button;

Button* init_button(int x, int y, int width, int height,
     const char* label, bool isClicked, bool isHovered, TTF_Font* font);

void render_button(Button* button, SDL_Renderer* renderer);
void check_button_hover(Button* button, int mouse_x, int mouse_y);
bool check_button_click(Button* button, int mouse_x, int mouse_y);
void free_button(Button* button);
void render_arrow_button(SDL_Renderer* renderer, int x, int y, int size, int direction);

InputField* init_input_field(int x, int y, int width, int height, TTF_Font* font, SDL_Color textColor);
void render_input_field(InputField* field, SDL_Renderer* renderer);
void handle_input_event(InputField* field, SDL_Event* e, SDL_Renderer* renderer);
void free_input_field(InputField* field);
#endif