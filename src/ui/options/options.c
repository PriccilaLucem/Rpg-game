#include "options.h"
#include "options_geometry.h"
#include "options_handlers.h"
#include "options_render.h"
#include "../../lang/language.h"
#include "../../states/states.h"
#include "../../config/config.h"
#include "../../screen/screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern SDL_Window* window;
extern InitialScreen* screen;

/* ===== CONSTANTS AND GLOBALS ===== */
ScreenResolution available_resolutions[] = {
    {800, 600},
    {1280, 720},
    {1920, 1080},
};

LanguageOption available_languages[] = {
    {"pt", "Português"},
    {"en", "English"},
};

int current_language_index = 0;
int num_languages = sizeof(available_languages) / sizeof(available_languages[0]);

const char* available_language_codes[] = {
    "en",
    "pt"
};

const char* resolution_labels[] = {
    "800x600",
    "1280x720",
    "1920x1080",
};

int is_valid_language_code(const char* lang_code) {
    if (lang_code == NULL) return false;

    size_t num_codes = sizeof(available_language_codes) / sizeof(available_language_codes[0]);
    for (size_t i = 0; i < num_codes; i++) {
        if (strcmp(lang_code, available_language_codes[i]) == 0) {
            return 1; 
        }
    }
    return 0; 
}

int current_resolution_index = 0;
const int num_resolutions = sizeof(available_resolutions) / sizeof(available_resolutions[0]);

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
static void update_screen_size_button_text(Options* options, SDL_Renderer* renderer) {
    if (!options || !options->resolution_dropdown || !renderer) return;
    
    ScreenResolution res = available_resolutions[current_resolution_index];
    snprintf(options->resolution_dropdown->text, MAX_INPUT_LENGTH, "%dx%d", res.width, res.height);
    
    // Update the dropdown button texture
    if (options->resolution_dropdown->texture) {
        SDL_DestroyTexture(options->resolution_dropdown->texture);
        options->resolution_dropdown->texture = NULL;
    }
    
    options->resolution_dropdown->texture = create_text_texture(
        renderer,
        options->button_font,
        options->resolution_dropdown->text,
        (SDL_Color){255, 255, 255, 255}
    );
}

Options* init_options(int width, int height, SDL_Renderer* renderer, int font_size) {
    Options* options = malloc(sizeof(Options));
    if (!options) {
        printf("Failed to allocate memory for Options\n");
        exit(EXIT_FAILURE);
    }
    if (!load_language("pt")) {
        printf("Failed to load language file\n");
        free(options);
        exit(EXIT_FAILURE);
    }

    // Initialize configuration
    options->config = load_config();
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
    options->resolution_dropdown = NULL;
    options->language_dropdown = NULL;
    init_resolution_dropdown(options);
    init_language_dropdown(options);
    
    setup_button_geometry(options, width, height);
    // Create title texture
    create_title_texture(options, renderer);

    printf("Title texture created successfully\n");
    // Initialize dropdowns

    
    printf("Dropdowns initialized successfully\n");
    // Initialize button textures and states
    initialize_buttons_textures(options);
    current_resolution_index = find_current_resolution_index(
        options->config->screen_width, options->config->screen_height
    );
    
    printf("Buttons textures initialized successfully\n");
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

    // Free dropdowns
    if (options->resolution_dropdown) free_button_dropdown(options->resolution_dropdown);
    if (options->language_dropdown) free_button_dropdown(options->language_dropdown);
    
    // Free buttons

    
    Button* buttons[] = {
        options->full_screen, options->vsync, options->sound, options->volume,
        options->antialiasing, options->music_volume, options->effects_volume,
        options->voice_volume, options->save, options->reset,
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
        button->texture = NULL;
    }

    const char* translated_label = get_text_from_key(button->label);

    button->texture = create_text_texture(
        renderer,
        font,
        translated_label ? translated_label : button->label, 
        (SDL_Color){255, 255, 255, 255}
    );
}

