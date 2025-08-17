#include "./attributes.h"
#include <stdlib.h>

Attributes* init_attributes(int* level, Race* race, Class* cls) {
    Attributes* attributes = malloc(sizeof(Attributes));
    attributes->id = get_num_state();
    calculate_attributes(attributes, level, race, cls);
    return attributes;
}

void calculate_attributes(Attributes* attributes, int* level, Race* race, Class* cls) {
    attributes->level = *level;
    
    attributes->strength = 10 + race->strength_bonus + cls->strength_bonus * (*level);
    attributes->agility = 10 + race->agility_bonus + cls->agility_bonus * (*level);
    attributes->intelligence = 10 + race->intelligence_bonus + cls->intelligence_bonus * (*level);
    attributes->charisma = 10 + race->charisma_bonus + cls->charisma_bonus * (*level);
    attributes->endurance = 10 + race->endurance_bonus + cls->endurance_bonus * (*level);
    attributes->luck = 5 + race->luck_bonus + cls->luck_bonus;
    attributes->wisdom = 10 + race->wisdom_bonus + cls->wisdom_bonus * (*level);
    attributes->dexterity = 10 + race->dexterity_bonus + cls->dexterity_bonus * (*level);
    attributes->perception = 10 + race->perception_bonus + cls->perception_bonus * (*level);
    attributes->stamina = 15 + race->stamina_bonus + cls->stamina_bonus * (*level);
    
    attributes->health = 50 + (attributes->endurance * 3) + (attributes->stamina * 2);
    attributes->mana = 30 + (attributes->intelligence * 2) + (attributes->wisdom * 1);
}
