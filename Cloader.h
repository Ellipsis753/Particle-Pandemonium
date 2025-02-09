#pragma once

#include <stdio.h>
#define NO_SDL_GLEXT
#include <GL/glew.h>
#include "SDL.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <cmath>
#include <random>
#include <stdlib.h>

#include "CshaderProgram.h"
#include "Csdl.h"
#include "Cvao.h"
#include "constSdl.h"
#include "constImages.h"
#include "constOpengl.h"
#include "constParticleController.h"
#include "Csound.h"

class Cloader {
    public:
    Cloader();
    bool preload();
    void load_loading_image();
    bool load();
    ~Cloader();

    SDL_Surface* get_icon();
    OPENGL::speed2d* get_random_speeds();
    std::default_random_engine* get_random_engine();
    Mix_Music* get_menu_music();
    Mix_Music* get_in_game_music();
    Mix_Music* get_lose_music();
    Mix_Music* get_win_music();
    Mix_Chunk* get_laser_effect();
    Mix_Chunk* get_explosion_effect();
    Mix_Chunk* get_bomb_effect();
    Mix_Chunk* get_death_effect();

    private:
    Cloader(const Cloader&) = delete;
    Cloader& operator = (const Cloader&) = delete;

    bool load_vanilla_shader();
    SDL_Surface* load_image(const char path[], bool colourKey=0);
    GLuint convert_image(SDL_Surface* image);
    GLuint load_and_convert_image(const char path[], bool colourKey=0);
    void generate_random_speeds();
    void unload();

    SDL_Surface* icon;
    SDL_Surface* loadingSdl;
    GLuint loadingImage;
    GLuint menuImage;
    GLuint gameplayImage;
    //GLuint playerImage;
    //Too big for stack! static makes it on the heap.
    OPENGL::speed2d* randomSpeeds;
    std::default_random_engine randomEngine;
    Mix_Music* menuMusic;
    Mix_Music* inGameMusic;
    Mix_Music* loseMusic;
    Mix_Music* winMusic;
    Mix_Chunk* laserEffect;
    Mix_Chunk* explosionEffect;
    Mix_Chunk* bombEffect;
    Mix_Chunk* deathEffect;
};

inline
std::default_random_engine* Cloader::get_random_engine() {
    return &randomEngine;
}

inline
OPENGL::speed2d* Cloader::get_random_speeds() {
    return randomSpeeds;
}
