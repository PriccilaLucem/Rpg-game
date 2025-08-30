#include "./main_character.h"

MainCharacter* init_main_character(int id){
    MainCharacter* main_character = malloc(sizeof(MainCharacter));
    
    main_character->id = id;
    
    return main_character;
}
