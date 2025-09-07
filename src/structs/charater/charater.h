#ifndef BASIC_CHAR_H
#define BASIC_CHAR_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdlib.h>
#include <SDL.h>

#include "../../constants/constants.h"
#include "../../load_obj/load_obj.h"

typedef struct BasicCharater
{
    char description[MAX_DESCRIPTION_LENGTH];
    char name[MAX_NAME_LENGTH];
    int level;
    bool is_in_combat;
    SDL_Rect rect;
    OBJ_Model* model;
} BasicCharater;



typedef struct MainCharater
{   
    int tile_x;
    int tile_y;
    BasicCharater* bc;
    int id;
    
} MainCharater;    

BasicCharater* init_basic_charater(const char* name, const char* description, const char* path_to_obj);
void free_basic_charater(BasicCharater* basic_charater);
MainCharater* init_main_charater(int start_tile_y, int start_tile_x, char* name, const char* description, const char* path_to_obj);
void free_main_charater(MainCharater* main_charater);

#endif