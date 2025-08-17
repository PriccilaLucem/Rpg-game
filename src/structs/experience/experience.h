#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include "../../states/states.h"

typedef struct Experience
{
    int id;
    char description[MAX_DESCRIPTION_LENGTH];
    int combat_experience;
    int arrow_experience;
    int magic_experience;
    int player_experience;
    int mining_experience;

} Experience;


Experience* init_experience(int arrow_experience,
    int combat_experience,
    int magic_experience,
    int mining_experience,
    int player_experience,
    char* description,
);

#endif