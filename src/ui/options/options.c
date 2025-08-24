#include "./options.h"
#include "../../states/states.h"
#include "../../config/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern SDL_Window* window;
extern Config* current_config;

ScreenResolution available_resolutions[] = {
    {800, 600},
    {1280, 720},
    {1920, 1080},
};
int current_resolution_index = 0;
int num_resolutions = sizeof(available_resolutions)/sizeof(available_resolutions[0]);

int find_current_resolution_index(int w, int h) {
    printf("Finding resolution index for %dx%d\n", w, h);
    for(int i = 0; i < num_resolutions; i++) {
        printf("Checking against available resolution %dx%d\n", available_resolutions[i].width, available_resolutions[i].height);
        if(available_resolutions[i].width == w && available_resolutions[i].height == h)
            return i;
    }
    printf("Current resolution not found in available resolutions, defaulting to first option.\n");
    return 0; 
}

Options* init_options(int x, int y, int width, int height, SDL_Renderer* renderer) {
    Options* options = malloc(sizeof(Options));
    if (!options){
        printf("Failed to allocate memory for Options\n");
        exit(EXIT_FAILURE);
    } 

    options->config = load_config();
    current_config = options->config;

    options->font = TTF_OpenFont(MENU_FONT_PATH, 24);
    if (!options->font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        free(options);
        exit(EXIT_FAILURE);
    }

    options->renderer = renderer;

    int current_x = x + 100;   // Posição inicial X
    int current_y = y + 100;   // Posição inicial Y
    int spacing_y = 70;        // Espaçamento vertical entre botões

    options->screen_size_left_arrow  = init_button(current_x, current_y, 50, 50, "<", false, false, options->font);
    options->screen_size             = init_button(current_x + 60, current_y, 130, 50, "800x600", false, false, options->font);
    options->screen_size_right_arrow = init_button(current_x + 200, current_y, 50, 50, ">", false, false, options->font);

    current_y += spacing_y;

    options->full_screen   = init_button(current_x, current_y, 250, 50, "Full Screen: OFF", false, false, options->font);
    current_y += spacing_y;

    options->vsync         = init_button(current_x, current_y, 250, 50, "VSync: OFF", false, false, options->font);
    current_y += spacing_y;

    options->sound         = init_button(current_x, current_y, 250, 50, "Sound: ON", false, false, options->font);
    current_y += spacing_y;

    options->volume        = init_button(current_x, current_y, 250, 50, "Volume: 100", false, false, options->font);
    current_y += spacing_y;

    options->antialiasing  = init_button(current_x, current_y, 250, 50, "Antialiasing: OFF", false, false, options->font);
    current_y += spacing_y;

    options->music_volume  = init_button(current_x, current_y, 250, 50, "Music Volume: 100", false, false, options->font);
    current_y += spacing_y;

    options->effects_volume= init_button(current_x, current_y, 250, 50, "Effects Volume: 100", false, false, options->font);
    current_y += spacing_y;

    options->voice_volume  = init_button(current_x, current_y, 250, 50, "Voice Volume: 100", false, false, options->font);

    int right_x = x + 400;
    int right_y = y + 100;

    options->save             = init_button(right_x, right_y, 200, 50, "Save", false, false, options->font);
    right_y += spacing_y;

    options->load             = init_button(right_x, right_y, 200, 50, "Load", false, false, options->font);
    right_y += spacing_y;

    options->reset            = init_button(right_x, right_y, 200, 50, "Reset to Default", false, false, options->font);
    right_y += spacing_y;

    options->back_to_main_menu= init_button(right_x, right_y, 200, 50, "Back to Main Menu", false, false, options->font);

    
    options->screen_title = "Options";
    
    if (!options->screen_size_left_arrow || !options->screen_size_right_arrow || !options->screen_size ||
        !options->full_screen || !options->vsync || !options->sound || !options->volume ||
        !options->antialiasing || !options->music_volume || !options->effects_volume ||
        !options->voice_volume || !options->save || !options->load || !options->reset ||
        !options->back_to_main_menu) {
        free_options(options);
        printf("Failed to initialize all buttons\n");
        exit(EXIT_FAILURE);
        printf("Initializing options\n");
        }
    options->screen_size->texture = create_text_texture(options->renderer, options->font, options->screen_size->label, (SDL_Color){255,255,255,255});    
    current_resolution_index = find_current_resolution_index(options->config->screen_width, options->config->screen_height);
    printf("CONFIG WIDTH");
    update_screen_size_button_text(options, options->renderer);

    update_options(options);
    printf("Options initialized successfully\n");
    return options;
}

