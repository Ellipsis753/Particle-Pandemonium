#pragma once

#include "Copengl.h"
#include "constEnemy.h"

/*
constants relating to the bombs that the player makes.
*/

namespace BOMB {
    //The depth that the bombs will be rendered at.
    const float DEPTH = 0.45f;
    //The speed that the bombs will move upwards at in OpenGL coordinates moved per frame.
    const float SPEED = Copengl::convert_pixel_height(7);
    //The lifespan of a bomb before exploding (in frames)
    const int LIFE = 30;
    //Number of particles to create each frame while exploding
    const int PARTICLES = 500;
    //Number of frames to explode for
    const int EXPLODING_FRAMES = 30;
    //The frames that a bomb should hang around for after exploding
    //should be long enough to ensure the screen is cleared.
    const int LIFE_AFTER_EXPLODING = 200;

    //possible return values from step
    enum STEP {
        ERROR_ENCOUNTERED,
        OK,
        DELETE_ME
    };
    //the score gained for killing an enemy with a bomb
    //Double points for killing an enemy with a bomb.
    const int ENEMY_KILL_SCORE = ENEMY::SCORE * 2;
}
