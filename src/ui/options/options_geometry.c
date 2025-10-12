#include "options_geometry.h"
#include "../button/button.h"
#include "../../lang/language.h"

void setup_button_geometry(Options* options, int screen_width, int screen_height) {
    // Base dimensions
    int button_width = 300;
    int button_height = 50;
    int dropdown_width = 200;
    int spacing_y = 20;
    int section_spacing = 40;
    
    // Center everything
    int center_x = screen_width / 2;
    int start_y = 120;
    
    // Current Y position tracker
    int current_y = start_y;

    // === DISPLAY SETTINGS SECTION ===
    
    // Resolution dropdown (replaces arrow buttons)
    if (options->resolution_dropdown) {
        options->resolution_dropdown->x = center_x - dropdown_width / 2;
        options->resolution_dropdown->y = current_y;
        options->resolution_dropdown->width = dropdown_width;
        options->resolution_dropdown->height = button_height;
        options->resolution_dropdown->rect = (SDL_Rect){options->resolution_dropdown->x, options->resolution_dropdown->y, dropdown_width, button_height};
    }
    current_y += button_height + spacing_y;
    
    // Language dropdown
    if (options->language_dropdown) {
        options->language_dropdown->x = center_x - dropdown_width / 2;
        options->language_dropdown->y = current_y;
        options->language_dropdown->width = dropdown_width;
        options->language_dropdown->height = button_height;
        options->language_dropdown->rect = (SDL_Rect){options->language_dropdown->x, options->language_dropdown->y, dropdown_width, button_height};
    }
    current_y += button_height + section_spacing;
    
    // === VIDEO SETTINGS SECTION ===
    
    // Full Screen
    options->full_screen = init_button(center_x - button_width/2, current_y, button_width, button_height, "FULL SCREEN: OFF", false, false, options->button_font);
    options->full_screen->onClick = fullscreen_onClick;
    options->full_screen->onClickData = options;
    current_y += button_height + spacing_y;
    
    // VSync
    options->vsync = init_button(center_x - button_width/2, current_y, button_width, button_height, "VSYNC: OFF", false, false, options->button_font);
    options->vsync->onClick = vsync_onClick;
    options->vsync->onClickData = options;
    current_y += button_height + spacing_y;
    
    // Antialiasing
    options->antialiasing = init_button(center_x - button_width/2, current_y, button_width, button_height, "ANTIALIASING: ON", false, false, options->button_font);
    options->antialiasing->onClick = antialiasing_onClick;
    options->antialiasing->onClickData = options;
    current_y += button_height + section_spacing;
    
    // === AUDIO SETTINGS SECTION ===
    
    // Sound
    options->sound = init_button(center_x - button_width/2, current_y, button_width, button_height, "SOUND: ON", false, false, options->button_font);
    options->sound->onClick = sound_onClick;
    options->sound->onClickData = options;
    current_y += button_height + spacing_y;
    
    // Master Volume
    options->volume = init_button(center_x - button_width/2, current_y, button_width, button_height, "VOLUME: 100", false, false, options->button_font);
    options->volume->onClick = volume_onClick;
    options->volume->onClickData = options;
    current_y += button_height + spacing_y;
    
    // Music Volume
    options->music_volume = init_button(center_x - button_width/2, current_y, button_width, button_height, "MUSIC VOLUME: 0", false, false, options->button_font);
    options->music_volume->onClick = music_volume_onClick;
    options->music_volume->onClickData = options;
    current_y += button_height + spacing_y;
    
    // Effects Volume
    options->effects_volume = init_button(center_x - button_width/2, current_y, button_width, button_height, "EFFECTS VOLUME: 70", false, false, options->button_font);
    options->effects_volume->onClick = effects_volume_onClick;
    options->effects_volume->onClickData = options;
    current_y += button_height + spacing_y;
    
    // Voice Volume
    options->voice_volume = init_button(center_x - button_width/2, current_y, button_width, button_height, "VOICE VOLUME: 75", false, false, options->button_font);
    options->voice_volume->onClick = voice_volume_onClick;
    options->voice_volume->onClickData = options;
    current_y += button_height + section_spacing;
    
    // === ACTION BUTTONS SECTION ===
    
    // Save button
    const char* save_text = get_text_from_key("options.BTN_SAVE");
    options->save = init_button(center_x - button_width/2, current_y, button_width, button_height, 
                               save_text ? save_text : "SAVE", false, false, options->button_font);
    options->save->onClick = save_onClick;
    options->save->onClickData = options;
    current_y += button_height + spacing_y;
    
    // Reset button
    const char* reset_text = get_text_from_key("options.BTN_RESET");
    options->reset = init_button(center_x - button_width/2, current_y, button_width, button_height, 
                                reset_text ? reset_text : "RESET TO DEFAULT", false, false, options->button_font);
    options->reset->onClick = reset_onClick;
    options->reset->onClickData = options;
    current_y += button_height + spacing_y;
    
    // Back button
    const char* back_text = get_text_from_key("options.BTN_BACK");
    options->back_to_main_menu = init_button(center_x - button_width/2, current_y, button_width, button_height, 
                                           back_text ? back_text : "BACK TO MAIN MENU", false, false, options->button_font);
    options->back_to_main_menu->onClick = back_to_main_menu_onClick;
    options->back_to_main_menu->onClickData = options;
}