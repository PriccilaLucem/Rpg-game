#include "./music.h"
#include "../config/config.h"

Music* init_music(const char* path){
    
    Config* conf = load_config();

    Music* music = malloc(sizeof(Music));
    if(!music){
        printf("Failed to allocate memory for music\n");
        exit(EXIT_FAILURE);
    }
    music->music = Mix_LoadMUS(path);
    if(!music->music){
        printf("Failed to load music: %s\n", Mix_GetError());
        free(music);
        exit(EXIT_FAILURE);
    }
    music->volume = conf->music_volume;
    music->is_playing = false;
    music->looping = false;
    return music;
}

void render_music(Music* music){
    if(music->is_playing){
        Mix_VolumeMusic(music->volume);
        Mix_StartTrack(music->music, music->looping ? -1 : 1);
    }
    else{
        Mix_HaltMusic();
    }
}

void play_music(Music* music){
    music->is_playing = true;
}
void stop_music(Music* music){
    music->is_playing = false;
}

