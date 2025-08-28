#ifndef BASIC_CHAR_H
#define BASIC_CHAR_H

#include <string.h>
#include <stdbool.h>

#include "../../states/global_states.h"
#include "../../entities/main_character/main_character.h"
#include "../attributes/attributes.h"
#include "../class/class.h"
#include "../equipped_itens/equipped_itens.h"
#include "../race/race.h"


typedef struct basic_character
{
    int id;
    char description[MAX_DESCRIPTION_LENGTH];
    char name[MAX_NAME_LENGTH];
    int level;
    bool is_in_combat;
    
    Attributes* attributes;
    Race* race;
    Class* cls;
    EquippedArmors* equipped_armors;
    char path_to_image[50];

    union basic_character
    {
        struct MainCharacter* MainCharacter;
        // Npc* npc;
    };
    

} basicCharacter;

basicCharacter* init_basic_character_as_main(
    const char* name,
    const char* description,
    const char* path_to_img,
    Attributes* attributes,
    Race* race,
    Class* class
);

#endif