#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H

#include <string.h>
#include <stdbool.h>

#include <stdlib.h>

typedef struct
{
    int id;
} MainCharacter;    

MainCharacter* init_main_character();
void free_main_character(MainCharacter* mc);

#endif