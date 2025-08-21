#include "button.h"

Button* init_button(int x, int y, int width, int height,
     const char* label, bool isClicked, bool isHovered, TTF_Font* font) {
    Button* button = malloc(sizeof(Button));
    if (button == NULL) {
        return NULL;
    }
    
    button->x = x;
    button->y = y;
    button->width = width;
    button->height = height;
    
    strncpy(button->label, label, MAX_BUTTON_LENGTH - 1);
    button->label[MAX_BUTTON_LENGTH - 1] = '\0'; 
    
    button->isHovered = isHovered;
    button->isClicked = isClicked;
    button->font = font;
    button->onClick = NULL;
    
    return button;
}