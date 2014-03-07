#pragma once

#include "Copengl.h"

/*
The constants relating to the player's bullets
*/

namespace PLAYER_BULLET {
    //The depth that the player's bullets will be rendered at.
    const float DEPTH = 0.9f;
    //The speed that the bullets will move upwards at in OpenGL coordinates moved per frame.
    const float SPEED = Copengl::convert_pixel_height(14);
}
