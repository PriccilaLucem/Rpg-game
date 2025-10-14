#include "charater_input.h"
void HandleCharacterInput(MainCharater* character, const Uint8* keyboard_state) {
    if (!character) return;
    
    float move_speed = 5.0f;
    
    // Salvar posição anterior para possível colisão
    float old_x = character->bc->position_x;
    float old_z = character->bc->position_z;
    
    if (keyboard_state[SDL_SCANCODE_UP]) {
        character->bc->position_z -= move_speed;
    }
    if (keyboard_state[SDL_SCANCODE_DOWN]) {
        character->bc->position_z += move_speed;
    }
    if (keyboard_state[SDL_SCANCODE_LEFT]) {
        character->bc->position_x -= move_speed;
    }
    if (keyboard_state[SDL_SCANCODE_RIGHT]) {
        character->bc->position_x += move_speed;
    }
}