// Libera memória das opções
void free_options(Options* options) {
    if (!options) return;

    if (options->font) TTF_CloseFont(options->font);
    free_button(options->screen_size_left_arrow);
    free_button(options->screen_size_right_arrow);
    free_button(options->screen_size);
    free_button(options->full_screen);
    free_button(options->vsync);
    free_button(options->sound);
    free_button(options->volume);
    free_button(options->antialiasing);
    free_button(options->music_volume);
    free_button(options->effects_volume);
    free_button(options->voice_volume);
    free_button(options->save);
    free_button(options->load);
    free_button(options->reset);
    free_button(options->back_to_main_menu);

    if (options->config) free(options->config);
    free(options);
}

// Atualiza o texto dos botões
void update_options(Options* options) {
    if (!options || !options->config) return;
    char buffer[50];

    snprintf(buffer, sizeof(buffer), "Full Screen: %s", options->config->fullscreen ? "ON" : "OFF");
    strncpy(options->full_screen->label, buffer, MAX_BUTTON_LENGTH);

    snprintf(buffer, sizeof(buffer), "VSync: %s", options->config->vsync ? "ON" : "OFF");
    strncpy(options->vsync->label, buffer, MAX_BUTTON_LENGTH);

    snprintf(buffer, sizeof(buffer), "Sound: %s", options->config->sound_enabled ? "ON" : "OFF");
    strncpy(options->sound->label, buffer, MAX_BUTTON_LENGTH);

    snprintf(buffer, sizeof(buffer), "Volume: %d", options->config->volume_level);
    strncpy(options->volume->label, buffer, MAX_BUTTON_LENGTH);

    snprintf(buffer, sizeof(buffer), "Antialiasing: %s", options->config->antialiasing ? "ON" : "OFF");
    strncpy(options->antialiasing->label, buffer, MAX_BUTTON_LENGTH);

    snprintf(buffer, sizeof(buffer), "Music Volume: %d", options->config->music_volume);
    strncpy(options->music_volume->label, buffer, MAX_BUTTON_LENGTH);

    snprintf(buffer, sizeof(buffer), "Effects Volume: %d", options->config->effects_volume);
    strncpy(options->effects_volume->label, buffer, MAX_BUTTON_LENGTH);

    snprintf(buffer, sizeof(buffer), "Voice Volume: %d", options->config->voice_volume);
    strncpy(options->voice_volume->label, buffer, MAX_BUTTON_LENGTH);

    snprintf(buffer, sizeof(buffer), "%dx%d", available_resolutions[current_resolution_index].width, available_resolutions[current_resolution_index].height);
    strncpy(options->screen_size->label, buffer, MAX_BUTTON_LENGTH);
}

// Atualiza botão de resolução
void update_screen_size_button_text(Options* options, SDL_Renderer* renderer) {

    if (!options || !renderer) return;
    ScreenResolution res = available_resolutions[current_resolution_index];
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%dx%d", res.width, res.height);
    strncpy(options->screen_size->label, buffer, MAX_BUTTON_LENGTH);

    if (options->screen_size->texture) SDL_DestroyTexture(options->screen_size->texture);
    options->screen_size->texture = create_text_texture(renderer, options->font, options->screen_size->label, (SDL_Color){255,255,255,255});
}

// Callbacks de resolução
void screen_size_left_arrow_onClick(void* data) {
    Options* options = (Options*)data;
    if (!options) return;
    current_resolution_index = (current_resolution_index - 1 + num_resolutions) % num_resolutions;
    update_screen_size_button_text(options, options->renderer);

    ScreenResolution res = available_resolutions[current_resolution_index];
    SDL_SetWindowSize(window, res.width, res.height);
    options->config->screen_width = res.width;
    options->config->screen_height = res.height;
    save_config(options->config);
}

void screen_size_right_arrow_onClick(void* data) {
    Options* options = (Options*)data;
    if (!options) return;
    current_resolution_index = (current_resolution_index + 1) % num_resolutions;
    update_screen_size_button_text(options, options->renderer);

    ScreenResolution res = available_resolutions[current_resolution_index];
    SDL_SetWindowSize(window, res.width, res.height);
    save_config(options->config);
}

