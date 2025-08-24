#include "./options.h"
#include "../../states/states.h"
#include "../../config/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern SDL_Window* window;
extern Config* current_config;

/* ===== CONSTANTS AND GLOBALS ===== */
ScreenResolution available_resolutions[] = {
    {800, 600},
    {1280, 720},
    {1920, 1080},
};

int current_resolution_index = 0;
const int num_resolutions = sizeof(available_resolutions) / sizeof(available_resolutions[0]);

/* ===== PRIVATE FUNCTION DECLARATIONS ===== */
static void setup_button_geometry(Options* options, int screen_width, int screen_height);
static void create_title_texture(Options* options, SDL_Renderer* renderer);
static void initialize_buttons_textures(Options* options);
static void update_all_buttons_textures(Options* options);
static void handle_mouse_motion(Options* options, int mouse_x, int mouse_y);
static void handle_mouse_click(Options* options, int mouse_x, int mouse_y);
static void render_title(Options* options, SDL_Renderer* renderer, int screen_width);
static void render_all_buttons(Options* options, SDL_Renderer* renderer);

// Button handler functions
static void handle_fullscreen_toggle(Options* options);
static void handle_vsync_toggle(Options* options);
static void handle_sound_toggle(Options* options);
static void handle_volume_click(Options* options);
static void handle_antialiasing_click(Options* options);
static void handle_music_volume_click(Options* options);
static void handle_effects_volume_click(Options* options);
static void handle_voice_volume_click(Options* options);
static void handle_save_click(Options* options);
static void handle_load_click(Options* options);
static void handle_reset_click(Options* options);
static void handle_back_to_main_menu(Options* options);

/* ===== PUBLIC FUNCTION IMPLEMENTATIONS ===== */

