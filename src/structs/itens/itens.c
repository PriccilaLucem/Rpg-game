#include "./itens.h"
#include <stdlib.h>
#include <stdio.h>

Weapon initWeapon(
    int id,
    WeaponType type,
    int damage,
    int weight,
    bool equippable,
    void (*onEquip)(Weapon*, struct MainCharater*),
    void (*onUnequip)(Weapon*, struct MainCharater*)
) {
    Weapon w;
    w.id = id;
    w.weapon_type = type;
    w.damage = damage;
    w.weight = weight;
    w.is_equippable = equippable;
    w.onEquip = onEquip;
    w.onUnequip = onUnequip;
    return w;
}

Armor initArmor(
    int id,
    ArmorType type,
    int defense,
    int weight,
    int price,
    bool equippable,
    void (*onEquip)(Armor*, struct MainCharater*),
    void (*onUnequip)(Armor*, struct MainCharater*)
) {
    Armor a;
    a.id = id;
    a.armor_type = type;
    a.defense = defense;
    a.weight = weight;
    a.price = price;
    a.is_equippable = equippable;
    a.onEquip = onEquip;
    a.onUnequip = onUnequip;
    return a;
}

Itens* initItem(
    const char* name,
    const char* description,
    ItemType type,
    int price,
    int weight
) {
    Itens* item = malloc(sizeof(Itens));
    if (!item) {
        fprintf(stderr, "Erro ao alocar memória para Itens\n");
        exit(EXIT_FAILURE);
    }

    item->id = get_num_state();
    strncpy(item->name, name, MAX_NAME_LENGTH - 1);
    item->name[MAX_NAME_LENGTH - 1] = '\0';
    strncpy(item->description, description, MAX_DESCRIPTION_LENGTH - 1);
    item->description[MAX_DESCRIPTION_LENGTH - 1] = '\0';

    if (type >= ITEM_WEAPON && type <= ITEM_MISC) {
        item->item_type = type;
    } else {
        fprintf(stderr, "Tipo de item inválido: %d\n", type);
        free(item);
        return NULL;
    }

    item->price = price;
    item->weight = weight;

    item->allItensType.weapon = NULL;
    item->allItensType.armor = NULL;

    return item;
}

