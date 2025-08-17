#ifndef CLASS_H
#define CLASS_H

#include <string.h>
#include "../states/states.h"

typedef struct class{
    
    int id;
    char class_name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int charisma_bonus;
    int intelligence_bonus;
    int strength_bonus;
    int agility_bonus;
    int endurance_bonus;
    int luck_bonus;
    int wisdom_bonus;
    int dexterity_bonus;
    int perception_bonus;
    int stamina_bonus;
    
} Class;

Class* init_base_class(char class_name, char description);


#endif