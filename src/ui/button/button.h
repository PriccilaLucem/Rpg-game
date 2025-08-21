#ifndef BUTTON_H
#define BUTTON_H

#include <SDL_ttf.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../states/states.h"

typedef struct {
    int id;
    int x;
    int y;
    int width;
    int height;
    char label[MAX_BUTTON_LENGTH];
    bool isHovered;
    bool isClicked;
    TTF_Font* font;
    void (*onClick)(void);
} Button;

Button* init_button(int x, int y, int width, int height,
     const char* label, bool isClicked, bool isHovered, TTF_Font* font);

#endif