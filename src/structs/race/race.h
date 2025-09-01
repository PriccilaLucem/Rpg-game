#ifndef RACE_H
#define RACE_H

#include <string.h>
#include "../../constants/constants.h"


/// @brief Race struct with base skills
typedef struct race {
    int id;
    
    char race_type[MAX_NAME_LENGTH]; 
    char race_name[MAX_NAME_LENGTH];
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
} Race;

Race* init_race(char race_type, const char race_name);

#endif