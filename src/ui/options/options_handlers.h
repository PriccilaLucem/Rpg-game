#ifndef OPTIONS_HANDLERS_H
#define OPTIONS_HANDLERS_H

#include "options.h"

// Input handlers
void handle_mouse_motion(Options* options, int mouse_x, int mouse_y);
void handle_mouse_click(Options* options, int mouse_x, int mouse_y);
void handle_dropdown_click(Options* options, int mouse_x, int mouse_y);

#endif