void update_options(Options* options) {
    if (!options || !options->config) return;

    // Update button labels with translations
    char buffer[100];
    
    // Full Screen
    const char* fullscreen_base = get_text_from_key("options.BTN_FULLSCREEN");
    if (fullscreen_base) {
        // Extract the base text without the status
        char base[80];
        strncpy(base, fullscreen_base, sizeof(base) - 1);
        base[sizeof(base) - 1] = '\0';
        char* colon_pos = strchr(base, ':');
        if (colon_pos) {
            *colon_pos = '\0'; // Truncate at the colon
        }
        snprintf(buffer, sizeof(buffer), "%s: %s", base, 
                options->config->fullscreen ? "ON" : "OFF");
    } else {
        snprintf(buffer, sizeof(buffer), "Full Screen: %s", 
                options->config->fullscreen ? "ON" : "OFF");
    }
    strncpy(options->full_screen->label, buffer, MAX_BUTTON_LENGTH - 1);
    options->full_screen->label[MAX_BUTTON_LENGTH - 1] = '\0';

    // VSync
    const char* vsync_base = get_text_from_key("options.BTN_VSYNC");
    if (vsync_base) {
        char base[80];
        strncpy(base, vsync_base, sizeof(base) - 1);
        base[sizeof(base) - 1] = '\0';
        char* colon_pos = strchr(base, ':');
        if (colon_pos) {
            *colon_pos = '\0';
        }
        snprintf(buffer, sizeof(buffer), "%s: %s", base, 
                options->config->vsync ? "ON" : "OFF");
    } else {
        snprintf(buffer, sizeof(buffer), "VSync: %s", 
                options->config->vsync ? "ON" : "OFF");
    }
    strncpy(options->vsync->label, buffer, MAX_BUTTON_LENGTH - 1);
    options->vsync->label[MAX_BUTTON_LENGTH - 1] = '\0';

    // Sound
    const char* sound_base = get_text_from_key("options.BTN_SOUND");
    if (sound_base) {
        char base[80];
        strncpy(base, sound_base, sizeof(base) - 1);
        base[sizeof(base) - 1] = '\0';
        char* colon_pos = strchr(base, ':');
        if (colon_pos) {
            *colon_pos = '\0';
        }
        snprintf(buffer, sizeof(buffer), "%s: %s", base, 
                options->config->sound_enabled ? "ON" : "OFF");
    } else {
        snprintf(buffer, sizeof(buffer), "Sound: %s", 
                options->config->sound_enabled ? "ON" : "OFF");
    }
    strncpy(options->sound->label, buffer, MAX_BUTTON_LENGTH - 1);
    options->sound->label[MAX_BUTTON_LENGTH - 1] = '\0';

    // Volume
    const char* volume_base = get_text_from_key("options.BTN_VOLUME");
    if (volume_base) {
        char base[80];
        strncpy(base, volume_base, sizeof(base) - 1);
        base[sizeof(base) - 1] = '\0';
        char* colon_pos = strchr(base, ':');
        if (colon_pos) {
            *colon_pos = '\0';
        }
        snprintf(buffer, sizeof(buffer), "%s: %d", base, options->config->volume_level);
    } else {
        snprintf(buffer, sizeof(buffer), "Volume: %d", options->config->volume_level);
    }
    strncpy(options->volume->label, buffer, MAX_BUTTON_LENGTH - 1);
    options->volume->label[MAX_BUTTON_LENGTH - 1] = '\0';

    // Antialiasing
    const char* aa_base = get_text_from_key("options.BTN_ANTIALIASING");
    if (aa_base) {
        char base[80];
        strncpy(base, aa_base, sizeof(base) - 1);
        base[sizeof(base) - 1] = '\0';
        char* colon_pos = strchr(base, ':');
        if (colon_pos) {
            *colon_pos = '\0';
        }
        snprintf(buffer, sizeof(buffer), "%s: %s", base, 
                options->config->antialiasing ? "ON" : "OFF");
    } else {
        snprintf(buffer, sizeof(buffer), "Antialiasing: %s", 
                options->config->antialiasing ? "ON" : "OFF");
    }
    strncpy(options->antialiasing->label, buffer, MAX_BUTTON_LENGTH - 1);
    options->antialiasing->label[MAX_BUTTON_LENGTH - 1] = '\0';

    // Music Volume
    const char* music_base = get_text_from_key("options.BTN_MUSIC_VOLUME");
    if (music_base) {
        char base[80];
        strncpy(base, music_base, sizeof(base) - 1);
        base[sizeof(base) - 1] = '\0';
        char* colon_pos = strchr(base, ':');
        if (colon_pos) {
            *colon_pos = '\0';
        }
        snprintf(buffer, sizeof(buffer), "%s: %d", base, options->config->music_volume);
    } else {
        snprintf(buffer, sizeof(buffer), "Music Volume: %d", options->config->music_volume);
    }
    strncpy(options->music_volume->label, buffer, MAX_BUTTON_LENGTH - 1);
    options->music_volume->label[MAX_BUTTON_LENGTH - 1] = '\0';

    // Effects Volume
    const char* effects_base = get_text_from_key("options.BTN_EFFECTS_VOLUME");
    if (effects_base) {
        char base[80];
        strncpy(base, effects_base, sizeof(base) - 1);
        base[sizeof(base) - 1] = '\0';
        char* colon_pos = strchr(base, ':');
        if (colon_pos) {
            *colon_pos = '\0';
        }
        snprintf(buffer, sizeof(buffer), "%s: %d", base, options->config->effects_volume);
    } else {
        snprintf(buffer, sizeof(buffer), "Effects Volume: %d", options->config->effects_volume);
    }
    strncpy(options->effects_volume->label, buffer, MAX_BUTTON_LENGTH - 1);
    options->effects_volume->label[MAX_BUTTON_LENGTH - 1] = '\0';

    // Voice Volume
    const char* voice_base = get_text_from_key("options.BTN_VOICE_VOLUME");
    if (voice_base) {
        char base[80];
        strncpy(base, voice_base, sizeof(base) - 1);
        base[sizeof(base) - 1] = '\0';
        char* colon_pos = strchr(base, ':');
        if (colon_pos) {
            *colon_pos = '\0';
        }
        snprintf(buffer, sizeof(buffer), "%s: %d", base, options->config->voice_volume);
    } else {
        snprintf(buffer, sizeof(buffer), "Voice Volume: %d", options->config->voice_volume);
    }
    strncpy(options->voice_volume->label, buffer, MAX_BUTTON_LENGTH - 1);
    options->voice_volume->label[MAX_BUTTON_LENGTH - 1] = '\0';

    // Update button textures
    update_all_buttons_textures(options);
}
void update_resolution_dropdown_text(Options* options) {
    if (!options || !options->resolution_dropdown) return;
    
    ScreenResolution res = available_resolutions[current_resolution_index];
    snprintf(options->resolution_dropdown->text, MAX_INPUT_LENGTH, "%dx%d", res.width, res.height);
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
                handle_dropdown_click(options, mouse_x, mouse_y);
                handle_mouse_click(options, mouse_x, mouse_y);
            }
            break;
    }
}

