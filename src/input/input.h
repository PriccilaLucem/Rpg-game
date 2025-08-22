#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <stdbool.h>



/// @brief Input of all possible keys of keyboard and mouse
typedef struct Input {
    bool quit;
    bool keys[SDL_NUM_SCANCODES];  
    int mouseX, mouseY;
    bool mouseButtons[5]; 
} Input;

void handleInput(Input* input, SDL_Event* event);

#endif 