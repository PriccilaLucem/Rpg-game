#include "./race.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

Race* init_race(char race_type, const char race_name) {
    Race* race = malloc(sizeof(Race));

    if(!race){
        fprintf(stderr, "ERROR IN ALLOCATING MEMORY TO RACE \n")
        exit(EXIT_FAILURE);
    }

    race->id = get_num_state();
    race->race_type = race_type
    
    race->race_name = strncpy(race->race_name, race_name, MAX_NAME_LENGTH - 1); 
    race->race_name[MAX_NAME_LENGTH - 1] = '\0';

    race->charisma_bonus = 0;
    race->intelligence_bonus = 0;
    race->strength_bonus = 0;
    race->agility_bonus = 0;
    race->endurance_bonus = 0;
    race->luck_bonus = 0;
    race->wisdom_bonus = 0;
    race->dexterity_bonus = 0;
    race->perception_bonus = 0;
    race->stamina_bonus = 0;

    switch (race_type) {
        case RACE_HUMAN: // 'H'
            race->charisma_bonus += 2;
            race->intelligence_bonus += 1;
            race->endurance_bonus += 1;
            break;

        case RACE_ELF: // 'E'
            race->agility_bonus += 3;
            race->wisdom_bonus += 2;
            race->perception_bonus += 2;
            race->strength_bonus -= 1;
            break;

        case RACE_DWARF: // 'D'
            race->strength_bonus += 2;
            race->endurance_bonus += 3;
            race->stamina_bonus += 2;
            race->agility_bonus -= 1; 
            break;

        case RACE_GNOME: // 'G'
            race->intelligence_bonus += 3;
            race->dexterity_bonus += 2;
            race->luck_bonus += 1;
            race->strength_bonus -= 2; 
            break;

        case RACE_TIEFLING: // 'T'
            race->charisma_bonus += 3;
            race->intelligence_bonus += 1;
            race->luck_bonus += 1;
            race->wisdom_bonus -= 1; 
            break;

        default:
            assert(0, "Unknown race type: %c\n", race_type);
            free(race);
            exit(EXIT_FAILURE);
    }
    return race;

}