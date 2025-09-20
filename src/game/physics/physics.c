#include "./physics.h"

void wall_collision(BasicCharater* character, float wall_x_min, float wall_x_max, float wall_z_min, float wall_z_max);

void ApplyFloorPhysics(MainCharater* character) {
    if (!character || !character->bc) return;
    
    const float MIN_HEIGHT_ABOVE_FLOOR = 50.0f;
    
    if (character->bc->position_y < MIN_HEIGHT_ABOVE_FLOOR) {
        character->bc->position_y = MIN_HEIGHT_ABOVE_FLOOR;
        character->bc->velocity_y = 0; 
    }
    wall_collision(character->bc, -300.0f, 300.0f, -300.0f, 300.0f);
}

void wall_collision(BasicCharater* character, float wall_x_min, float wall_x_max, float wall_z_min, float wall_z_max) {
    if (!character) return;

    if (character->position_x < wall_x_min) {
        character->position_x = wall_x_min;
    } else if (character->position_x > wall_x_max) {
        character->position_x = wall_x_max;
    }

    if (character->position_z < wall_z_min) {
        character->position_z = wall_z_min;
    } else if (character->position_z > wall_z_max) {
        character->position_z = wall_z_max;
    }
}