#ifndef OPTIONS_RENDER_H
#define OPTIONS_RENDER_H

#include "options.h"

// Rendering functions
void create_title_texture(Options* options, SDL_Renderer* renderer);
void initialize_buttons_textures(Options* options);
void update_all_buttons_textures(Options* options);
void render_title(Options* options, SDL_Renderer* renderer, int screen_width);
void render_all_buttons(Options* options, SDL_Renderer* renderer);

#endif