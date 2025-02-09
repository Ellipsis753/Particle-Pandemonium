#pragma once

/*
The constants relating to how stars are generated and drawn
*/

namespace STAR_CONTROLLER {
    //The speed that the stars move down the screen at. Given in OpenGL coordinates
    const float STAR_SPEED = 0.005f;
    //1 in X chance of making a star each frame
    const int STAR_GENERATION = 1;
    //added to each star speed is a random number between 0 and this.
    //This is used to emulate parallax of the stars and make them appear to be 3d.
    const float STAR_SPEED_RANDOM_MAX = 0.0003f;
    //The range of values that the stars would have as there brightness
    const float STAR_BRIGHTNESS_MIN = 0.1f;
    const float STAR_BRIGHTNESS_MAX = 1.0f;
    //The range of amounts that each star will randomly have taken from its different
    //colour elements (red green and blue).
    //For example a star which would otherwise have had 1.0 red, green and blue would
    //have a random number in this range taken from each element and might give something
    //like 0.98 for red, 0.96 for green and 0.92 for blue.
    //This is so that stars appear slightly off white sometimes to emulate different types
    //of stars and the effects that dopper shift could have on their perceived colour
    const float STAR_COLOUR_REDUCTION_MIN = 0.0f;
    const float STAR_COLOUR_REDUCTION_MAX = 0.1f;
}
