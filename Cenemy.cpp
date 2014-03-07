#include "Cenemy.h"

//We must compensate to make it as if the origin was at the centre of the enemy.
Cenemy::Cenemy(float x, float y, float aimX, float aimY, ENEMY::TYPE type, int hp, float speed): x(x-(Copengl::convert_pixel_width(IMAGES::ENEMY::WIDTH)/2.0f)), y(y+(Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT)/2.0f)), previousX(x), previousY(y), type(type), hp(hp), speed(speed), xSpeed(0), ySpeed(0), framesTillStop(0), frame(0), actionQueue() {
    set_aim(aimX, aimY, speed);
}

Cenemy::Cenemy(float x, float y, ENEMY::TYPE type, int hp, float speed): x(x-(Copengl::convert_pixel_width(IMAGES::ENEMY::WIDTH)/2.0f)), y(y+(Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT)/2.0f)), previousX(x), previousY(y), type(type), hp(hp), speed(speed), xSpeed(0), ySpeed(0), framesTillStop(0), frame(0), actionQueue() {
    set_aim(x, y, speed);
}

ENEMY::STEP Cenemy::step(Cloader &loader, std::vector<CplayerBullet*> &playerBullets, std::vector<Cbullet*> &bullets, CparticleController &particleController, Cscore &score, float playerX, float playerY) {
    previousX = x;
    previousY = y;
    if (framesTillStop > 0) {
        framesTillStop--;
        x += xSpeed;
        y += ySpeed;
    }

    for (std::vector<CplayerBullet*>::iterator iter = playerBullets.begin(); iter != playerBullets.end();) {
        float bulletX = (*iter)->get_x();
        float bulletY = (*iter)->get_y();

        if (y-Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT) < bulletY && y > bulletY-Copengl::convert_pixel_height(IMAGES::PLAYER_BULLET::HITBOX_HEIGHT) &&
            x < bulletX+Copengl::convert_pixel_width(IMAGES::PLAYER_BULLET::HITBOX_WIDTH) && x+Copengl::convert_pixel_width(IMAGES::ENEMY::WIDTH) > bulletX) {
            //hit so destroy bullet and remove 1 hp
            hp--;
            iter = playerBullets.erase(iter);
        } else {
            iter++;
        }
    }

    if (hp <= 0) {
        //ask to be deleted
        Csound::play_effect(loader.get_explosion_effect());
        if (die(loader, particleController, score) == false) {
            return ENEMY::STEP::ERROR_ENCOUNTERED;
        }
        return ENEMY::STEP::DELETE_ME;
    }

    if (do_actions(bullets, playerX, playerY) == false) {
        //has requested to be deleted
        return ENEMY::STEP::DELETE_ME;
    }

    frame++;
    return ENEMY::STEP::OK;
}

OPENGL::vanillaPoint* Cenemy::draw(Copengl &opengl, OPENGL::vanillaPoint* freeSpace) {
    return opengl.add_rectangle(x, y, ENEMY::DEPTH,
                            opengl.convert_pixel_width(IMAGES::ENEMY::WIDTH), opengl.convert_pixel_height(IMAGES::ENEMY::HEIGHT),
                            IMAGES::ENEMY::TEX_X+(type*IMAGES::ENEMY::TEX_W), IMAGES::ENEMY::TEX_Y,
                            IMAGES::ENEMY::TEX_W, IMAGES::ENEMY::TEX_H, freeSpace);
}

bool Cenemy::die(Cloader &loader, CparticleController &particleController, Cscore &score) {
    float xSpeed = x-previousX;
    float ySpeed = y-previousY;

    if (particleController.make_ready_to_add() == false) {
        return false;
    }
    for (int iii = 0; iii < ENEMY::PARTICLES; iii++) {
        float red = rand()/float(RAND_MAX);
        float green = rand()/float(RAND_MAX);
        float blue = rand()/float(RAND_MAX);

        std::default_random_engine* randomEngine = loader.get_random_engine();
        std::uniform_real_distribution<float> widthDistribution(0.0f, Copengl::convert_pixel_width(IMAGES::ENEMY::WIDTH));
        std::uniform_real_distribution<float> heightDistribution(0.0f, Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT));

        particleController.add_explosion_particle(loader, x+widthDistribution(*randomEngine), y-heightDistribution(*randomEngine),
                                                  red, green, blue, xSpeed, ySpeed);
    }
    particleController.finish_adding();
    score.add(ENEMY::SCORE);
    return true;
}

