#pragma once

#include "Copengl.h"

/*
The positions and dimensions of each of the buttons on tutorial screen
*/

namespace TUTORIAL {
    namespace BACK {
        const float X = Copengl::convert_to_opengl_x(0);
        const float Y = Copengl::convert_to_opengl_y(0);
        const float W = Copengl::convert_pixel_width(70);
        const float H = Copengl::convert_pixel_height(72);
    }
}

