#include "options_geometry.h"
#include "../button/button.h"
#include "../../lang/language.h"

void setup_button_geometry(Options* options, int screen_width, int screen_height) {
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

    // Left column buttons - use translation keys
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

    // Right column buttons - use translation keys
    const char* save_text = get_text_from_key("options.BTN_SAVE");
    options->save = init_button(right_x, right_y, right_column_width, button_height, 
                               save_text ? save_text : "SAVE", false, false, options->button_font);
    
    right_y += button_height + spacing_y_right;
    
    const char* reset_text = get_text_from_key("options.BTN_RESET");
    options->reset = init_button(right_x, right_y, right_column_width, button_height, 
                                reset_text ? reset_text : "RESET TO DEFAULT", false, false, options->button_font);
    
    right_y += button_height + spacing_y_right;
    
    const char* back_text = get_text_from_key("options.BTN_BACK");
    options->back_to_main_menu = init_button(right_x, right_y, right_column_width, button_height, 
                                           back_text ? back_text : "BACK TO MAIN MENU", false, false, options->button_font);
}