SDL_Texture* create_text_texture(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color) {
    if (!renderer || !font || !text) {
        printf("Invalid parameters to create_text_texture\n");
        return NULL;
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

int find_current_resolution_index(int width, int height) {
    printf("Finding resolution index for %dx%d\n", width, height);
    
    for (int i = 0; i < num_resolutions; i++) {
        printf("Checking against available resolution %dx%d\n", 
               available_resolutions[i].width, available_resolutions[i].height);
        
        if (available_resolutions[i].width == width && available_resolutions[i].height == height) {
            return i;
        }
    }
    
    printf("Current resolution not found in available resolutions, defaulting to first option.\n");
    return 0;
}

Options* init_options(int width, int height, SDL_Renderer* renderer, int font_size) {
    Options* options = malloc(sizeof(Options));
    if (!options) {
        printf("Failed to allocate memory for Options\n");
        exit(EXIT_FAILURE);
    }

    // Initialize configuration
    options->config = load_config();
    current_config = options->config;
    options->renderer = renderer;

    // Load fonts
    options->screen_title_font = TTF_OpenFont(MENU_FONT_PATH, font_size * 2);
    options->button_font = TTF_OpenFont(MENU_FONT_PATH, font_size);
    
    if (!options->screen_title_font || !options->button_font) {
        printf("Options fonts not loading! Error: %s\n", TTF_GetError());
        free_options(options);
        exit(EXIT_FAILURE);
    }

    // Setup button geometry
    setup_button_geometry(options, width, height);
    
    // Create title texture
    create_title_texture(options, renderer);

    // Initialize button textures and states
    initialize_buttons_textures(options);
    current_resolution_index = find_current_resolution_index(
        options->config->screen_width, options->config->screen_height
    );
    
    update_screen_size_button_text(options, renderer);
    update_options(options);

    printf("Options initialized successfully with centered layout\n");
    return options;
}

void free_options(Options* options) {
    if (!options) return;

    // Free fonts
    if (options->button_font) TTF_CloseFont(options->button_font);
    if (options->screen_title_font) TTF_CloseFont(options->screen_title_font);

    // Free buttons
    Button* buttons[] = {
        options->screen_size_left_arrow, options->screen_size_right_arrow, options->screen_size,
        options->full_screen, options->vsync, options->sound, options->volume,
        options->antialiasing, options->music_volume, options->effects_volume,
        options->voice_volume, options->save, options->load, options->reset,
        options->back_to_main_menu, NULL
    };

    for (int i = 0; buttons[i] != NULL; i++) {
        free_button(buttons[i]);
    }

    // Free textures and config
    if (options->texture) SDL_DestroyTexture(options->texture);
    if (options->config) free(options->config);
    
    free(options);
}

void update_button_texture(Button* button, SDL_Renderer* renderer, TTF_Font* font) {
    if (!button || !renderer || !font) return;
    
    if (button->texture) {
        SDL_DestroyTexture(button->texture);
    }
    
    button->texture = create_text_texture(renderer, font, button->label, (SDL_Color){255, 255, 255, 255});
}

void update_options(Options* options) {
    if (!options || !options->config) return;

    // Update button labels
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

    // Update button textures
    update_all_buttons_textures(options);
}

void update_screen_size_button_text(Options* options, SDL_Renderer* renderer) {
    if (!options || !renderer) return;
    
    ScreenResolution res = available_resolutions[current_resolution_index];
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%dx%d", res.width, res.height);
    strncpy(options->screen_size->label, buffer, MAX_BUTTON_LENGTH);

    update_button_texture(options->screen_size, renderer, options->button_font);
}

void screen_size_left_arrow_onClick(void* data) {
    Options* options = (Options*)data;
    if (!options) return;
    
    current_resolution_index = (current_resolution_index - 1 + num_resolutions) % num_resolutions;
    update_screen_size_button_text(options, options->renderer);
    apply_resolution(options);
}

void screen_size_right_arrow_onClick(void* data) {
    Options* options = (Options*)data;
    if (!options) return;
    
    current_resolution_index = (current_resolution_index + 1) % num_resolutions;
    update_screen_size_button_text(options, options->renderer);
    apply_resolution(options);
}

void handle_options_input(SDL_Event* event, Options* options) {
    if (!options || !event) return;
    
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    switch (event->type) {
        case SDL_MOUSEMOTION:
            handle_mouse_motion(options, mouse_x, mouse_y);
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                handle_mouse_click(options, mouse_x, mouse_y);
            }
            break;
    }
}

void render_options(Options* options, SDL_Renderer* renderer, int screen_width) {
    if (!options || !renderer) return;
    
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render title
    render_title(options, renderer, screen_width);

    // Render all buttons
    render_all_buttons(options, renderer);

    SDL_RenderPresent(renderer);
}

void set_button_geometry(Button* button, int x, int y, int width, int height) {
    if (!button) return;
    button->x = x;
    button->y = y;
    button->width = width;
    button->height = height;
}

void update_button_geometry(Options* options, int screen_width, int screen_height) {
    if (!options) return;
    setup_button_geometry(options, screen_width, screen_height);
}

void apply_resolution(Options* options) {
    if (!options || !options->config) return;
    
    ScreenResolution res = available_resolutions[current_resolution_index];
    SDL_SetWindowSize(window, res.width, res.height);
    
    options->config->screen_width = res.width;
    options->config->screen_height = res.height;
    
    save_config(options->config);
    update_options(options);
    update_button_geometry(options, res.width, res.height);
}

/* ===== PRIVATE FUNCTION IMPLEMENTATIONS ===== */

static void setup_button_geometry(Options* options, int screen_width, int screen_height) {
    float scale_factor = (float)screen_height / 720.0f;
    
    // Calculate dimensions
    int button_height = (int)(60 * scale_factor);
    int left_column_width = (int)(350 * scale_factor);
    int right_column_width = (int)(280 * scale_factor);
    int padding_top_bottom = (int)(80 * scale_factor);
    int arrow_button_width = (int)(50 * scale_factor);
    int main_button_width = (int)(180 * scale_factor);
    int column_spacing = (int)(100 * scale_factor);

    // Calculate spacing
    int available_height = screen_height - (padding_top_bottom * 2);
    int spacing_y_left = (available_height - (9 * button_height)) / 10;
    int spacing_y_right = (available_height - (4 * button_height)) / 5;

    // Calculate positions
    int total_columns_width = left_column_width + right_column_width + column_spacing;
    int start_x = (screen_width - total_columns_width) / 2;

    int left_x = start_x;
    int right_x = start_x + left_column_width + column_spacing;
    int left_y = padding_top_bottom + spacing_y_left;
    int right_y = padding_top_bottom + spacing_y_right;

    // Left column buttons
    options->screen_size_left_arrow = init_button(left_x, left_y, arrow_button_width, button_height, "<", false, false, options->button_font);
    options->screen_size = init_button(left_x + arrow_button_width + 10, left_y, main_button_width, button_height, "1280x720", false, false, options->button_font);
    options->screen_size_right_arrow = init_button(left_x + arrow_button_width + main_button_width + 20, left_y, arrow_button_width, button_height, ">", false, false, options->button_font);

    left_y += button_height + spacing_y_left;
    options->full_screen = init_button(left_x, left_y, left_column_width, button_height, "FULL SCREEN: OFF", false, false, options->button_font);
    
    left_y += button_height + spacing_y_left;
    options->vsync = init_button(left_x, left_y, left_column_width, button_height, "VSYNC: OFF", false, false, options->button_font);
    
    left_y += button_height + spacing_y_left;
    options->sound = init_button(left_x, left_y, left_column_width, button_height, "SOUND: ON", false, false, options->button_font);
    
    left_y += button_height + spacing_y_left;
    options->volume = init_button(left_x, left_y, left_column_width, button_height, "VOLUME: 100", false, false, options->button_font);
    
    left_y += button_height + spacing_y_left;
    options->antialiasing = init_button(left_x, left_y, left_column_width, button_height, "ANTIALIASING: ON", false, false, options->button_font);
    
    left_y += button_height + spacing_y_left;
    options->music_volume = init_button(left_x, left_y, left_column_width, button_height, "MUSIC VOLUME: 0", false, false, options->button_font);
    
    left_y += button_height + spacing_y_left;
    options->effects_volume = init_button(left_x, left_y, left_column_width, button_height, "EFFECTS VOLUME: 70", false, false, options->button_font);
    
    left_y += button_height + spacing_y_left;
    options->voice_volume = init_button(left_x, left_y, left_column_width, button_height, "VOICE VOLUME: 75", false, false, options->button_font);

    // Right column buttons
    options->save = init_button(right_x, right_y, right_column_width, button_height, "SAVE", false, false, options->button_font);
    right_y += button_height + spacing_y_right;
    
    options->load = init_button(right_x, right_y, right_column_width, button_height, "LOAD", false, false, options->button_font);
    right_y += button_height + spacing_y_right;
    
    options->reset = init_button(right_x, right_y, right_column_width, button_height, "RESET TO DEFAULT", false, false, options->button_font);
    right_y += button_height + spacing_y_right;
    
    options->back_to_main_menu = init_button(right_x, right_y, right_column_width, button_height, "BACK TO MAIN MENU", false, false, options->button_font);
}

static void create_title_texture(Options* options, SDL_Renderer* renderer) {
    options->texture = create_text_texture(renderer, options->screen_title_font, "Options!", (SDL_Color){255, 255, 255, 255});
}

static void initialize_buttons_textures(Options* options) {
    Button* buttons[] = {
        options->screen_size_left_arrow, options->screen_size_right_arrow, options->screen_size,
        options->full_screen, options->vsync, options->sound, options->volume,
        options->antialiasing, options->music_volume, options->effects_volume,
        options->voice_volume, options->save, options->load, options->reset,
        options->back_to_main_menu, NULL
    };

    for (int i = 0; buttons[i] != NULL; i++) {
        update_button_texture(buttons[i], options->renderer, options->button_font);
    }
}

static void update_all_buttons_textures(Options* options) {
    Button* buttons[] = {
        options->full_screen, options->vsync, options->sound, options->volume,
        options->antialiasing, options->music_volume, options->effects_volume,
        options->voice_volume, NULL
    };

    for (int i = 0; buttons[i] != NULL; i++) {
        update_button_texture(buttons[i], options->renderer, options->button_font);
    }
}

static void handle_mouse_motion(Options* options, int mouse_x, int mouse_y) {
    Button* buttons[] = {
        options->screen_size_left_arrow, options->screen_size_right_arrow, options->screen_size,
        options->full_screen, options->vsync, options->sound, options->volume,
        options->antialiasing, options->music_volume, options->effects_volume,
        options->voice_volume, options->save, options->load, options->reset,
        options->back_to_main_menu, NULL
    };

    for (int i = 0; buttons[i] != NULL; i++) {
        check_button_hover(buttons[i], mouse_x, mouse_y);
    }
}

static void handle_mouse_click(Options* options, int mouse_x, int mouse_y) {
    // Handle resolution buttons
    if (check_button_click(options->screen_size_left_arrow, mouse_x, mouse_y)) {
        screen_size_left_arrow_onClick(options);
        return;
    }
    if (check_button_click(options->screen_size_right_arrow, mouse_x, mouse_y)) {
        screen_size_right_arrow_onClick(options);
        return;
    }

    // Handle configuration buttons
    if (check_button_click(options->full_screen, mouse_x, mouse_y)) {
        handle_fullscreen_toggle(options);
    }
    else if (check_button_click(options->vsync, mouse_x, mouse_y)) {
        handle_vsync_toggle(options);
    }
    else if (check_button_click(options->sound, mouse_x, mouse_y)) {
        handle_sound_toggle(options);
    }
    else if (check_button_click(options->volume, mouse_x, mouse_y)) {
        handle_volume_click(options);
    }
    else if (check_button_click(options->antialiasing, mouse_x, mouse_y)) {
        handle_antialiasing_click(options);
    }
    else if (check_button_click(options->music_volume, mouse_x, mouse_y)) {
        handle_music_volume_click(options);
    }
    else if (check_button_click(options->effects_volume, mouse_x, mouse_y)) {
        handle_effects_volume_click(options);
    }
    else if (check_button_click(options->voice_volume, mouse_x, mouse_y)) {
        handle_voice_volume_click(options);
    }
    else if (check_button_click(options->save, mouse_x, mouse_y)) {
        handle_save_click(options);
    }
    else if (check_button_click(options->load, mouse_x, mouse_y)) {
        handle_load_click(options);
    }
    else if (check_button_click(options->reset, mouse_x, mouse_y)) {
        handle_reset_click(options);
    }
    else if (check_button_click(options->back_to_main_menu, mouse_x, mouse_y)) {
        handle_back_to_main_menu(options);
    }
}

static void render_title(Options* options, SDL_Renderer* renderer, int screen_width) {
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

static void render_all_buttons(Options* options, SDL_Renderer* renderer) {
    Button* buttons[] = {
        options->screen_size_left_arrow, options->screen_size_right_arrow, options->screen_size,
        options->full_screen, options->vsync, options->sound, options->volume,
        options->antialiasing, options->music_volume, options->effects_volume,
        options->voice_volume, options->save, options->load, options->reset,
        options->back_to_main_menu, NULL
    };

    for (int i = 0; buttons[i] != NULL; i++) {
        render_button(buttons[i], renderer);
    }
}

/* ===== BUTTON HANDLER FUNCTIONS ===== */

static void handle_fullscreen_toggle(Options* options) {
    options->config->fullscreen = !options->config->fullscreen;
    SDL_SetWindowFullscreen(window, options->config->fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
    save_config(options->config);
    update_options(options);
}

static void handle_vsync_toggle(Options* options) {
    options->config->vsync = !options->config->vsync;
    save_config(options->config);
    update_options(options);
}

static void handle_sound_toggle(Options* options) {
    options->config->sound_enabled = !options->config->sound_enabled;
    save_config(options->config);
    update_options(options);
}

static void handle_volume_click(Options* options) {
    options->config->volume_level = (options->config->volume_level + 10) % 110;
    if (options->config->volume_level == 0) options->config->volume_level = 10;
    save_config(options->config);
    update_options(options);
}

static void handle_antialiasing_click(Options* options) {
    if (options->config->antialiasing == 0) options->config->antialiasing = 2;
    else if (options->config->antialiasing == 2) options->config->antialiasing = 4;
    else if (options->config->antialiasing == 4) options->config->antialiasing = 8;
    else options->config->antialiasing = 0;
    save_config(options->config);
    update_options(options);
}

static void handle_music_volume_click(Options* options) {
    options->config->music_volume = (options->config->music_volume + 10) % 110;
    if (options->config->music_volume == 0) options->config->music_volume = 10;
    save_config(options->config);
    update_options(options);
}

static void handle_effects_volume_click(Options* options) {
    options->config->effects_volume = (options->config->effects_volume + 10) % 110;
    if (options->config->effects_volume == 0) options->config->effects_volume = 10;
    save_config(options->config);
    update_options(options);
}

static void handle_voice_volume_click(Options* options) {
    options->config->voice_volume = (options->config->voice_volume + 10) % 110;
    if (options->config->voice_volume == 0) options->config->voice_volume = 10;
    save_config(options->config);
    update_options(options);
}

static void handle_save_click(Options* options) {
    save_config(options->config);
}

static void handle_load_click(Options* options) {
    Config* loaded = load_config();
    if (loaded) {
        *options->config = *loaded;
        free(loaded);
        update_options(options);
    }
}

static void handle_reset_click(Options* options) {
    reset_config_to_defaults(options->config);
    save_config(options->config);
    update_options(options);
}

static void handle_back_to_main_menu(Options* options) {
    change_state(STATE_MAIN_MENU);
}