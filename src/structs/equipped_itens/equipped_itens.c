#include <stdlib.h>
#include <stdio.h>

#include "./equipped_itens.h"


EquippedArmors init_equipped_armors(
    Armor boots,
    Armor chest,
    Armor gloves,
    Armor head, 
    Armor legs,
    Armor shield,
){
    EquippedArmors* equipped_armors = malloc(sizeof(EquippedArmors));

    equipped_armors->id = get_num_state();
    equipped_armors->boots = boots;
    equipped_armors->chest = chest;
    equipped_armors->gloves = gloves;
    equipped_armors->head = head;
    equipped_armors->legs = legs;
    equipped_armors->shield = shield;

    return equipped_armors;
}