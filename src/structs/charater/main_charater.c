#include "./charater.h"

MainCharater* init_main_charater(int start_tile_y, int start_tile_x, char* name, const char* description, const char* path_to_obj){
    MainCharater* main_charater = malloc(sizeof(MainCharater));
    if(!main_charater){
        printf("Failed to allocate memory to main charater \n");
        exit(EXIT_FAILURE);
    }

    main_charater->id = 1;
    main_charater->tile_y= start_tile_x;
    main_charater->tile_x= start_tile_y;
    main_charater->bc = init_basic_charater(name, description, path_to_obj);
    return main_charater;
}

void free_main_charater(MainCharater* mc){
    if(mc){

        free_basic_charater(mc->bc);
        free(mc);
    }
}