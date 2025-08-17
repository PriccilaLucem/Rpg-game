#include <stdio.h>
#include <stdlib.h>

#include "./experience.h"

Experience* init_experience(int arrow_experience,
    int combat_experience,
    int magic_experience,
    int mining_experience,
    int player_experience,
    char* description,
){
    Experience* experience = malloc(sizeof(Experience));
    
    experience->id = get_num_state();
    experience->description = description;
    experience->arrow_experience = arrow_experience;
    experience->combat_experience = combat_experience;
    experience->magic_experience = magic_experience;
    experience->mining_experience = mining_experience;
    experience->player_experience = player_experience;
    
    return experience;
}