#include "Cgame.h"

int Cgame::run() {
    Cloader loader;
    Copengl opengl;
    Cvao vanilla;
    CshaderProgram vanillaProgram;
    Cscore score;

    CstateManager stateManager;
    STATE::STATE currentState = STATE::START_GAME;

    while (currentState != STATE::END_GAME && currentState != STATE::ENCOUNTERED_ERROR) {
        currentState = stateManager.set_state(currentState, vanilla, vanillaProgram, loader, opengl, score);
    }
    if (currentState == STATE::ENCOUNTERED_ERROR) {
        return 1;
    }

    return 0;
}
