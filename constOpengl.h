#pragma once

#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <GL/gl.h>

#include "constSdl.h"

/*
All constants and data structures relating to OpenGL.
*/

namespace OPENGL {
    //Some definitions relating to the coordinate system used.
    //In OpenGL it goes from (-1,-1) in bottom left to (1,1) in top right.
    const float LEFT_SIDE_X = -1.0f;
    const float RIGHT_SIDE_X = 1.0f;
    const float TOP_Y = 1.0f;
    const float BOTTOM_Y = -1.0f;
    const float SCREEN_WIDTH = RIGHT_SIDE_X-LEFT_SIDE_X;
    const float SCREEN_HEIGHT = TOP_Y-BOTTOM_Y;
    const float CENTRE_X = LEFT_SIDE_X+(SCREEN_WIDTH/2);
    const float CENTRE_Y = BOTTOM_Y+(SCREEN_HEIGHT/2);

    //The default background colour to clear the screen with
    const float CLEAR_COLOUR_RED = 1.0f;
    const float CLEAR_COLOUR_GREEN = 1.0f;
    const float CLEAR_COLOUR_BLUE = 1.0f;
    const float CLEAR_COLOUR_ALPHA = 1.0f;

    //As opengl uses a coordinate system from -1 to 1 an on screen pixel is not 1.
    //A pixel is defined in the OpenGL coordinate system by the lines below.
    //As the window is not square a pixel on screen is a different amount
    //horizontally than vertically
    const float PIXEL_WIDTH = OPENGL::SCREEN_WIDTH/SDL::SCREEN_WIDTH;
    const float PIXEL_HEIGHT = OPENGL::SCREEN_HEIGHT/SDL::SCREEN_HEIGHT;

    //A ratio of the width to the height. It is needed to ajust some calculations
    //that assume a pixel has the same width as height.
    const float PIXEL_RATIO_WIDTH_BY_HEIGHT = PIXEL_WIDTH/PIXEL_HEIGHT;

    /*
    Some definitions of data structions used for OpenGL.
    */

    //A 3d position in OpenGL coordinates
    struct position {
        GLfloat x;
        GLfloat y;
        GLfloat z;
    };

    //A texture position, in OpenGL coordinates
    struct texture {
        GLfloat x;
        GLfloat y;
    };

    //A single 3d point and texture position. These are passed to the
    //Vanilla shader program and will act as 1 textured vertex of a triangle.
    struct vanillaPoint {
        position pos;
        texture tex;
    };

    //A 2d position in OpenGl coordinates
    struct position2d {
        GLfloat x;
        GLfloat y;
    };

    //A 2d speed vector given in OpenGL coordinates.
    //It is the distance to travel on the x and y planes in a single frame.
    struct speed2d {
        GLfloat x;
        GLfloat y;
    };

    //A colour data structure without an alpha channel. It defines the colour of something.
    struct colour {
        GLfloat r;
        GLfloat g;
        GLfloat b;
    };

    //A single point of a particle. This structure is passed to the particle shader program and
    //is used to render a single particle point.
    struct particlePoint {
        position2d pos2d;
        speed2d spd2d;
        colour col;
    };
}
