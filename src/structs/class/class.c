#include "./class.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

Class* init_base_class(char class_name, char description) {
    Class* class = malloc(sizeof(Class));
      
    class->id = get_num_state();
        
    class->class_name = strncpy(class-> class_name, class_name, MAX_NAME_LENGTH - 1);
    class->class_name[MAX_NAME_LENGTH - 1] = '\0'; 
    class->description = strncpy(class->description, description, MAX_DESCRIPTION_LENGTH - 1);
    class->description[MAX_DESCRIPTION_LENGTH - 1] = '\0'; 

    class->charisma_bonus = 0;
    class->intelligence_bonus = 0;
    class->strength_bonus = 0;
    class->agility_bonus = 0;
    class->endurance_bonus = 0;
    class->luck_bonus = 0;
    class->wisdom_bonus = 0;
    class->dexterity_bonus = 0;
    class->perception_bonus = 0;
    class->stamina_bonus = 0;

    switch (class_name) {
        case CLASS_WARRIOR:
            class->strength_bonus += 4;
            class->endurance_bonus += 3;
            class->stamina_bonus += 2;
            class->agility_bonus -= 1; 
            break;

        case CLASS_MAGE:
            class->intelligence_bonus += 5;
            class->wisdom_bonus += 3;
            class->perception_bonus += 2;
            class->strength_bonus -= 2; 
            break;

        case CLASS_ROGUE: 
            class->dexterity_bonus += 4;
            class->agility_bonus += 3;
            class->luck_bonus += 2;
            class->endurance_bonus -= 1;
            break;

        case CLASS_CLERIC: 
            class->wisdom_bonus += 4;
            class->charisma_bonus += 2;
            class->endurance_bonus += 2;
            class->dexterity_bonus -= 1;
            break;

        case CLASS_ARCHER:
            class->dexterity_bonus += 4;
            class->perception_bonus += 3;
            class->agility_bonus += 2;
            class->strength_bonus -= 1;
            break;

        default:
            fprintf(stderr, "Unknown class type %d\n", class_name);
            free(class);
            exit(EXIT_FAILURE);
            break;
    }
    return class;
}
