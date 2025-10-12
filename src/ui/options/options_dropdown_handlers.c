#include "options.h"

extern ButtonDropdown* resolution_dropdown;
extern ButtonDropdown* language_dropdown;

void handle_dropdown_click_dropdown(Options* options, int mouse_x, int mouse_y) {
    if (!options) return;
    
    // Check resolution dropdown
    if (options->resolution_dropdown) {
        SDL_Rect dropdown_rect = options->resolution_dropdown->rect;
        
        // Check main dropdown button click
        if (mouse_x >= dropdown_rect.x && mouse_x <= dropdown_rect.x + dropdown_rect.w &&
            mouse_y >= dropdown_rect.y && mouse_y <= dropdown_rect.y + dropdown_rect.h) {
            
            if (options->resolution_dropdown->isActive) {
                close_button_dropdown(options->resolution_dropdown);
            } else {
                open_button_dropdown(options->resolution_dropdown);
                close_button_dropdown(options->language_dropdown); // Close other dropdown
            }
        }
        
        // Check dropdown options click
        if (options->resolution_dropdown->isActive) {
            int option_y = dropdown_rect.y + dropdown_rect.h;
            for (int i = 0; i < options->resolution_dropdown->itemCount; i++) {
                if (mouse_x >= dropdown_rect.x && mouse_x <= dropdown_rect.x + dropdown_rect.w &&
                    mouse_y >= option_y && mouse_y <= option_y + dropdown_rect.h) {
                    
                    // Select this option
                    options->resolution_dropdown->selectedItem = options->resolution_dropdown->items[i];
                    strncpy(options->resolution_dropdown->text, options->resolution_dropdown->items[i]->text, MAX_INPUT_LENGTH - 1);
                    options->resolution_dropdown->text[MAX_INPUT_LENGTH - 1] = '\0';
                    
                    // Call callback
                    if (options->resolution_dropdown->items[i]->onClick) {
                        options->resolution_dropdown->items[i]->onClick(options->resolution_dropdown->items[i]);
                    }
                    
                    close_button_dropdown(options->resolution_dropdown);
                    break;
                }
                option_y += dropdown_rect.h;
            }
        }
    }
    
    // Check language dropdown
    if (options->language_dropdown) {
        SDL_Rect dropdown_rect = options->language_dropdown->rect;
        
        // Check main dropdown button click
        if (mouse_x >= dropdown_rect.x && mouse_x <= dropdown_rect.x + dropdown_rect.w &&
            mouse_y >= dropdown_rect.y && mouse_y <= dropdown_rect.y + dropdown_rect.h) {
            
            if (options->language_dropdown->isActive) {
                close_button_dropdown(options->language_dropdown);
            } else {
                open_button_dropdown(options->language_dropdown);
                close_button_dropdown(options->resolution_dropdown); // Close other dropdown
            }
        }
        
        // Check dropdown options click
        if (options->language_dropdown->isActive) {
            int option_y = dropdown_rect.y + dropdown_rect.h;
            for (int i = 0; i < options->language_dropdown->itemCount; i++) {
                if (mouse_x >= dropdown_rect.x && mouse_x <= dropdown_rect.x + dropdown_rect.w &&
                    mouse_y >= option_y && mouse_y <= option_y + dropdown_rect.h) {
                    
                    // Select this option
                    options->language_dropdown->selectedItem = options->language_dropdown->items[i];
                    strncpy(options->language_dropdown->text, options->language_dropdown->items[i]->text, MAX_INPUT_LENGTH - 1);
                    options->language_dropdown->text[MAX_INPUT_LENGTH - 1] = '\0';
                    
                    // Call callback
                    if (options->language_dropdown->items[i]->onClick) {
                        options->language_dropdown->items[i]->onClick(options->language_dropdown->items[i]);
                    }
                    
                    close_button_dropdown(options->language_dropdown);
                    break;
                }
                option_y += dropdown_rect.h;
            }
        }
    }
}