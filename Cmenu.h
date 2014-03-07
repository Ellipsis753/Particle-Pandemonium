#pragma once

#include <stdio.h>
#include "SDL.h"

#include "Copengl.h"
#include "Cloader.h"
#include "Cbutton.h"
#include "CshaderProgram.h"
#include "constState.h"
#include "constMenu.h"
#include "Csound.h"

class Cmenu {
    public:
    STATE::STATE run(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl);

    private:
    bool init(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl);
};
