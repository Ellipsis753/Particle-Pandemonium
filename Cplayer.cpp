#include "Cplayer.h"

Cplayer::Cplayer(float x, float y, int id, PLAYER::controls controls): x(x), y(y), id(id), controls(controls), startX(x), startY(y), lives(PLAYER::LIVES), bombCount(PLAYER::BOMBS), invincible(PLAYER::SPAWN_INVINCIBILITY), bombRefreshTime(0), isDead(false), shouldFlicker(true), respawnTimer(0), timeUntilShoot(PLAYER::SHOT_COOLDOWN) {
    respawn();
}

PLAYER::STEP Cplayer::step(Cloader &loader, Uint8* keyboardState, std::vector<Cbullet*> &bullets, std::vector<CplayerBullet*> &playerBullets, std::vector<Cbomb*> &bombs, std::vector<Cenemy*> &enemies, CparticleController &particleController) {
    if (lives < 0) {
        //out of lives, game over
        //but wait a little so they can see they died
        if (respawnTimer < -PLAYER::EXTRA_DELAY_AFTER_DEATH) {
            //They have waited long enough. End game.
            return PLAYER::DELETE_ME;
        } else {
            respawnTimer--;
        }
        //Don't delete yet so they can see what happened.
        return PLAYER::OK;
    }

    if (isDead == true) {
        if (respawnTimer == 0) {
            respawn();
        } else {
            respawnTimer--;
            //do nothing as they're dead
            return PLAYER::OK;
        }

    }

    if (keyboardState[controls.left] == true) {
        x -= PLAYER::LEFT_SPEED;
    }
    if (keyboardState[controls.right] == true) {
        x += PLAYER::RIGHT_SPEED;
    }
    if (keyboardState[controls.up] == true) {
        y += PLAYER::UP_SPEED;
    }
    if (keyboardState[controls.down] == true) {
        y -= PLAYER::DOWN_SPEED;
    }

    //Keep in bounds
    if (x > OPENGL::RIGHT_SIDE_X) {
        x = OPENGL::RIGHT_SIDE_X-OPENGL::PIXEL_WIDTH;
    } else if (x < OPENGL::LEFT_SIDE_X) {
        x = OPENGL::LEFT_SIDE_X;
    }
    if (y < OPENGL::BOTTOM_Y) {
        y = OPENGL::BOTTOM_Y;
    } else if (y > OPENGL::TOP_Y) {
        y = OPENGL::TOP_Y-OPENGL::PIXEL_HEIGHT;
    }

    if (keyboardState[controls.bomb] == true && bombCount > 0 && bombRefreshTime == 0) {
        bombs.push_back(new Cbomb(x-(Copengl::convert_pixel_width(IMAGES::BOMB::WIDTH)/2), y+Copengl::convert_pixel_height(IMAGES::BOMB::HEIGHT)));
        bombCount--;
        bombRefreshTime = 30;
        shouldFlicker = false;
        invincible = BOMB::LIFE+BOMB::LIFE_AFTER_EXPLODING;
        Csound::play_effect(loader.get_bomb_effect());
    }

    if (invincible == 0) {
        if (handleCollisions(loader, bullets, enemies, particleController) == false) {
            return PLAYER::ERROR_ENCOUNTERED;
        }
    } else {
        invincible--;
    }

    if (timeUntilShoot == 0) {
        if (keyboardState[controls.shoot] == true) {
            Csound::play_effect(loader.get_laser_effect());
            playerBullets.push_back(new CplayerBullet(x-(Copengl::convert_pixel_width(IMAGES::PLAYER_BULLET::WIDTH)/2), y+Copengl::convert_pixel_height(IMAGES::PLAYER::HEIGHT)+(Copengl::convert_pixel_height(IMAGES::PLAYER_BULLET::HEIGHT)/2)));
            timeUntilShoot = PLAYER::SHOT_COOLDOWN;
        }
    } else {
        timeUntilShoot--;
    }

    if (bombRefreshTime > 0) {
        bombRefreshTime--;
    }

    return PLAYER::OK;
}

OPENGL::vanillaPoint* Cplayer::draw(Copengl &opengl, OPENGL::vanillaPoint* freeSpace) {
    //Don't draw them if they're dead or on every other frame when invincible (so they flicker)
    if (isDead == false && (shouldFlicker == false || ((invincible/PLAYER::FLICKER_SPEED) % 2) == 0)) {
        return opengl.add_rectangle(x+PLAYER::HITBOX_OFFSET_X, y+PLAYER::HITBOX_OFFSET_Y, PLAYER::DEPTH,
                                    opengl.convert_pixel_width(IMAGES::PLAYER::WIDTH), opengl.convert_pixel_height(IMAGES::PLAYER::HEIGHT),
                                    IMAGES::PLAYER::TEX_X, IMAGES::PLAYER::TEX_Y,
                                    IMAGES::PLAYER::TEX_W, IMAGES::PLAYER::TEX_H, freeSpace);
    }
    return freeSpace;
}

bool Cplayer::die(Cloader &loader, CparticleController &particleController) {
    Csound::play_effect(loader.get_death_effect());
    lives--;
    isDead = true;
    respawnTimer = PLAYER::FRAMES_UNTIL_RESPAWN;

    //make particle explosion
    if (particleController.make_ready_to_add() == false) {
        return false;
    }
    for (int iii = 0; iii < PLAYER::PARTICLES; iii++) {
        particleController.add_explosion_particle(loader, x, y, PLAYER::EXPLOSION_RED, PLAYER::EXPLOSION_GREEN, PLAYER::EXPLOSION_BLUE);
    }
    particleController.finish_adding();
    return true;
}

bool Cplayer::handleCollisions(Cloader &loader, std::vector<Cbullet*> &bullets, std::vector<Cenemy*> &enemies, CparticleController &particleController) {
    for (std::vector<Cbullet*>::iterator iter = bullets.begin(); iter != bullets.end(); iter++) {
        //get distance between bullet and player
        float xDifference = ((*iter)->get_x()-x)/OPENGL::PIXEL_WIDTH;
        float yDifference = ((*iter)->get_y()-y)/OPENGL::PIXEL_HEIGHT;
        float distance = sqrt(xDifference*xDifference + yDifference*yDifference);
        if (distance < IMAGES::BULLET::RADIUS) {
            if (die(loader, particleController) == false) {
                return false;
            }
        }
    }

    for (std::vector<Cenemy*>::iterator iter = enemies.begin(); iter != enemies.end(); iter++) {
        //if you are inside an enemy you should die
        if (y > (*iter)->get_y()-Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT) && x > (*iter)->get_x() &&
            x < (*iter)->get_x()+Copengl::convert_pixel_width(IMAGES::ENEMY::WIDTH) && y < (*iter)->get_y()) {
            if (die(loader, particleController) == false) {
                return false;
            }
        }
    }
    return true;
}

void Cplayer::respawn() {
    //respawn
    x = startX;
    y = startY;
    isDead = false;
    shouldFlicker = true;
    invincible = PLAYER::SPAWN_INVINCIBILITY;
    //refill bombs
    bombCount = PLAYER::BOMBS;
}

int Cplayer::get_lives() {
    return lives;
}

int Cplayer::get_bomb_count() {
    return bombCount;
}

float Cplayer::get_x() {
    return x;
}

float Cplayer::get_y() {
    return y;
}
