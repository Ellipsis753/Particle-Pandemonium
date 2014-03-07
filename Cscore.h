#pragma once

#include "Ctext.h"
#include "constScore.h"
#include "Copengl.h"
#include "constImages.h"

class Cscore {
    public:
    Cscore();
    void add(int change);
    OPENGL::vanillaPoint* draw(Copengl &opengl, OPENGL::vanillaPoint* freeSpace);

    unsigned long get_score();
    void set_score(unsigned long setTo);

    private:
    Ctext text;
    unsigned long score;
};
