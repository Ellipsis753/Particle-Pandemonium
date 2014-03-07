#pragma once

#include "constText.h"
#include "constOpengl.h"

/*
The constants relating to the score counter class which keeps
track of the player's score and draws to the screen.
*/

namespace SCORE {
    //The number of extra 0s to render on the end of the score
    //this is so that the score seems larger to impress players
    //without actually having to deal with and store huge numbers.
    //I.E if EXTRA_ZEROS is 2 then a score of 1 will be drawn as 100.
    const int EXTRA_ZEROS = 2;

    //The coordinates of the top left of the score in Opengl coordinates.
    const float X = OPENGL::LEFT_SIDE_X+Copengl::convert_pixel_width(2);
    const float Y = OPENGL::TOP_Y-Copengl::convert_pixel_height(2);

    //The text that will be placed to the left of the score
    //Should be in all caps and use no special chars other than ':'
    const char* const TEXT = "SCORE:";
    //The length of the above text (not counting the null termination)
    const int LENGTH_OF_TEXT = 6;
}
