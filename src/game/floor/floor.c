#include "./floor.h"

Floor* init_floor(const char* path){
    Floor* floor = malloc(sizeof(Floor));
    floor->model = OBJ_Load(path);
    floor->rect = toRect(floor->model);
    return floor;
}