void render_options(Options* options, SDL_Renderer* renderer) {
    if (!options || !renderer) return;
    
    int current_width = 800, current_height = 600;
    SDL_GetRendererOutputSize(renderer, &current_width, &current_height);
    
    // Render title
    render_title(options, renderer, current_width);

    // Render dropdowns (only main dropdown, not options)
    if (options->resolution_dropdown && options->resolution_dropdown->font) {
        render_button_dropdown(options->resolution_dropdown, renderer);
    }
    
    if (options->language_dropdown && options->language_dropdown->font) {
        render_button_dropdown(options->language_dropdown, renderer);
    }

    // Render all buttons
    render_all_buttons(options, renderer);
    
    // Render dropdown options on top (if active)
    if (options->resolution_dropdown && options->resolution_dropdown->isActive && 
        options->resolution_dropdown->items && options->resolution_dropdown->itemCount > 0) {
        render_button_dropdown_options(options->resolution_dropdown, renderer);
    }
    
    if (options->language_dropdown && options->language_dropdown->isActive && 
        options->language_dropdown->items && options->language_dropdown->itemCount > 0) {
        render_button_dropdown_options(options->language_dropdown, renderer);
    }
}

void change_language(Options* options, const char* lang_code) {
    if (!options || lang_code == NULL) return;
    

    // Update the language in the config
    strncpy(options->config->language, lang_code, sizeof(options->config->language) - 1);
    options->config->language[sizeof(options->config->language) - 1] = '\0';

    // Save the config
    save_config(options->config);

    // Update the interface
    update_options(options);
    update_button_geometry(options, options->config->screen_width, options->config->screen_height);
    printf("Language changed to %s\n", lang_code);
}

void update_button_geometry(Options* options, int screen_width, int screen_height) {
    if (!options) return;
    setup_button_geometry(options, screen_width, screen_height);
    
    // Update dropdown text after geometry change
    if (options->resolution_dropdown) {
        update_resolution_dropdown_text(options);
    }
}

void apply_resolution(Options* options) {
    if (!options || !options->config) return;
    
    ScreenResolution res = available_resolutions[current_resolution_index];
    
    // Aplicar mudança de resolução usando a nova função
    apply_resolution_change(screen, res.width, res.height);
    
    // Atualizar config
    options->config->screen_width = res.width;
    options->config->screen_height = res.height;
    // Salvar e atualizar interface
    save_config(options->config);
    update_options(options);
    update_button_geometry(options, res.width, res.height);
    
    printf("Resolution changed to %dx%d\n", res.width, res.height);
}