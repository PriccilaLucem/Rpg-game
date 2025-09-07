#include "./floor.h"

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

    // Define como alvo de render
    SDL_SetRenderTarget(renderer, tex);

    // Preenche com branco
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Volta para renderizador padrão
    SDL_SetRenderTarget(renderer, NULL);

    return tex;
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


void render_floor(SDL_Renderer* renderer, Floor* floor, IsoCamera* cam, int start_x, int start_y, int tile_width, int tile_height) {
    for(int y = 0; y < floor->height; y++) {
        for(int x = 0; x < floor->width; x++) {
            if (!floor->tiles[x][y]) continue; // verifica se há textura

            int sx, sy;
            tile_to_screen(x, y, cam, tile_width, tile_height, &sx, &sy);

            SDL_Rect dst;
            dst.x = sx + start_x;  // deslocamento opcional
            dst.y = sy + start_y;
            dst.w = tile_width * cam->zoom;
            dst.h = tile_height * cam->zoom;

            SDL_RenderCopy(renderer, floor->tiles[x][y], NULL, &dst);
        }
    }
}




 
