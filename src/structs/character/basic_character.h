#ifndef BASIC_CHAR_H
#define BASIC_CHAR_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdlib.h>
#include <SDL.h>

#include "../../constants/constants.h"
#include "../../load_obj/load_obj.h"
#include "../../entities/main_character/main_character.h"

typedef struct 
{
    int id;
    char description[MAX_DESCRIPTION_LENGTH];
    char name[MAX_NAME_LENGTH];
    int level;
    bool is_in_combat;
    SDL_Rect rect;
    OBJ_Model* model;
    char path_to_image[50];

    union
    {
        MainCharacter* main_character;
        // Npc* npc;
    } character_type;
    

} BasicCharacter;

BasicCharacter* init_basic_character_as_main(
    const char* name,
    const char* description,
    const char* path_to_obj
);

#endif