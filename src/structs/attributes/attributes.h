#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "../class/class.h"
#include "../race/race.h"

typedef struct attributes
{
    int id;
    int health;
    int mana;
    int strength;
    int agility;
    int intelligence;
    int charisma;
    int endurance;
    int luck;
    int wisdom;
    int dexterity;
    int perception;
    int stamina;
    int* level;

    void (*calculate_attributes) (Attributes* attributes, int* level, Race* race, Class* class);
} Attributes;

Attributes* init_attributes(int* level, Race* race, Class* cls);

#endif