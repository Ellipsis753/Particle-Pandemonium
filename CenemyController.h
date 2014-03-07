#pragma once

#include <stdio.h>
#include <vector>

#include "constEnemyController.h"
#include "Cenemy.h"
#include "Cbullet.h"
#include "bulletPatternsAndEnemyMacros.h"

class CenemyController {
    public:
    CenemyController();
    bool step(std::vector<Cenemy*> &enemies, std::vector<Cbullet*> &bullets);

    void set_level(int level);
    int get_level();


    private:
    Cenemy* pixels_create_enemy(int x, int y, int aimX, int aimY,
        ENEMY::TYPE type=ENEMY::TYPE::DEFAULT, int hp=1, float speed=ENEMY::DEFAULT_SPEED);
    bool step_level_1(std::vector<Cenemy*> &enemies, std::vector<Cbullet*> &bullets);

    int level;
    int stepCount;
};

inline
Cenemy* CenemyController::pixels_create_enemy(int x, int y, int aimX, int aimY, ENEMY::TYPE type, int hp, float speed) {
    return new Cenemy(OPENGL::LEFT_SIDE_X+Copengl::convert_pixel_width(x), OPENGL::TOP_Y-Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT+y),
        OPENGL::LEFT_SIDE_X+Copengl::convert_pixel_width(aimX), OPENGL::TOP_Y-Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT+aimY),
        type, hp, speed);
}
