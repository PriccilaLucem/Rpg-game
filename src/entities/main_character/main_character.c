#include "./main_character.h"

MainCharacter* init_main_character(){
    MainCharacter* main_character = malloc(sizeof(MainCharacter));
    main_character->id = 1;
    return main_character;
}

void free_main_character(MainCharacter* mc){
    free(mc);
}