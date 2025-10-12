#include "options.h"

void render_title(Options* options, SDL_Renderer* renderer, int screen_width) {
    if (!options || !renderer || !options->texture) return;
    
    int texture_width, texture_height;
    SDL_QueryTexture(options->texture, NULL, NULL, &texture_width, &texture_height);
    
    // Get screen height for responsive positioning
    int screen_height;
    SDL_GetRendererOutputSize(renderer, NULL, &screen_height);
    float scale = (float)screen_height / 720.0f;
    
    SDL_Rect dest_rect = {
        (screen_width - texture_width) / 2,
        (int)(50 * scale),
        texture_width,
        texture_height
    };
    
    SDL_RenderCopy(renderer, options->texture, NULL, &dest_rect);
}

void render_section_label(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    if (!renderer || !font || !text) return;
    
    SDL_Color gray = {180, 180, 180, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, gray);
    if (surface) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture) {
            SDL_Rect rect = {x, y, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, NULL, &rect);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(surface);
    }
}

void render_all_buttons(Options* options, SDL_Renderer* renderer) {
    if (!options || !renderer) return;
    
    // Responsive section labels
    if (options->button_font) {
        int window_width = 800, window_height = 600;
        SDL_GetRendererOutputSize(renderer, &window_width, &window_height);
        
        float scale = (float)window_height / 720.0f;
        int center_x = window_width / 2;
        int label_y = (int)(95 * scale);
        int label_spacing = (int)(140 * scale);
        
        render_section_label(renderer, options->button_font, "DISPLAY", center_x - 30, label_y);
        render_section_label(renderer, options->button_font, "VIDEO", center_x - 25, label_y + label_spacing);
        render_section_label(renderer, options->button_font, "AUDIO", center_x - 25, label_y + label_spacing * 2);
        render_section_label(renderer, options->button_font, "ACTIONS", center_x - 35, label_y + (int)(label_spacing * 3.4));
    }
    
    // Render buttons (excluding removed arrow buttons)
    Button* buttons[] = {
        options->full_screen, options->vsync, options->sound, options->volume,
        options->antialiasing, options->music_volume, options->effects_volume,
        options->voice_volume, options->save, options->reset,
        options->back_to_main_menu, NULL
    };
    
    for (int i = 0; buttons[i] != NULL; i++) {
        render_button(buttons[i], renderer);
    }
}

void create_title_texture(Options* options, SDL_Renderer* renderer) {
    if (!options || !renderer || !options->screen_title_font) return;
    
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(options->screen_title_font, "OPTIONS", white);
    
    if (surface) {
        options->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}

void initialize_buttons_textures(Options* options) {
    if (!options || !options->renderer || !options->button_font) return;
    
    Button* buttons[] = {
        options->full_screen, options->vsync, options->sound, options->volume,
        options->antialiasing, options->music_volume, options->effects_volume,
        options->voice_volume, options->save, options->reset,
        options->back_to_main_menu, NULL
    };
    
    for (int i = 0; buttons[i] != NULL; i++) {
        if (buttons[i]) {
            update_button_texture(buttons[i], options->renderer, options->button_font);
        }
    }
}

void update_all_buttons_textures(Options* options) {
    initialize_buttons_textures(options);
}