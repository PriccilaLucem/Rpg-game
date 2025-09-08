#ifndef ITENS_H 
#define ITENS_H

#include "../../constants/constants.h"
#include <string.h>
#include <stdbool.h>

struct MainCharater;

typedef struct weapon {
    int id;
    WeaponType weapon_type;
    int damage;
    bool is_equippable;

} Weapon;

// Struct de Armadura
typedef struct armor {
    int id;
    ArmorType armor_type;
    int defense;
    bool is_equippable;

} Armor;

// Struct de Item genérico
typedef struct itens {
    int id;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int price;
    int weight;

    ItemType item_type;

    union {
        Weapon* weapon;
        Armor* armor;
    } allItensType;

} Itens;


Weapon initWeapon(
    int id,
    WeaponType type,
    int damage,
    int weight,
    bool equippable,
    void (*onEquip)(Weapon*, struct MainCharater*),
    void (*onUnequip)(Weapon*, struct MainCharater*)
);

Armor initArmor(
    int id,
    ArmorType type,
    int defense,
    int weight,
    int price,
    bool equippable,
    void (*onEquip)(Armor*, struct MainCharater*),
    void (*onUnequip)(Armor*, struct MainCharater*)
);

Itens* initItem(
    const char* name,
    const char* description,
    ItemType type,
    int price,
    int weight
);

#endif