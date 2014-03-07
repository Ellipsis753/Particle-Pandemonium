#pragma once

#include "Ctext.h"
#include "constLives.h"
#include "Copengl.h"
#include "constImages.h"

class Clives {
    public:
    static OPENGL::vanillaPoint* draw(int lives, Copengl &opengl, OPENGL::vanillaPoint* freeSpace);

    private:
    //none
};
