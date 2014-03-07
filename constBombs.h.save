#pragma once

#include "constText.h"
#include "Copengl.h"
#include "constImages.h"

/*
The constants relating to the bombs counter class which
draws the player's bombs to the screen
*/

namespace BOMBS {
    //The text that will be placed to the left of the lives
    //Should be in all caps and use no special chars other than ':'
    const char* const TEXT = "BOMBS:";
    //The length of the above text (not counting the null termination)
    const int LENGTH_OF_TEXT = 6;
    //The number of digits that the bombs should be shown to.
    //for example "2" would give bombs as 03 instead of 3 etc.
    const int PLACES = 1;

    //The coordinates of the top left of the bombs in Opengl coordinates.
    const float X = OPENGL::RIGHT_SIDE_X-Copengl::convert_pixel_width(2) -
                    PLACES * Copengl::convert_pixel_width(IMAGES::DIGITS::WIDTH + TEXT::SPACING + TEXT::DIGIT_PADDING_X + TEXT::DIGIT_EXTRA_SPACING) -
                    LENGTH_OF_TEXT*Copengl::convert_pixel_width(IMAGES::LETTERS::WIDTH+TEXT::SPACING);
    const float Y = OPENGL::TOP_Y-Copengl::convert_pixel_height(2+IMAGES::LETTERS::HEIGHT);
}
