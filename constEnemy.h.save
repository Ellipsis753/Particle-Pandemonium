#pragma once

namespace ENEMY {
    //The speed that an enemy will move at (per frame) by default (if not set in the constructor)
    const float DEFAULT_SPEED = Copengl::convert_pixel_width(3);
    //The depth that the enemy will be rendered at
    const float DEPTH = 0.4f;
    //The number of particles for the enemy to create when it dies
    const int PARTICLES = 4000;
    //The amount to increase your score by when the enemy is killed
    const int SCORE = 10;

    //This different types of enemy (each has its own graphics)
    enum TYPE {
        DEFAULT,
        SPECIAL,
        SUPER
    };

    //possible return values from step
    //A windows related libary defines ERROR and so I cannot use it here.
    enum STEP {
        ERROR_ENCOUNTERED,
        OK,
        DELETE_ME
    };

    //Actions that the enemy can do
    //Each has a frame (counted from 0 upwards from enemy creation) that must be at least met for the action to take place.
    //They also have an event. This is what they will do.
    //They also have an x y and speed which may or may not be used for that event.
    //The centre of the enemy is taken as it's origin in the commands below.
    //MOVE_AT will start moving the enemy towards the point specified by x and y at speed set by speed. Or the default speed if speed is set to 0.
    //SHOOT_AT will create a bullet and fire it towards the point specified by x and y, speed of the bullet is set by speed or will use default speed is set to 0.
    //CREATE_BULLET will create a bullet and give it the speedX and speedY specified by x and y, speed is ignored.
    //SHOOT_PLAYER will fire a bullet at the player with speed, speed or default if speed is set to 0.
    //SHOOT_ANGLE will shoot at the angle x with speed, speed. y is ignored. (if speed is 0 then default speed will be used).
    //DELETE_SELF will cause the enemy to delete itself without creating an explosion or increasing the players score.
    enum EVENT {
        MOVE_AT,
        SHOOT_AT,
        CREATE_BULLET,
        SHOOT_PLAYER,
        SHOOT_ANGLE,
        DELETE_SELF
    };

    struct action {
        unsigned int minFrame;
        EVENT event;
        float x;
        float y;
        float speed;
        float angleOffset;
    };
}
