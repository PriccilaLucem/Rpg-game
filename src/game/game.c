    #include "./game.h"


    Game* init_game(int screen_width, int screen_height, SDL_Renderer* renderer, int font_size){
        Game* game = malloc(sizeof(Game));
        game->font = TTF_OpenFont(MENU_FONT_PATH, font_size);
        game->main_character = NULL;
        game->InitGame.char_build = init_char_build();
        game->game_enum = INITIAL_SCREEN;
        return game;
    }

    void render_game(Game* game, SDL_Renderer* renderer){
        if(game->game_enum == INITIAL_SCREEN){
            render_char_build(game->InitGame.char_build, renderer);
        }
        else if (game->game_enum == GAME_SCREEN)
        {
            SDL_Color background_color = {0, 0, 0, 255};
            SDL_RenderClear(renderer);
        }
        
    }

    void handle_on_click(Game* data){
        Game* game = (Game*) data;
        game->main_character = init_basic_character_as_main(game->InitGame.char_build->input_field->text, "Uma descricao momentanea", MAIN_CHARCATHER_OBJ)->character_type.main_character;
        printf("%s", game->InitGame.char_build->input_field->text);
        game->game_enum = GAME_SCREEN;
    }

    void handle_game_events(Game* game, SDL_Event* event){
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        switch (game->game_enum){
            case INITIAL_SCREEN:
            switch (event->type) {
                case SDL_MOUSEMOTION:
                check_button_hover(game->InitGame.char_build->button, mouse_x, mouse_y);
                break;
                
                case SDL_MOUSEBUTTONDOWN:
                if (event->button.button == SDL_BUTTON_LEFT) {
                    handle_on_click(game);
                }
                break;
            }
            break;
            case GAME_SCREEN:
                printf("Entering game screen!");
                break;
        }
    }

    void free_game(Game* game){
        if(game->font) TTF_CloseFont(game->font);
        if(game->main_character) free_main_character(game->main_character);
        if(game->font) TTF_CloseFont(game->font);
        if(game->renderer) SDL_RenderClear(game->renderer);
        free(game);
    }