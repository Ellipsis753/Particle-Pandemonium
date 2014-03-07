#pragma once

#include <cmath>

#include "Copengl.h"
#include "constImages.h"
#include "constBullet.h"

class Cbullet {
    public:
    Cbullet(float x, float y, float xSpeed, float ySpeed);
    bool step();
    OPENGL::vanillaPoint* draw(Copengl &opengl, OPENGL::vanillaPoint* freeSpace, float z);
    float get_x();
    float get_y();

    private:
    float x;
    float y;
    float xSpeed;
    float ySpeed;
};

inline
bool Cbullet::step() {
    x+=xSpeed;
    y+=ySpeed;

    //ask to be destroyed if gone offscreen
    if (x-(Copengl::convert_pixel_width(IMAGES::BULLET::WIDTH)/2) > OPENGL::RIGHT_SIDE_X || x+(Copengl::convert_pixel_width(IMAGES::BULLET::WIDTH)/2) < OPENGL::LEFT_SIDE_X ||
        y-(Copengl::convert_pixel_height(IMAGES::BULLET::HEIGHT)/2) > OPENGL::TOP_Y || y+(Copengl::convert_pixel_height(IMAGES::BULLET::HEIGHT)/2) < OPENGL::BOTTOM_Y) {
        return true;
    }
    return false;
}

inline
OPENGL::vanillaPoint* Cbullet::draw(Copengl &opengl, OPENGL::vanillaPoint* freeSpace, float z) {
    return opengl.add_rectangle(x-opengl.convert_pixel_width(IMAGES::BULLET::WIDTH)/2, y+opengl.convert_pixel_height(IMAGES::BULLET::HEIGHT)/2, z,
                                opengl.convert_pixel_width(IMAGES::BULLET::WIDTH), opengl.convert_pixel_height(IMAGES::BULLET::HEIGHT),
                                IMAGES::BULLET::TEX_X, IMAGES::BULLET::TEX_Y,
                                IMAGES::BULLET::TEX_W, IMAGES::BULLET::TEX_H, freeSpace);
}
