#include "CplayerBullet.h"

CplayerBullet::CplayerBullet(float x, float y): x(x), y(y) {
    //empty
}

bool CplayerBullet::step() {
    y += PLAYER_BULLET::SPEED;
    //ask to be destroyed if gone offscreen
    if (y-Copengl::convert_pixel_height(IMAGES::PLAYER_BULLET::HEIGHT) > OPENGL::TOP_Y) {
        return true;
    }
    return false;
}

OPENGL::vanillaPoint* CplayerBullet::draw(Copengl &opengl, OPENGL::vanillaPoint* freeSpace) {
    return opengl.add_rectangle(x, y, PLAYER_BULLET::DEPTH,
                            opengl.convert_pixel_width(IMAGES::PLAYER_BULLET::WIDTH), opengl.convert_pixel_height(IMAGES::PLAYER_BULLET::HEIGHT),
                            IMAGES::PLAYER_BULLET::TEX_X, IMAGES::PLAYER_BULLET::TEX_Y,
                            IMAGES::PLAYER_BULLET::TEX_W, IMAGES::PLAYER_BULLET::TEX_H, freeSpace);
}

float CplayerBullet::get_x() {
    return x;
}

float CplayerBullet::get_y() {
    return y;
}
