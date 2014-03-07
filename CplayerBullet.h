#pragma once

#include "Copengl.h"
#include "constImages.h"
#include "constPlayerBullet.h"

class CplayerBullet {
    public:
    CplayerBullet(float x, float y);
    bool step();
    OPENGL::vanillaPoint* draw(Copengl &opengl, OPENGL::vanillaPoint* freeSpace);

    float get_x();
    float get_y();

    private:
    float x;
    float y;
};
