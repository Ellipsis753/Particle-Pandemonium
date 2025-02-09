#include "Csound.h"

Csound::Csound() {
    //empty
}

bool Csound::init() {
    if (Mix_OpenAudio(SOUNDS::FREQUENCY, SOUNDS::FORMAT, SOUNDS::CHANNELS, SOUNDS::CHUNKSIZE) != 0) {
        fprintf(stderr, "Could not start SDL mixer: %s.\n", Mix_GetError());
        return false;
    }

    int flags = Mix_Init(SOUNDS::FLAGS);
    if ((flags & MIX_INIT_MOD) != MIX_INIT_MOD) {
        fprintf(stderr, "Could not get .mod music support.\n");
        //We can continue without
    }
    return true;
}

Mix_Chunk* Csound::load_effect(const char* const path) {
    //Although it has WAV in the name it can also load .mod
    Mix_Chunk* chunk = Mix_LoadWAV(path);
    if (chunk == NULL) {
        fprintf(stderr, "Could not load %s.\n", path);
    } else {
        fprintf(stdout, "Loaded %s.\n", path);
    }
    return chunk;
}

Mix_Music* Csound::load_music(const char* const path) {
    Mix_Music* music = Mix_LoadMUS(path);
    if (music == NULL) {
        fprintf(stderr, "Could not load %s.\n", path);
    } else {
        fprintf(stdout, "Loaded %s.\n", path);
    }
    return music;
}

void Csound::play_effect(Mix_Chunk* chunk) {
    if (Mix_PlayChannel(-1, chunk, 0) == -1) {
        fprintf(stderr, "Could not play sound effect: %s.\n", Mix_GetError());
    }
}

void Csound::play_music(Mix_Music* music, bool loop) {
    int loopArg = -1;
    if (loop == false) {
        loopArg = 0;
    }
    if (Mix_PlayMusic(music, loopArg) == -1) {
        fprintf(stderr, "Could not play music: %s.\n", Mix_GetError());
    }
}

void Csound::set_effect_volume(Mix_Chunk* chunk, int volume) {
    Mix_VolumeChunk(chunk, volume);
}

void Csound::set_music_volume(int volume) {
    Mix_VolumeMusic(volume);
}

void Csound::unload_effect(Mix_Chunk* chunk) {

    Mix_FreeChunk(chunk);
}

void Csound::unload_music(Mix_Music* music) {
    Mix_FreeMusic(music);
}

void Csound::quit() {
    Mix_CloseAudio();
    Mix_Quit();
}
