#include "basic_character.h"

BasicCharacter* init_basic_character_as_main(const char* name, const char* description, const char* path_to_obj)
{
    BasicCharacter* character = malloc(sizeof(BasicCharacter));
    if (!character) return NULL;
    
    // Inicializar campos
    strncpy(character->name, name, MAX_NAME_LENGTH - 1);
    character->name[MAX_NAME_LENGTH - 1] = '\0';
    
    strncpy(character->description, description, MAX_DESCRIPTION_LENGTH - 1);
    character->description[MAX_DESCRIPTION_LENGTH - 1] = '\0';
    
    character->level = 1;
    character->is_in_combat = false;
    
    // Inicializar rect
    character->rect = (SDL_Rect){0, 0, 50, 50}; // Valores padrão
    
    // Carregar modelo OBJ
    character->model = OBJ_Load(path_to_obj);
    if (!character->model) {
        free(character);
        return NULL;
    }
    
    // Inicializar caminho da imagem
    strncpy(character->path_to_image, "", 50);
    
    character->character_type.main_character = init_main_character();
    if (!character->character_type.main_character) {
        OBJ_Free(character->model);
        free(character);
        return NULL;
    }
    
    return character;
}