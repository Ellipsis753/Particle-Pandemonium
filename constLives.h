#pragma once

#include "constText.h"
#include "Copengl.h"

/*
The constants relating to the lives counter class which
draws the player's lives to the screen
*/

namespace LIVES {
    //The text that will be placed to the left of the lives
    //Should be in all caps and use no special chars other than ':'
    const char* const TEXT = "LIVES:";
    //The length of the above text (not counting the null termination)
    const int LENGTH_OF_TEXT = 6;
    //The number of digits that the lives should be shown to.
    //for example "2" would give lives as 03 instead of 3 etc.
    const int PLACES = 1;

    //The coordinates of the top left of the lives in Opengl coordinates.
    const float X = OPENGL::RIGHT_SIDE_X-Copengl::convert_pixel_width(2) -
                    PLACES * Copengl::convert_pixel_width(IMAGES::DIGITS::WIDTH + TEXT::SPACING + TEXT::DIGIT_PADDING_X + TEXT::DIGIT_EXTRA_SPACING) -
                    LENGTH_OF_TEXT*Copengl::convert_pixel_width(IMAGES::LETTERS::WIDTH+TEXT::SPACING);
    const float Y = OPENGL::TOP_Y-Copengl::convert_pixel_height(2);
}
