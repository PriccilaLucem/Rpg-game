#include "./main_character.h"
#include <stdlib.h>

MainCharacter* init_main_character(int id, int max_weight, size_t button_size){
    MainCharacter* main_character = malloc(sizeof(MainCharacter));
    
    main_character->id = id;
    main_character->name = name;
    main_character->gold = 0;
    main_character->is_alive = true;
    Experience *experience = init_experience(0,0,0,0,0, "");
    main_character-> experience = experience;
    main_character->player_inventory = init_player_inventory(max_weight, "B");
    
    return main_character;
}
