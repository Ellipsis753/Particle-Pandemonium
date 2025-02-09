#pragma once

#include "Copengl.h"

/*
The constants relating the text class. Which is used to draw text and digits to the screen.
*/

namespace TEXT {
    //The depth that the text should be drawn at.
    const float DEPTH = 0.2f;
    //The spacing in pixels between each character.
    const int SPACING = 1;
    //The default number of digits that a number should be drawn to.
    //The number will be padded with 0s at the begging if it is not large enough.
    //For example if NUM_DIGITS is set to 4 and the number "34" is drawn then it will
    //be drawn as "0034".
    const int NUM_DIGITS = 10;
    //The value of a colon as they come out of ASCII order.
    const char COLON = 'Z'+1;

    //Because the numbers are smaller than the letters they must be padded so they
    //blend well when used with letters. (To keep everything fixed width)
    const int DIGIT_PADDING_X = 2;
    const int DIGIT_PADDING_Y = 1;
    //The extra padding digits need after themself to make up for their smaller horizontal size
    const int DIGIT_EXTRA_SPACING = 3;
}
