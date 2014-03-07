#pragma once

#include <stdio.h>

#include "constState.h"
#include "constOpengl.h"
#include "constImages.h"
#include "Cvao.h"
#include "Copengl.h"
#include "Cloader.h"
#include "CshaderProgram.h"

class Cload {
    public:
    STATE::STATE run(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl);

    private:
    bool draw_loading_screen(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl);
};
