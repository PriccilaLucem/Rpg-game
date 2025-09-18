#ifndef MUSIC_H
#define MUSIC_H

#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Music
{
    Mix_Music* music;
    int volume;
    bool is_playing;
    bool looping;
} Music;

Music* init_music(const char* file_path);
void render_music(Music* music);
void play_music(Music* music);
void stop_music(Music* music);


#endif