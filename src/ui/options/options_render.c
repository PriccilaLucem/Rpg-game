#include "options_render.h"
#include "../button/button.h"
#include "../../lang/language.h" 

// Add function declarations if they're not in headers
SDL_Texture* create_text_texture(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color);
void update_button_texture(Button* button, SDL_Renderer* renderer, TTF_Font* font);

void create_title_texture(Options* options, SDL_Renderer* renderer) {
    const char* title_text = get_text_from_key("options.title");
    if (!title_text) {
        title_text = "OPTIONS";
    }
    options->texture = create_text_texture(renderer, options->screen_title_font, title_text, (SDL_Color){255, 255, 255, 255});
}

void initialize_buttons_textures(Options* options) {
    Button* buttons[] = {
        options->screen_size_left_arrow, options->screen_size_right_arrow, options->screen_size,
        options->full_screen, options->vsync, options->sound, options->volume,
        options->antialiasing, options->music_volume, options->effects_volume,
        options->voice_volume, options->save, options->reset,
        options->back_to_main_menu, NULL
    };

    for (int i = 0; buttons[i] != NULL; i++) {
        update_button_texture(buttons[i], options->renderer, options->button_font);
    }
}

void update_all_buttons_textures(Options* options) {
    Button* buttons[] = {
        options->full_screen, options->vsync, options->sound, options->volume,
        options->antialiasing, options->music_volume, options->effects_volume,
        options->voice_volume, NULL
    };

    for (int i = 0; buttons[i] != NULL; i++) {
        update_button_texture(buttons[i], options->renderer, options->button_font);
    }
}

void render_title(Options* options, SDL_Renderer* renderer, int screen_width) {
    if (!options->texture) return;
    
    int textW, textH;
    SDL_QueryTexture(options->texture, NULL, NULL, &textW, &textH);
    
    SDL_Rect title_dest = {
        .x = (screen_width - textW) / 2,
        .y = 20,
        .w = textW,
        .h = textH
    };
    
    SDL_RenderCopy(renderer, options->texture, NULL, &title_dest);
}

void render_all_buttons(Options* options, SDL_Renderer* renderer) {
    Button* buttons[] = {
        options->screen_size_left_arrow, options->screen_size_right_arrow, options->screen_size,
        options->full_screen, options->vsync, options->sound, options->volume,
        options->antialiasing, options->music_volume, options->effects_volume,
        options->voice_volume, options->save, options->reset,
        options->back_to_main_menu, NULL
    };

    for (int i = 0; buttons[i] != NULL; i++) {
        render_button(buttons[i], renderer);
    }
}