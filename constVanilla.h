#pragma once

/*
Constants relating to the vanilla shader which is used for general textured rendering.
*/

namespace VANILLA {
    //The amount of space to allocate in the buffer for this many points.
    //This must be large enough for the maximum of points that vanilla is given to render in a frame.
    //For example a triangle will be 3 points and a square made from 2 triangles will require 3*2 points.
    const int MAX_POINTS = 1000000*(3*2);

    //The code for the vanilla shader program's vertex shader. It is written in GLSL.
    //This will just place the point at the position required and then pass the colour it was
    //given on to the fragment shader
    const char* const VERTEX_CODE =
    "#version 130\n"
    ""
    "in vec3 positionIn;"
    ""
    "in vec2 texturePositionIn;"
    "out vec2 texturePosition;"
    ""
    "void main() {"
        "texturePosition = texturePositionIn;"
        "gl_Position = vec4(positionIn.x, positionIn.y, positionIn.z, 1.0f);"
    "}";

    //The code for the vanilla shader program's fragment shader. It is written in GLSL.
    //This will check if the pixel to be drawn has an alpha value below a threshold.
    //If the alpha value of a pixel is below this threshold then it will not be drawn.
    //Otherwise it will be drawn fully solidly.
    //This is used because some pixels are not to be drawn and so have a low alpha value.
    //However as blending is not enabled with the vanilla shader they would normally be rendered
    //without taking the alpha value into consideration. Here they are discarded and not drawn if
    //the alpha value is too low. This is much faster than drawing with blending enabled.
    const char* const FRAGMENT_CODE =
    "#version 130\n"
    "uniform sampler2D currentTexture;"
    ""
    "in vec2 texturePosition;"
    "out vec4 fragmentColour;"
    ""
    "void main() {"
        "vec4 colour = texture(currentTexture, texturePosition);"
        "if (colour.a < 0.9) {"
            "discard;"
        "}"
        "fragmentColour = colour;"
    "}";
}
