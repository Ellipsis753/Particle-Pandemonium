#pragma once

#include "SDL_mixer.h"
#include <stdio.h>

#include "constSounds.h"

class Csound {
    public:
    static bool init();
    static Mix_Chunk* load_effect(const char* const path);
    static Mix_Music* load_music(const char* const path);
    static void play_effect(Mix_Chunk* chunk);
    static void play_music(Mix_Music* music, bool loop=true);
    static void set_effect_volume(Mix_Chunk* chunk, int volume);
    static void set_music_volume(int volume);
    static void unload_effect(Mix_Chunk* chunk);
    static void unload_music(Mix_Music* music);
    static void quit();

    private:
    //Prevent people from constructing it
    Csound();
};
