#include "./game.h"

static void handle_input_char_build(Game* game, SDL_Event* event);
static void handle_on_click(Game* game);

Game* init_game(int screen_width, int screen_height, SDL_Renderer* renderer, int font_size) {
    Game* game = malloc(sizeof(Game));
    if (!game) return NULL;

    game->font = TTF_OpenFont(MENU_FONT_PATH, font_size);
    game->main_charater = NULL;
    game->char_build = init_char_build();
    game->floor = init_floor_from_obj(renderer, "assets/floor/floor.obj", 100, 30);
    game->game_enum = INITIAL_SCREEN;
    game->renderer = renderer;

    return game;
}

void render_game(Game* game, SDL_Renderer* renderer) {
    switch (game->game_enum) {
        case INITIAL_SCREEN:
            render_char_build(game->char_build, renderer);
            break;
        case GAME_SCREEN:
            if (game->main_charater)
                render_initial_game(renderer, game->main_charater, game->floor);
            break;
        default:
            exit(0);
    }
}

void handle_game_events(Game* game, SDL_Event* event) {
    switch (game->game_enum) {
        case INITIAL_SCREEN:
            handle_input_char_build(game, event);
            break;
        case GAME_SCREEN:
            // eventos do jogo aqui
            break;
    }
}

static void handle_input_char_build(Game* game, SDL_Event* event) {
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    switch (event->type) {
        case SDL_MOUSEMOTION:
            check_button_hover(game->char_build->button, mouse_x, mouse_y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                handle_on_click(game);
            }
            break;
    }
}

static void handle_on_click(Game* game) {
    if (game->main_charater) 
        free_main_charater(game->main_charater);

    game->main_charater = init_main_charater(
        10, 10,
        game->char_build->input_field->text,
        "Uma descricao momentanea",
        MAIN_CHARCATHER_OBJ
    );
    game->game_enum = GAME_SCREEN;
}

void free_game(Game* game) {
    if (game->font) TTF_CloseFont(game->font);
    if (game->main_charater) free_main_charater(game->main_charater);

    if (game->floor) {
        free_floor(game->floor);
    }

    free(game);
}
