#include "./charater.h"

BasicCharater* init_basic_charater(const char* name, const char* description, const char* path_to_obj){
     BasicCharater* character = malloc(sizeof(BasicCharater));
    if (!character){
        printf("Failed to allocate memory to basic character \n");
        exit(EXIT_FAILURE);
    }
    
    strncpy(character->name, name, MAX_NAME_LENGTH - 1);
    character->name[MAX_NAME_LENGTH - 1] = '\0';
    
    strncpy(character->description, description, MAX_DESCRIPTION_LENGTH - 1);
    character->description[MAX_DESCRIPTION_LENGTH - 1] = '\0';
    
    character->level = 1;
    character->is_in_combat = false;
    
    character->rect = (SDL_Rect){0, 0, 50, 50};
    
    character->model = OBJ_Load(path_to_obj);

    
    
    return character;
}

void free_basic_charater(BasicCharater* bs){
    if(bs){
        if(bs->model) OBJ_Free(bs->model);
        free(bs);
    }
}