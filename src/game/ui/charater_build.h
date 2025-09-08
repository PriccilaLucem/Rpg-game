#ifndef CHAR_BUILD_H
#define CHAR_BUILD_H

#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL_ttf.h>

#include "../../constants/constants.h"
#include "../../ui/button/button.h"
#include "../../structs/charater/charater.h"
#include "../floor/floor.h"

typedef struct {
    char title[MAX_DESCRIPTION_LENGTH];
    TTF_Font* title_font;
    InputField* input_field;
    Button* button;

} charaterBuild;

charaterBuild* init_char_build();
void render_char_build(charaterBuild* char_build, SDL_Renderer* renderer);
void free_char_build(charaterBuild* char_build);
#endif