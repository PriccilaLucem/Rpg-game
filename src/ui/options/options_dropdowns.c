#include "options.h"
#include "../button/button.h"

extern ScreenResolution available_resolutions[];
extern LanguageOption available_languages[];
extern int current_resolution_index;
extern int current_language_index;
extern const int num_resolutions;
extern int num_languages;

void resolution_dropdown_callback(void* data) {
    DropdownItem* item = (DropdownItem*)data;
    if (!item) return;
    
    // Parse resolution from value
    int width, height;
    if (sscanf(item->value, "%dx%d", &width, &height) == 2) {
        // Find and set resolution index
        for (int i = 0; i < num_resolutions; i++) {
            if (available_resolutions[i].width == width && available_resolutions[i].height == height) {
                current_resolution_index = i;
                printf("Resolution changed to %dx%d\n", width, height);
                break;
            }
        }
    }
}

void language_dropdown_callback(void* data) {
    DropdownItem* item = (DropdownItem*)data;
    if (!item) return;
    
    // Find and set language index
    for (int i = 0; i < num_languages; i++) {
        if (strcmp(available_languages[i].code, item->value) == 0) {
            current_language_index = i;
            printf("Language changed to %s\n", item->value);
            break;
        }
    }
}

void init_resolution_dropdown(Options* options) {
    if (!options || !options->button_font) return;
    
    // Create dropdown items
    DropdownItem** items = malloc(num_resolutions * sizeof(DropdownItem*));
    if(!items){
        printf("Failed to allocate memory for resolution dropdown items\n");
        return;
    }
    
    for (int i = 0; i < num_resolutions; i++) {
        items[i] = malloc(sizeof(DropdownItem));
        if (!items[i]) {
            printf("Failed to allocate memory for a resolution dropdown item\n");
            for (int j = 0; j < i; j++) {
                free(items[j]);
            }
            free(items);
            return;
        }
        snprintf(items[i]->text, MAX_INPUT_LENGTH, "%dx%d", 
                available_resolutions[i].width, available_resolutions[i].height);
        snprintf(items[i]->value, MAX_INPUT_LENGTH, "%dx%d", 
                available_resolutions[i].width, available_resolutions[i].height);
        items[i]->onClick = resolution_dropdown_callback;
    }
    
    // Create dropdown
    char current_res[32];
    snprintf(current_res, sizeof(current_res), "%dx%d", 
            available_resolutions[current_resolution_index].width,
            available_resolutions[current_resolution_index].height);
            
    options->resolution_dropdown = init_button_dropdown(
        100, 100, 200, 40, num_resolutions, items, 
        current_res, options->button_font, (SDL_Color){255, 255, 255, 255}
    );
}

void init_language_dropdown(Options* options) {
    if (!options || !options->button_font) return;
    
    // Create dropdown items
    DropdownItem** items = malloc(num_languages * sizeof(DropdownItem*));
    if (!items){
        printf("Failed to allocate memory for language dropdown items\n");
        return;
    }

    
    for (int i = 0; i < num_languages; i++) {
        items[i] = malloc(sizeof(DropdownItem));
        if (!items[i]) {
            printf("Failed to allocate memory for a language dropdown item\n");
            for (int j = 0; j < i; j++) {
                free(items[j]);
            }
            free(items);
            return;
        }
        strncpy(items[i]->text, available_languages[i].name, MAX_INPUT_LENGTH - 1);
        items[i]->text[MAX_INPUT_LENGTH - 1] = '\0';
        strncpy(items[i]->value, available_languages[i].code, MAX_INPUT_LENGTH - 1);
        items[i]->value[MAX_INPUT_LENGTH - 1] = '\0';
        items[i]->onClick = language_dropdown_callback;
    }
    
    // Create dropdown
    options->language_dropdown = init_button_dropdown(
        320, 100, 200, 40, num_languages, items,
        available_languages[current_language_index].name, 
        options->button_font, (SDL_Color){255, 255, 255, 255}
    );
}