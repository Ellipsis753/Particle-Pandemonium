#pragma once

#include <stdio.h>
#include <vector>
#include "SDL.h"

#include "constState.h"
#include "constImages.h"
#include "Cbullet.h"
#include "Cplayer.h"
#include "CparticleController.h"
#include "constOpengl.h"
#include "Cloader.h"
#include "constGameplay.h"
#include "CstarController.h"
#include "CplayerBullet.h"
#include "Cenemy.h"
#include "constBullet.h"
#include "Cscore.h"
#include "Csound.h"
#include "Copengl.h"
#include "CenemyController.h"
#include "Cvao.h"
#include "Cbomb.h"
#include "Clives.h"
#include "Cbombs.h"

class Cgameplay {
    public:
    Cgameplay();
    STATE::STATE run(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl, Cscore &score);
    ~Cgameplay();

    private:
    void init(Cloader &loader, Copengl &opengl, Cscore &score);
    bool frame(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl, Cscore &score);
    void handleEvents();
    bool draw(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl, Cscore &score);

    CparticleController particleController;
    CstarController starController;
    CenemyController enemyController;
    std::vector<Cbullet*> bullets;
    std::vector<CplayerBullet*> playerBullets;
    std::vector<Cenemy*> enemies;
    Cplayer player;
    std::vector<Cbomb*> bombs;
    Uint32 startGameTime;
    unsigned int frameCount;
    char drawsInLastSecond;
    bool endGame;
    bool quit;
    bool menu;
    bool win;
};

