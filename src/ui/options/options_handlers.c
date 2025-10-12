#include "options.h"

void handle_dropdown_click(Options* options, int mouse_x, int mouse_y) {
    if (!options) return;
    
    // Check resolution dropdown
    if (options->resolution_dropdown) {
        SDL_Rect* rect = &options->resolution_dropdown->rect;
        if (mouse_x >= rect->x && mouse_x <= rect->x + rect->w &&
            mouse_y >= rect->y && mouse_y <= rect->y + rect->h) {
            options->resolution_dropdown->isActive = !options->resolution_dropdown->isActive;
            if (options->language_dropdown) options->language_dropdown->isActive = false;
            return;
        }
        
        // Check dropdown options if active
        if (options->resolution_dropdown->isActive && options->resolution_dropdown->items) {
            int optionY = rect->y + rect->h;
            for (int i = 0; i < options->resolution_dropdown->itemCount; i++) {
                if (options->resolution_dropdown->items[i] &&
                    mouse_x >= rect->x && mouse_x <= rect->x + rect->w &&
                    mouse_y >= optionY && mouse_y <= optionY + rect->h) {
                    if (options->resolution_dropdown->items[i]->onClick) {
                        options->resolution_dropdown->items[i]->onClick(options->resolution_dropdown->items[i]);
                    }
                    options->resolution_dropdown->isActive = false;
                    return;
                }
                optionY += rect->h;
            }
        }
    }
    
    // Check language dropdown
    if (options->language_dropdown) {
        SDL_Rect* rect = &options->language_dropdown->rect;
        if (mouse_x >= rect->x && mouse_x <= rect->x + rect->w &&
            mouse_y >= rect->y && mouse_y <= rect->y + rect->h) {
            options->language_dropdown->isActive = !options->language_dropdown->isActive;
            if (options->resolution_dropdown) options->resolution_dropdown->isActive = false;
            return;
        }
        
        // Check dropdown options if active
        if (options->language_dropdown->isActive && options->language_dropdown->items) {
            int optionY = rect->y + rect->h;
            for (int i = 0; i < options->language_dropdown->itemCount; i++) {
                if (options->language_dropdown->items[i] &&
                    mouse_x >= rect->x && mouse_x <= rect->x + rect->w &&
                    mouse_y >= optionY && mouse_y <= optionY + rect->h) {
                    if (options->language_dropdown->items[i]->onClick) {
                        options->language_dropdown->items[i]->onClick(options->language_dropdown->items[i]);
                    }
                    options->language_dropdown->isActive = false;
                    return;
                }
                optionY += rect->h;
            }
        }
    }
}

void handle_mouse_motion(Options* options, int mouse_x, int mouse_y) {
    if (!options) return;
    
    Button* buttons[] = {
        options->full_screen, options->vsync, options->sound, options->volume,
        options->antialiasing, options->music_volume, options->effects_volume,
        options->voice_volume, options->save, options->reset,
        options->back_to_main_menu, NULL
    };
    
    for (int i = 0; buttons[i] != NULL; i++) {
        if (buttons[i]) {
            check_button_hover(buttons[i], mouse_x, mouse_y);
        }
    }
}

void handle_mouse_click(Options* options, int mouse_x, int mouse_y) {
    if (!options) return;
    
    Button* buttons[] = {
        options->full_screen, options->vsync, options->sound, options->volume,
        options->antialiasing, options->music_volume, options->effects_volume,
        options->voice_volume, options->save, options->reset,
        options->back_to_main_menu, NULL
    };
    
    for (int i = 0; buttons[i] != NULL; i++) {
        if (buttons[i] && check_button_click(buttons[i], mouse_x, mouse_y)) {
            printf("Button clicked: %s\n", buttons[i]->label);
            if (buttons[i]->onClick) {
                buttons[i]->onClick(buttons[i]->onClickData);
            } else {
                printf("No callback set for button: %s\n", buttons[i]->label);
            }
        }
    }
}