#pragma once

#include <stdio.h>

#include "constState.h"
#include "Cmenu.h"
#include "CstartGame.h"
#include "Cload.h"
#include "Cgameplay.h"
#include "Ctutorial.h"
#include "Close.h"
#include "Cwin.h"
#include "Cscoreboard.h"

class Cloader;
class Cvao;
class CshaderProgram;
class Copengl;
class Cscore;

class CstateManager {
    public:
    STATE::STATE set_state(STATE::STATE state, Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl, Cscore &score);

    private:
};
