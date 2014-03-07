#pragma once

#include "SDL.h"
#include <vector>

#include "Copengl.h"
#include "constImages.h"
#include "constOpengl.h"
#include "Cbullet.h"
#include "constPlayer.h"
#include "CplayerBullet.h"
#include "Csound.h"
#include "Cloader.h"
#include "Cbomb.h"
#include "Cenemy.h"
#include "CparticleController.h"

class Cplayer {
    public:
    Cplayer(float x, float y, int id=0, PLAYER::controls controls=PLAYER::DEFAULT_CONTROLS);
    PLAYER::STEP step(Cloader &loader, Uint8* keyboardState, std::vector<Cbullet*> &bullets, std::vector<CplayerBullet*> &playerBullets, std::vector<Cbomb*> &bombs, std::vector<Cenemy*> &enemies, CparticleController &particleController);    OPENGL::vanillaPoint* draw(Copengl &opengl, OPENGL::vanillaPoint* freeSpace);
    bool die(Cloader &loader, CparticleController &particleController);

    int get_lives();
    int get_bomb_count();
    float get_x();
    float get_y();

    private:
    bool handleCollisions(Cloader &loader, std::vector<Cbullet*> &bullets, std::vector<Cenemy*> &enemies, CparticleController &particleController);
    void respawn();

    float x;
    float y;
    int id;
    PLAYER::controls controls;
    float startX;
    float startY;
    int lives;
    int bombCount;
    int invincible;
    int bombRefreshTime;
    bool isDead;
    bool shouldFlicker;
    int respawnTimer;
    int timeUntilShoot;
};
