#pragma once

#include <random>

#include "CparticleController.h"
#include "constStarController.h"

class CstarController {
    public:
    void cover_screen(std::default_random_engine* randomEngine, CparticleController &particleController);
    void step(std::default_random_engine* randomEngine, CparticleController &particleController);

    private:
    void add_star(std::default_random_engine* randomEngine, CparticleController &particleController);
};