void Cenemy::set_aim(float aimX, float aimY, float speed) {
    float xDif = aimX - x;
    float yDif = aimY - y;
    float distance = sqrt(xDif*xDif + yDif*yDif);
    float time = distance/speed;
    framesTillStop = ceil(time);
    xSpeed = xDif/time;
    ySpeed = yDif/time;
}

void Cenemy::add_action(unsigned int minFrame, ENEMY::EVENT event, float angleOffset, float x, float y, float speed) {
    ENEMY::action action;
    action.minFrame = minFrame;
    action.event = event;
    action.angleOffset = angleOffset;
    action.x = x;
    action.y = y;
    action.speed = speed;
    actionQueue.push_back(action);
}

bool Cenemy::do_actions(std::vector<Cbullet*> &bullets, float playerX, float playerY) {
    while (actionQueue.size() != 0 && actionQueue[0].minFrame <= frame) {
        //the action is due. Do it.
        switch (actionQueue[0].event) {
            case ENEMY::MOVE_AT: {
                //We compensate as to line up the aim with the centre of the enemy
                if (actionQueue[0].speed == 0.0f) {
                    //use default speed
                    set_aim(actionQueue[0].x-(Copengl::convert_pixel_width(IMAGES::ENEMY::WIDTH)/2.0f), actionQueue[0].y+(Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT)/2.0f));
                } else {
                    //use specified speed
                    set_aim(actionQueue[0].x-(Copengl::convert_pixel_width(IMAGES::ENEMY::WIDTH)/2.0f), actionQueue[0].y+(Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT)/2.0f), actionQueue[0].speed);
                }
            }
            break;

            case ENEMY::SHOOT_PLAYER: {
                actionQueue[0].x = playerX;
                actionQueue[0].y = playerY;
            }
            //Fall through (on purpose!)

            case ENEMY::SHOOT_AT: {
                float speed = 0.0f;
                if (actionQueue[0].speed == 0.0f) {
                    speed = BULLET::SPEED;
                } else {
                    speed = actionQueue[0].speed;
                }

                float xDif = actionQueue[0].x-(x+(Copengl::convert_pixel_width(IMAGES::ENEMY::WIDTH)/2.0f));
                float yDif = actionQueue[0].y-(y-(Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT)/2.0f));
                float distance = sqrt(xDif*xDif + yDif*yDif);
                float time = distance/speed;

                float bulletXSpeed = xDif/time;
                float bulletYSpeed = yDif/time;

                if (actionQueue[0].angleOffset != 0.0f) {
                    float angle = atan2(bulletYSpeed, bulletXSpeed);
                    angle += actionQueue[0].angleOffset;
                    bulletXSpeed = speed*sin(angle);
                    bulletYSpeed = speed*cos(angle);
                }

                bullets.push_back(new Cbullet(x+(Copengl::convert_pixel_width(IMAGES::ENEMY::WIDTH)/2.0f), y-(Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT)/2.0f), bulletXSpeed, bulletYSpeed));
            }
            break;

            case ENEMY::CREATE_BULLET: {
                bullets.push_back(new Cbullet(x+(Copengl::convert_pixel_width(IMAGES::ENEMY::WIDTH)/2.0f), y-(Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT)/2.0f), actionQueue[0].x, actionQueue[0].y));
            }
            break;

            case ENEMY::SHOOT_ANGLE: {
                float angle = actionQueue[0].x;
                float speed = 0.0f;
                if (actionQueue[0].speed == 0.0f) {
                    speed = BULLET::SPEED;
                } else {
                    speed = actionQueue[0].speed;
                }

                float bulletXSpeed = speed * OPENGL::PIXEL_RATIO_WIDTH_BY_HEIGHT;
                float bulletYSpeed = speed;

                bulletXSpeed = bulletXSpeed*sin(angle);
                bulletYSpeed = bulletYSpeed*cos(angle);
                bullets.push_back(new Cbullet(x+(Copengl::convert_pixel_width(IMAGES::ENEMY::WIDTH)/2.0f), y-(Copengl::convert_pixel_height(IMAGES::ENEMY::HEIGHT)/2.0f), bulletXSpeed, bulletYSpeed));
            }
            break;

            case ENEMY::DELETE_SELF: {
                return false;
            }
            break;

            default: {
                //This should never happen
                fprintf(stderr, "Unexpected enemy event: %d.\n", actionQueue[0].event);
            }
            break;
        }
        //remove the event now that it has been executed.
        actionQueue.erase(actionQueue.begin());
    }
    return true;
}

float Cenemy::get_x() {
    return x;
}

float Cenemy::get_y() {
    return y;
}
