#pragma once

#include <stdio.h>

#include "constState.h"
#include "Cloader.h"
#include "Csdl.h"
#include "Copengl.h"
#include "CshaderProgram.h"

class CstartGame {
    public:
    STATE::STATE run(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl);

    private:
};
