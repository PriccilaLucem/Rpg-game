#include "village_maccarena.h"


VillageMaccarena* init_village_maccarena(SDL_Renderer* renderer) {
    VillageMaccarena* village = (VillageMaccarena*)malloc(sizeof(VillageMaccarena));
    if (!village) {
        printf("Error allocating memory for VillageMaccarena\n");
        exit(EXIT_FAILURE);
    }

    
    SDL_Color house_color = {255, 0, 0, 255}; // Exemplo de cor vermelha
    village->house = init_house("assets/houses/house.obj", 1.0f, 0.0f, 0.0f, 0.0f, house_color);

    village->num_floors = 3; 
    village->floors = (Floor**)malloc(village->num_floors * sizeof(Floor*));
    for (int i = 0; i < village->num_floors; i++) {
        char path[100];
        snprintf(path, sizeof(path), "assets/floors/floor_%d.obj", i + 1);
        village->floors[i] = init_floor_from_obj(renderer, path, 100, 30);
    }
    village->current_floor = 0;

    
    village->camera = (IsoCamera*)malloc(sizeof(IsoCamera));
    IsoCamera_Init(village->camera, 0.0f, 0.0f, 10.0f); 

    village->main_charater = NULL; 

    return village;
}

void render_village_maccarena(SDL_Renderer* renderer, VillageMaccarena* village) {
    if (!village) return;

    
    if (village->current_floor >= 0 && village->current_floor < village->num_floors) {
        render_floor(renderer, village->floors[village->current_floor], village->camera, 100, 100, 100, 30);
    }

    
    render_house(village->house, renderer, village->camera->x, village->camera->y, village->camera->z);

    
    if (village->main_charater && village->main_charater->bc && village->main_charater->bc->model) {
        OBJ_Render_Isometric(renderer, village->main_charater->bc->model, village->camera);
    }
}
void destroy_village_maccarena(VillageMaccarena* village) {
    if (!village) return;

    
    if (village->house) {
        free_house(village->house);
        village->house = NULL;
    }

    
    for (int i = 0; i < village->num_floors; i++) {
        if (village->floors[i]) {
            free_floor(village->floors[i]);
            village->floors[i] = NULL;
        }
    }
    free(village->floors);
    village->floors = NULL;

    
    if (village->camera) {
        free(village->camera);
        village->camera = NULL;
    }

    
    if (village->main_charater) {
        if (village->main_charater->bc) {
            free_basic_charater(village->main_charater->bc);
            free_main_charater(village->main_charater);
        }
        free(village->main_charater);
        village->main_charater = NULL;
    }

    free(village);
}