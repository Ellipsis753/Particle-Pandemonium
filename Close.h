#pragma once

#include <stdio.h>

#include "Copengl.h"
#include "Cloader.h"
#include "CshaderProgram.h"
#include "constState.h"
#include "constLose.h"
#include "Csound.h"

class Close {
    public:
    STATE::STATE run(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl);

    private:
    bool init(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl);
};
