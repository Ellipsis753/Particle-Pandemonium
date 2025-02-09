#include "CstartGame.h"

STATE::STATE CstartGame::run(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl) {
    Csdl sdl;
    if (sdl.init() == false) {
        return STATE::ENCOUNTERED_ERROR;
    }

    if (Csound::init() == false) {
        return STATE::ENCOUNTERED_ERROR;
    }

    if (loader.preload() == false) {
        return STATE::ENCOUNTERED_ERROR;
    }

    if (sdl.create_window(loader.get_icon()) == false) {
        return STATE::ENCOUNTERED_ERROR;
    }

    if (opengl.init(vanilla, vanillaProgram) == false) {
        return STATE::ENCOUNTERED_ERROR;
    }

    return STATE::LOAD;
}
