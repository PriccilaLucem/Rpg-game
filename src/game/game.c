#include "./game.h"

Game* init_game(int screen_width, int screen_height, SDL_Renderer* renderer, int font_size){
    Game* game = malloc(sizeof(Game));
    game->font = TTF_OpenFont(MENU_FONT_PATH, font_size);
    game->main_character = NULL;
    game->InitGame.char_build = init_char_build();
    game->game_enum = INITIAL_SCREEN;
}

void render_game(Game* game, SDL_Renderer* renderer){
    if(game->game_enum == INITIAL_SCREEN){
        render_char_build(game->InitGame.char_build, renderer);
    }
    else if (game->game_enum == GAME_SCREEN)
    {
        // TODO
    }
    
}

void handle_game_events(Game* game, SDL_Event* event){
    if(game->game_enum == INITIAL_SCREEN){
        handle_input_event(game->InitGame.char_build->input_field, event, game->renderer);
    }
}

void free_game(Game* game){
    if(game->font) TTF_CloseFont(game->font);
    if(game->main_character) free_main_character(game->main_character);
    if(game->font) TTF_CloseFont(game->font);
    if(game->renderer) SDL_RenderClear(game->renderer);
    free(game);
}