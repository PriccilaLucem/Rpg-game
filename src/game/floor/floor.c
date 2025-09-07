#include "./floor.h"
#include "./floor.h"
#include "../../load_obj/load_obj.h"

SDL_Texture* create_white_tile(SDL_Renderer* renderer, int width, int height) {
    SDL_Texture* tex = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        width,
        height
    );

    if (!tex) {
        printf("Failed to create white tile: %s\n", SDL_GetError());
        return NULL;
    }

    // salva o alvo atual
    SDL_Texture* old_target = SDL_GetRenderTarget(renderer);

    // define a textura como alvo
    SDL_SetRenderTarget(renderer, tex);

    // preenche com branco opaco
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // restaura o alvo original
    SDL_SetRenderTarget(renderer, old_target);

    return tex;
}

Floor* init_floor_from_obj(SDL_Renderer* renderer, const char* path, int tile_width, int tile_height) {
    Floor* floor = malloc(sizeof(Floor));
    if (!floor) {
        printf("Error allocating floor memory\n");
        exit(EXIT_FAILURE);
    }

    OBJ_Model* model = OBJ_Load(path);
    if (!model) {
        printf("Failed to load OBJ: %s\n", path);
        free(floor);
        exit(EXIT_FAILURE);
    }

    SDL_Rect bounds = toRect(model);

    floor->width  = bounds.w / tile_width;
    floor->height = bounds.h / tile_height;

    floor->tiles = malloc(floor->width * sizeof(SDL_Texture**));
    for (int x = 0; x < floor->width; x++) {
        floor->tiles[x] = malloc(floor->height * sizeof(SDL_Texture*));
    }

    SDL_Texture* white_tile = create_white_tile(renderer, tile_width, tile_height);

    for (int x = 0; x < floor->width; x++) {
        for (int y = 0; y < floor->height; y++) {
            floor->tiles[x][y] = white_tile;
        }
    }
    floor->obj = model;
    
    return floor;
}

Floor* init_floor_with_white_tiles(SDL_Renderer* renderer, int width, int height, int tile_width, int tile_height) {
    Floor* floor = malloc(sizeof(Floor));
    if (!floor) {
        printf("Error allocating floor memory\n");
        exit(EXIT_FAILURE);
    }

    floor->width = width;
    floor->height = height;

    // aloca colunas
    floor->tiles = malloc(width * sizeof(SDL_Texture**));
    if (!floor->tiles) {
        printf("Error allocating floor columns\n");
        free(floor);
        exit(EXIT_FAILURE);
    }

    // cria textura branca padrão
    SDL_Texture* white_tile = create_white_tile(renderer, tile_width, tile_height);
    if (!white_tile) {
        free(floor->tiles);
        free(floor);
        exit(EXIT_FAILURE);
    }

    for (int x = 0; x < width; x++) {
        floor->tiles[x] = malloc(height * sizeof(SDL_Texture*));
        if (!floor->tiles[x]) {
            printf("Error allocating floor rows\n");
            for (int i = 0; i < x; i++) free(floor->tiles[i]);
            SDL_DestroyTexture(white_tile);
            free(floor->tiles);
            free(floor);
            exit(EXIT_FAILURE);
        }

        for (int y = 0; y < height; y++) {
            floor->tiles[x][y] = white_tile; // todos os tiles apontam para a mesma textura branca
        }
    }

    return floor;
}


void free_floor(Floor* floor) {
    if (!floor) return;

    if (floor->tiles) {
        for (int x = 0; x < floor->width; x++) {
            if (floor->tiles[x]) free(floor->tiles[x]);
        }
        free(floor->tiles);
    }

    // como todos os tiles apontam para a mesma textura, só precisa destruir 1 vez
    if (floor->width > 0 && floor->height > 0 && floor->tiles[0][0]) {
        SDL_DestroyTexture(floor->tiles[0][0]);
    }

    free(floor);
}


 
