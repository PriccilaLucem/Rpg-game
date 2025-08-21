#include "./basic_character.h"

basicCharacter* init_basic_character_as_main(
    const char* name,
    const char* description,
    Attributes* attributes,
    Race* race,
    Class* class
) {
    basicCharacter* bc = malloc(sizeof(basicCharacter));
    if (!bc) {
        fprintf(stderr, "Erro ao alocar basicCharacter\n");
        exit(EXIT_FAILURE);
    }

    bc->id = get_num_state();

    strncpy(bc->name, name, MAX_NAME_LENGTH - 1);
    bc->name[MAX_NAME_LENGTH - 1] = '\0';

    strncpy(bc->description, description, MAX_DESCRIPTION_LENGTH - 1);
    bc->description[MAX_DESCRIPTION_LENGTH - 1] = '\0';

    bc->attributes = attributes;
    bc->race = race;
    bc->class = class;
    bc->equipped_armors = init_equipped_armors();

    bc->Characters.MainCharacter = init_main_character(bc->id, 100, 10);

    return bc;
}
