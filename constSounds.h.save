#pragma once

#include "SDL_mixer.h"

/*
Constants related to sounds and music in the game as well SDL_mixer
which is the library used for the sound and music.
*/

namespace SOUNDS {
    //The flags to be set for the systems required in SDL_mixer
    const int FLAGS = MIX_INIT_MOD;
    //The sample rate in Hz for music and sounds to be played at
    const int FREQUENCY = MIX_DEFAULT_FREQUENCY;
    //The format for the samples
    const Uint16 FORMAT = MIX_DEFAULT_FORMAT;
    //The number of channels to be used in SDL_mixer. 2 is for stereo sound.
    const int CHANNELS = 2;
    //The chunk size to be alocated. Larger will allow for smoother music without
    //any stuttering but may cause a delay between when a sound is called for and when
    //it starts to play. (While the chunk is being loaded.)
    const int CHUNKSIZE = 4096;

    //The paths to the required music and sound.
    const char* const MENU_PATH = "menu.xm";
    const char* const INGAME_PATH = "1.mod";
    const char* const WIN_PATH = "win.xm";
    const char* const LOSE_PATH = "lose.xm";
    const char* const LASER_PATH = "laser.wav";
    const char* const EXPLOSION_PATH = "explosion.wav";
    const char* const BOMB_PATH = "bomb.wav";
    const char* const DEATH_PATH = "die.wav";
}
