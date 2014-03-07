#include "Cbomb.h"

Cbomb::Cbomb(float x, float y): x(x), y(y), life(BOMB::LIFE) {
    //empty
}

BOMB::STEP Cbomb::step(Cscore &score, Cloader &loader, CparticleController &particleController, std::vector<Cenemy*> &enemies, std::vector<Cbullet*> &bullets) {
    if (life <= 0) {
        if (explode(score, loader, particleController, enemies, bullets) == false) {
            //error
            return BOMB::ERROR_ENCOUNTERED;
        }
        if (life <= 0-BOMB::LIFE_AFTER_EXPLODING) {
            //ask to be deleted
            return BOMB::DELETE_ME;
        }
    } else {
        y += BOMB::SPEED;
    }

    life--;

    return BOMB::OK;
}

OPENGL::vanillaPoint* Cbomb::draw(Copengl &opengl, OPENGL::vanillaPoint* freeSpace) {
    if (life > 0) {
        return opengl.add_rectangle(x, y, BOMB::DEPTH,
                                opengl.convert_pixel_width(IMAGES::BOMB::WIDTH), opengl.convert_pixel_height(IMAGES::BOMB::HEIGHT),
                                IMAGES::BOMB::TEX_X, IMAGES::BOMB::TEX_Y,
                                IMAGES::BOMB::TEX_W, IMAGES::BOMB::TEX_H, freeSpace);
    }
    return freeSpace;
}

bool Cbomb::explode(Cscore &score, Cloader &loader, CparticleController &particleController, std::vector<Cenemy*> &enemies, std::vector<Cbullet*> &bullets) {
    float bombCentreX = x+(Copengl::convert_pixel_width(IMAGES::BOMB::WIDTH)/2);
    float bombCentreY = y-(Copengl::convert_pixel_height(IMAGES::BOMB::HEIGHT)/2);

    //Only create particles for the first bit after exploding. After the bomb just sticks around to destroy enemies and bullets.
    if (life > -BOMB::EXPLODING_FRAMES) {
        if (particleController.make_ready_to_add() == false) {
            return false;
        }
        for (int iii = 0; iii < BOMB::PARTICLES; iii++) {
            particleController.add_explosion_particle(loader, bombCentreX, bombCentreY);
        }
        particleController.finish_adding();
    }

    //Destroy things that the bomb hits
    for (std::vector<Cenemy*>::iterator iter = enemies.begin(); iter != enemies.end();) {
        //get distance between us
        float xDifference = (((*iter)->get_x()+(Copengl::convert_pixel_width(IMAGES::ENEMY::WIDTH)/2))-bombCentreX)*OPENGL::PIXEL_RATIO_WIDTH_BY_HEIGHT;
        float yDifference = (((*iter)->get_y()-(Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT)/2))-bombCentreY);
        float distance = sqrt(xDifference*xDifference + yDifference*yDifference);
        int framesExplodedFor = 0-life;
        //if it's caught in the blast range we kill it (also make sure it's actually on screen.
        if (distance < framesExplodedFor*PARTICLE_CONTROLLER::AVERAGE_SPEED &&
            (*iter)->get_x()+Copengl::convert_pixel_width(IMAGES::ENEMY::WIDTH) > OPENGL::LEFT_SIDE_X &&
            (*iter)->get_x() < OPENGL::RIGHT_SIDE_X && (*iter)->get_y()-Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT) < OPENGL::TOP_Y && (*iter)->get_y() > OPENGL::BOTTOM_Y) {
            //kill the enemy then destroy it.
            if ((*iter)->die(loader, particleController, score) == false) {
                return false;
            }
            //double score for bomb kills. Once here and again in the call to die() above.
            score.add(ENEMY::SCORE);
            delete (*iter);
            iter = enemies.erase(iter);
        } else {
            iter++;
        }
    }

    for (std::vector<Cbullet*>::iterator iter = bullets.begin(); iter != bullets.end();) {
        //get distance between us
        float xDifference = ((*iter)->get_x()-bombCentreX)*OPENGL::PIXEL_RATIO_WIDTH_BY_HEIGHT;
        float yDifference = ((*iter)->get_y()-bombCentreY);
        float distance = sqrt(xDifference*xDifference + yDifference*yDifference);
        int framesExplodedFor = 0-life;
        //if it's caught in the blast range we kill it
        if (distance < framesExplodedFor*PARTICLE_CONTROLLER::AVERAGE_SPEED) {
            delete (*iter);
            iter = bullets.erase(iter);
        } else {
            iter++;
        }
    }

    return true;
}
