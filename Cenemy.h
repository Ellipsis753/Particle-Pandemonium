#pragma once

#include <vector>
#include <cmath>
#include <stdio.h>

#include "Copengl.h"
#include "Cbullet.h"
#include "constOpengl.h"
#include "constEnemy.h"
#include "CparticleController.h"
#include "CplayerBullet.h"
#include "Cloader.h"
#include "Cscore.h"
#include "Cbullet.h"
#include "constImages.h"

class Cenemy {
    public:
    Cenemy(float x, float y, float aimX, float aimY, ENEMY::TYPE type=ENEMY::TYPE::DEFAULT, int hp=1, float speed=ENEMY::DEFAULT_SPEED);
    Cenemy(float x, float y, ENEMY::TYPE type=ENEMY::TYPE::DEFAULT, int hp=1, float speed=ENEMY::DEFAULT_SPEED);

    ENEMY::STEP step(Cloader &loader, std::vector<CplayerBullet*> &playerBullets, std::vector<Cbullet*> &bullets, CparticleController &particleController, Cscore &score, float playerX, float playerY);
    bool die(Cloader &loader, CparticleController &particleController, Cscore &score);
    OPENGL::vanillaPoint* draw(Copengl &opengl, OPENGL::vanillaPoint* freeSpace);
    void set_aim(float aimX, float aimY, float speed=ENEMY::DEFAULT_SPEED);
    void add_action(unsigned int minFrame, ENEMY::EVENT event, float angleOffset=0.0f, float x=0.0f, float y=0.0f, float speed=5.0f);
    void move_at_pixels(unsigned int frame, int x, int y, float speed=0.0f);
    void shoot_player(unsigned int frame, float angleOffset=0.0f, float speed=0.0f);
    void shoot_at(unsigned int frame, int x, int y, float angleOffset=0.0f, float speed=0.0f);
    void shoot_angle(unsigned int frame, float angle, float speed=0.0f);
    void delete_self(unsigned int frame);

    float get_x();
    float get_y();

    private:
    bool do_actions(std::vector<Cbullet*> &bullets, float playerX, float playerY);

    float x;
    float y;
    float previousX;
    float previousY;
    ENEMY::TYPE type;
    int hp;
    float speed;
    float xSpeed;
    float ySpeed;
    int framesTillStop;
    unsigned int frame;
    std::vector<ENEMY::action> actionQueue;
};


inline
void Cenemy::move_at_pixels(unsigned int frame, int x, int y, float speed) {
    add_action(frame, ENEMY::MOVE_AT, 0.0f, OPENGL::LEFT_SIDE_X+Copengl::convert_pixel_width(x), OPENGL::TOP_Y-Copengl::convert_pixel_height(y), speed);
}

inline
void Cenemy::shoot_player(unsigned int frame, float angleOffset, float speed) {
    add_action(frame, ENEMY::SHOOT_PLAYER, angleOffset, 0.0f, 0.0f, speed);
}

inline
void Cenemy::shoot_at(unsigned int frame, int x, int y, float angleOffset, float speed) {
    add_action(frame, ENEMY::SHOOT_AT, angleOffset, OPENGL::LEFT_SIDE_X+Copengl::convert_pixel_width(x), OPENGL::TOP_Y-Copengl::convert_pixel_height(y), speed);
}

inline
void Cenemy::shoot_angle(unsigned int frame, float angle, float speed) {
    add_action(frame, ENEMY::SHOOT_ANGLE, angle, 0.0f, 0.0f, speed);
}

inline
void Cenemy::delete_self(unsigned int frame) {
    add_action(frame, ENEMY::DELETE_SELF);
}