// Input do menu de opções
void handle_options_input(SDL_Event* event, Options* options) {
    if (!options || !event) return;
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    switch(event->type) {
        case SDL_MOUSEMOTION:
            check_button_hover(options->screen_size_left_arrow, mouse_x, mouse_y);
            check_button_hover(options->screen_size_right_arrow, mouse_x, mouse_y);
            check_button_hover(options->screen_size, mouse_x, mouse_y);
            check_button_hover(options->full_screen, mouse_x, mouse_y);
            check_button_hover(options->vsync, mouse_x, mouse_y);
            check_button_hover(options->sound, mouse_x, mouse_y);
            check_button_hover(options->volume, mouse_x, mouse_y);
            check_button_hover(options->antialiasing, mouse_x, mouse_y);
            check_button_hover(options->music_volume, mouse_x, mouse_y);
            check_button_hover(options->effects_volume, mouse_x, mouse_y);
            check_button_hover(options->voice_volume, mouse_x, mouse_y);
            check_button_hover(options->save, mouse_x, mouse_y);
            check_button_hover(options->load, mouse_x, mouse_y);
            check_button_hover(options->reset, mouse_x, mouse_y);
            check_button_hover(options->back_to_main_menu, mouse_x, mouse_y);
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                if (check_button_click(options->screen_size_left_arrow, mouse_x, mouse_y))
                    screen_size_left_arrow_onClick(options);
                else if (check_button_click(options->screen_size_right_arrow, mouse_x, mouse_y))
                    screen_size_right_arrow_onClick(options);
                else if (check_button_click(options->full_screen, mouse_x, mouse_y)) {
                    options->config->fullscreen = !options->config->fullscreen;
                    SDL_SetWindowFullscreen(window, options->config->fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
                    save_config(options->config);
                    update_options(options);
                }
                else if (check_button_click(options->vsync, mouse_x, mouse_y)) {
                    options->config->vsync = !options->config->vsync;
                    save_config(options->config);
                    update_options(options);
                }
                else if (check_button_click(options->sound, mouse_x, mouse_y)) {
                    options->config->sound_enabled = !options->config->sound_enabled;
                    save_config(options->config);
                    update_options(options);
                }
                else if (check_button_click(options->volume, mouse_x, mouse_y)) {
                    options->config->volume_level = (options->config->volume_level + 10) % 110;
                    if(options->config->volume_level == 0) options->config->volume_level = 10;
                    save_config(options->config);
                    update_options(options);
                }
                else if (check_button_click(options->antialiasing, mouse_x, mouse_y)) {
                    if(options->config->antialiasing == 0) options->config->antialiasing = 2;
                    else if(options->config->antialiasing == 2) options->config->antialiasing = 4;
                    else if(options->config->antialiasing == 4) options->config->antialiasing = 8;
                    else options->config->antialiasing = 0;
                    save_config(options->config);
                    update_options(options);
                }
                else if (check_button_click(options->music_volume, mouse_x, mouse_y)) {
                    options->config->music_volume = (options->config->music_volume + 10) % 110;
                    if(options->config->music_volume == 0) options->config->music_volume = 10;
                    save_config(options->config);
                    update_options(options);
                }
                else if (check_button_click(options->effects_volume, mouse_x, mouse_y)) {
                    options->config->effects_volume = (options->config->effects_volume + 10) % 110;
                    if(options->config->effects_volume == 0) options->config->effects_volume = 10;
                    save_config(options->config);
                    update_options(options);
                }
                else if (check_button_click(options->voice_volume, mouse_x, mouse_y)) {
                    options->config->voice_volume = (options->config->voice_volume + 10) % 110;
                    if(options->config->voice_volume == 0) options->config->voice_volume = 10;
                    save_config(options->config);
                    update_options(options);
                }
                else if (check_button_click(options->save, mouse_x, mouse_y))
                    save_config(options->config);
                else if (check_button_click(options->load, mouse_x, mouse_y)) {
                    Config* loaded = load_config();
                    if(loaded) {
                        *options->config = *loaded;
                        free(loaded);
                        update_options(options);
                    }
                }
                else if (check_button_click(options->reset, mouse_x, mouse_y)) {
                    reset_config_to_defaults(options->config);
                    save_config(options->config);
                    update_options(options);
                }
                else if (check_button_click(options->back_to_main_menu, mouse_x, mouse_y)) {
                    change_state(STATE_MAIN_MENU);
                }
            }
            break;
    }
}


void render_options(Options* options, SDL_Renderer* renderer) {
    if (!options || !renderer) return;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Renderiza botões
    render_button(options->screen_size_left_arrow, renderer);
    render_button(options->screen_size_right_arrow, renderer);
    render_button(options->screen_size, renderer);
    render_button(options->full_screen, renderer);
    render_button(options->vsync, renderer);
    render_button(options->sound, renderer);
    render_button(options->volume, renderer);
    render_button(options->antialiasing, renderer);
    render_button(options->music_volume, renderer);
    render_button(options->effects_volume, renderer);
    render_button(options->voice_volume, renderer);
    render_button(options->save, renderer);
    render_button(options->load, renderer);
    render_button(options->reset, renderer);
    render_button(options->back_to_main_menu, renderer);

    SDL_RenderPresent(renderer);
}
void apply_resolution(Options* options) {
    if (!options || !options->config) return;
    ScreenResolution res = available_resolutions[current_resolution_index];
    SDL_SetWindowSize(window, res.width, res.height);
    options->config->screen_width = res.width;
    options->config->screen_height = res.height;
    save_config(options->config);
    update_options(options);
}

SDL_Texture* create_text_texture(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color) {
    if (!renderer || !font || !text){
        printf("Invalid parameters to create_text_texture\n");
        exit(EXIT_FAILURE);
    }

    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    if (!surface) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        printf("Failed to create text texture: %s\n", SDL_GetError());
        return NULL;
    }

    return texture;
}

