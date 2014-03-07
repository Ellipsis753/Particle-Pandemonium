#pragma once

#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <GL/gl.h>
#include <random>

#include "constParticleController.h"
#include "Cvao.h"
#include "constOpengl.h"
#include "CshaderProgram.h"
#include "Cloader.h"

class CparticleController {
    public:
    CparticleController();
    void draw_and_step();
    void step();
    bool make_ready_to_add();
    void finish_adding();
    void add_particle(float x, float y, float speedX, float speedY, float r, float g, float b);
    void add_explosion_particle(Cloader &loader, float x, float y, float r, float g, float b, float speedOffsetX, float speedOffsetY);
    void add_explosion_particle(Cloader &loader, float x, float y, float r, float g, float b);
    void add_explosion_particle(Cloader &loader, float x, float y);

    ~CparticleController();

    private:
    CparticleController(const CparticleController&) = delete;
    CparticleController& operator = (const CparticleController&) = delete;

    bool init();

    Cvao ping;
    Cvao pong;
    Cvao* active;
    Cvao* inactive;
    CshaderProgram program;
    unsigned int frame;
    int noFreeUnusedBefore;
    int finalUsedIndex;
    unsigned int particleDeathsFrames[PARTICLE_CONTROLLER::MAX_POINTS];
    OPENGL::particlePoint* startOfActive;
};

//We could have perhaps used one function (with defaults) here instead of overloading. However for speed 3 seperate functions are better
inline
void CparticleController::add_explosion_particle(Cloader &loader, float x, float y, float r, float g, float b, float speedOffsetX, float speedOffsetY) {
    OPENGL::speed2d* randomSpeeds = loader.get_random_speeds();
    std::default_random_engine* randomEngine = loader.get_random_engine();
    std::uniform_int_distribution<int> distribution(0, PARTICLE_CONTROLLER::NUMBER_OF_RANDOM_SPEEDS-1);

    bool loop = true;
    float speedX;
    float speedY;
    while (loop == true) {
        loop = false;
        OPENGL::speed2d randomSpeed = randomSpeeds[distribution(*randomEngine)];

        speedX = randomSpeed.x+speedOffsetX;
        speedY = randomSpeed.y+speedOffsetY;

        if (std::abs(speedY) < PARTICLE_CONTROLLER::EXPLOSION_DISTRIBUTION::MIN_SPEED/2 && std::abs(speedX) < PARTICLE_CONTROLLER::EXPLOSION_DISTRIBUTION::MIN_SPEED/2) {
            //If it would have been super slow reject it and get a new random
            loop = true;
        }
    }

    add_particle(x, y, speedX, speedY, r, g, b);
}

inline
void CparticleController::add_explosion_particle(Cloader &loader, float x, float y, float r, float g, float b) {
    OPENGL::speed2d* randomSpeeds = loader.get_random_speeds();
    std::default_random_engine* randomEngine = loader.get_random_engine();
    std::uniform_int_distribution<int> distribution(0, PARTICLE_CONTROLLER::NUMBER_OF_RANDOM_SPEEDS-1);
    OPENGL::speed2d randomSpeed = randomSpeeds[distribution(*randomEngine)];

    add_particle(x, y, randomSpeed.x, randomSpeed.y, r, g, b);
}

inline
void CparticleController::add_explosion_particle(Cloader &loader, float x, float y) {
    OPENGL::speed2d* randomSpeeds = loader.get_random_speeds();
    std::default_random_engine* randomEngine = loader.get_random_engine();
    std::uniform_int_distribution<int> distribution(0, PARTICLE_CONTROLLER::NUMBER_OF_RANDOM_SPEEDS-1);
    OPENGL::speed2d randomSpeed = randomSpeeds[distribution(*randomEngine)];

    float red = rand()/float(RAND_MAX);
    float green = rand()/float(RAND_MAX);
    float blue = rand()/float(RAND_MAX);

    add_particle(x, y, randomSpeed.x, randomSpeed.y, red, green, blue);
}
