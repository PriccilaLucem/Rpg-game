#ifndef EQUIPPED_ITENS_H
#define EQUIPPED_ITENS_H

#include "../itens/itens.h"

typedef struct equipped_armors{
    int id;
    Armor* head;
    Armor* chest;
    Armor* legs;
    Armor* boots;
    Armor* gloves;
    Armor* shield;
    
} EquippedArmors;

#endif