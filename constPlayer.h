#pragma once

#include "Copengl.h"

/*
All constants relating to the player class.
*/

namespace PLAYER {
    //The depth that the player will be drawn at.
    const float DEPTH = 0.99f;
    //The default number of lives that a player will start with.
    const int LIVES = 3;
    //The default number of bombs that a player will start with.
    const int BOMBS = 3;
    //The wait in frames before the a killed player will respawn.
    const int FRAMES_UNTIL_RESPAWN = 90;
    //The amount of extra time that the player will wait before the game ends after loosing all lives
    const int EXTRA_DELAY_AFTER_DEATH = 200-FRAMES_UNTIL_RESPAWN;

    //Amount of time in frames you are invincible after respawning
    const int SPAWN_INVINCIBILITY = 160;
    //Amount of time in frames to flicker for while invincible (2 is 2 frames on then 2 off etc.)
    const int FLICKER_SPEED = 3;
    //The default position the player spawns at in OpenGL units
    const float SPAWN_X = OPENGL::CENTRE_X;
    const float SPAWN_Y = OPENGL::BOTTOM_Y+Copengl::convert_pixel_height(100);

    //The speeds that the player will move in each direction given in OpenGL coordinates.
    const float LEFT_SPEED = Copengl::convert_pixel_width(5);
    const float RIGHT_SPEED = Copengl::convert_pixel_width(5);
    const float UP_SPEED = Copengl::convert_pixel_height(5);
    const float DOWN_SPEED = Copengl::convert_pixel_height(5);

    //The offset of players hitbox from its top left. The player has a hitbox of only 1 point.
    const float HITBOX_OFFSET_X = Copengl::convert_pixel_width(-5);
    const float HITBOX_OFFSET_Y = Copengl::convert_pixel_height(7);

    //the time in frames until the next bullet can be fired.
    const int SHOT_COOLDOWN = 6;

    //the colour of the particles in the explosion when the player dies.
    const float EXPLOSION_RED = 1.0f;
    const float EXPLOSION_GREEN = 1.0f;
    const float EXPLOSION_BLUE = 1.0f;

    //the number of particles to create when the player dies
    const int PARTICLES = 10000;

    //The data structure for storing the player's controls.
    struct controls {
        const SDLKey left;
        const SDLKey right;
        const SDLKey up;
        const SDLKey down;
        const SDLKey shoot;
        const SDLKey bomb;
    };

    //The default controls for the player.
    const PLAYER::controls DEFAULT_CONTROLS = {
        SDLK_LEFT,
        SDLK_RIGHT,
        SDLK_UP,
        SDLK_DOWN,
        SDLK_z,
        SDLK_x
    };


    //possible return values from step
    enum STEP {
        ERROR_ENCOUNTERED,
        OK,
        DELETE_ME
    };
}
