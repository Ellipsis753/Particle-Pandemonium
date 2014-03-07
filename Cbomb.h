#pragma once

#include "Copengl.h"
#include "constImages.h"
#include "Cloader.h"
#include "CparticleController.h"
#include "constBomb.h"
#include "Cenemy.h"
#include "Cbullet.h"
#include "Cscore.h"

class Cbomb {
    public:
    Cbomb(float x, float y);
    BOMB::STEP step(Cscore &score, Cloader &loader, CparticleController &particleController, std::vector<Cenemy*> &enemies, std::vector<Cbullet*> &bullets);
    OPENGL::vanillaPoint* draw(Copengl &opengl, OPENGL::vanillaPoint* freeSpace);

    private:
    bool explode(Cscore &score, Cloader &loader, CparticleController &particleController, std::vector<Cenemy*> &enemies, std::vector<Cbullet*> &bullets);
    float x;
    float y;
    int life;
};
