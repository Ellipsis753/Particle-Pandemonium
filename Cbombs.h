#pragma once

#include "Ctext.h"
#include "constBombs.h"
#include "Copengl.h"
#include "constImages.h"

class Cbombs {
    public:
    static OPENGL::vanillaPoint* draw(unsigned int bombs, Copengl &opengl, OPENGL::vanillaPoint* freeSpace);

    private:
    //none
};
