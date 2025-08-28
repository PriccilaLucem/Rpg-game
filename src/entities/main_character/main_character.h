#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H

#include <string>
#include <stdbool.h>

#include "../structs/inventory/inventory.h"
#include "../states/states.h"
#include "../structs/experience/experience.h"

typedef struct main_character
{
    int id;
    
    Experience* experience;
    playerInventory* player_inventory;
    

} MainCharacter;

MainCharacter* init_main_character(int id, int max_weight, size_t button_size);

#endif