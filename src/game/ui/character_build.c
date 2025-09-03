#include "./character_build.h"

static void handle_on_click(void* data);

CharacterBuild* init_char_build(){
    CharacterBuild* char_build = malloc(sizeof(CharacterBuild));
    int font_size = 20;
    
    TTF_Font* font = TTF_OpenFont(MENU_FONT_PATH, font_size);
    TTF_Font* title_font = TTF_OpenFont(MENU_FONT_PATH, font_size*2);
    
    char_build->title_font = title_font;


    char_build->input_field = init_input_field(100, 100, 200, 40, font, (SDL_Color){0,0,0,255});
    char_build->button = init_button(100, 150, 200, 40, "Cofirme o nome", false, false, font);
    char_build->button->onClick = handle_on_click;
    strncpy(char_build->title, "Crie seu personagem!", MAX_DESCRIPTION_LENGTH);
    return char_build;
}

void handle_input_char_build(CharacterBuild* char_build, SDL_Renderer* renderer, SDL_Event* event) {
    if (!char_build || !event) return;

    InputField* input = char_build->input_field;

    if (event->type == SDL_TEXTINPUT) {
        strcat(input->text, event->text.text);
    } else if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_BACKSPACE && strlen(input->text) > 0) {
            input->text[strlen(input->text) - 1] = '\0';
        }
    }

    if (input->texture) {
        SDL_DestroyTexture(input->texture);
    }
    SDL_Color text_color = {0, 0, 0, 255};

    SDL_Surface* input_surface = TTF_RenderText_Solid(input->font, input->text, text_color);
    input->texture = SDL_CreateTextureFromSurface(renderer, input_surface);
    SDL_FreeSurface(input_surface);
}

void render_char_build(CharacterBuild* char_build, SDL_Renderer* renderer) {
    if (!char_build) return;

    SDL_Color title_color = {0, 0, 0, 255};
    SDL_Surface* title_surface = TTF_RenderText_Solid(char_build->title_font, char_build->title, title_color);
    SDL_Texture* title_texture = SDL_CreateTextureFromSurface(renderer, title_surface);

    SDL_Rect title_rect = {100, 30, title_surface->w, title_surface->h};
    SDL_RenderCopy(renderer, title_texture, NULL, &title_rect);

    SDL_FreeSurface(title_surface);
    SDL_DestroyTexture(title_texture);

    render_input_field(char_build->input_field, renderer);
    render_button(char_build->button, renderer);
}

static void handle_on_click(void* data){
    //todo
}


void free_char_build(CharacterBuild* char_build) {
    if (!char_build) return;

    if (char_build->title_font) {
        TTF_CloseFont(char_build->title_font);
    }
    if (char_build->input_field) {
        free_input_field(char_build->input_field);
    }
    if (char_build->button) {
        free_button(char_build->button);
    }
    free(char_build);
}