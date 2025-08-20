#ifndef STATES_H
#define STATES_H

#define MAX_DESCRIPTION_LENGTH 200
#define MAX_NAME_LENGTH 20
#define PATH_TO_MENU_FONT "src/assets/fonts/Luckiest_Guy,Playfair_Display/Luckiest_Guy/LuckiestGuy-Regular.ttf"

typedef enum itens_type {
    ITEM_WEAPON,      
    ITEM_ARMOR,       
    ITEM_CONSUMABLE,  
    ITEM_MATERIAL,    
    ITEM_KEY,        
    ITEM_MISC
} ItemType;

typedef enum armor_type {
    ARMOR_TYPE_HELMET = 'H',
    ARMOR_TYPE_CHEST = 'C',
    ARMOR_TYPE_LEGS = 'L',
    ARMOR_TYPE_BOOTS = 'B',
    ARMOR_TYPE_GLOVES = 'G',
    ARMOR_TYPE_SHIELD = 'S',
} ArmorType;

typedef enum weapon_type {
    WEAPON_TYPE_SWORD = 'S',
    WEAPON_TYPE_AXE = 'A',
    WEAPON_TYPE_BOW = 'B',
    WEAPON_TYPE_DAGGER = 'D',
    WEAPON_TYPE_STAFF = 'T',
    WEAPON_TYPE_MACE = 'M'
} WeaponType;

int get_num_state(void);

#endif