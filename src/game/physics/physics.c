#include "./physics.h"

void ApplyFloorPhysics(MainCharater* character) {
    if (!character || !character->bc) return;
    
    const float MIN_HEIGHT_ABOVE_FLOOR = 50.0f;
    
    if (character->bc->position_y < MIN_HEIGHT_ABOVE_FLOOR) {
        character->bc->position_y = MIN_HEIGHT_ABOVE_FLOOR;
        character->bc->velocity_y = 0; 
    }
    
    // character->velocity_y -= 0.5f; // Gravidade
    // character->position_y += character->velocity_y;
}
