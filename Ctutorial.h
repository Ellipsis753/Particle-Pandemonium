#pragma once

#include <stdio.h>
#include "SDL.h"

#include "Copengl.h"
#include "Cloader.h"
#include "Cbutton.h"
#include "CshaderProgram.h"
#include "constState.h"
#include "constTutorial.h"

class Ctutorial {
    public:
    STATE::STATE run(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl);

    private:
    bool init(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl);
};
