#include "./input.h"

void handleInput(Input* input, SDL_Event* event) {

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                input->quit = true;
                break;

            case SDL_KEYDOWN:
                input->keys[event.key.keysym.scancode] = true;
                break;

            case SDL_KEYUP:
                input->keys[event.key.keysym.scancode] = false;
                break;

            case SDL_MOUSEMOTION:
                input->mouseX = event.motion.x;
                input->mouseY = event.motion.y;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button < 5)
                    input->mouseButtons[event.button.button] = true;
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button < 5)
                    input->mouseButtons[event.button.button] = false;
                break;
        }
    }
}