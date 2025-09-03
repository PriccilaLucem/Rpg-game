#ifndef CHAR_BUILD_H
#define CHAR_BUILD_H

#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL_ttf.h>

#include "../../constants/constants.h"
#include "../../ui/button/button.h"
#include "../../structs/character/basic_character.h"
#include "../floor/floor.h"

typedef struct {
    char title[MAX_DESCRIPTION_LENGTH];
    TTF_Font* title_font;
    InputField* input_field;
    Button* button;

} CharacterBuild;

CharacterBuild* init_char_build();
void handle_input_char_build(CharacterBuild* char_build, SDL_Renderer* renderer, SDL_Event* event);
void render_char_build(CharacterBuild* char_build, SDL_Renderer* renderer);
void free_char_build(CharacterBuild* char_build);
#endif