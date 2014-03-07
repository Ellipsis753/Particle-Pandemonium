#pragma once

/*
Constants relating to the particle controller class
*/

namespace PARTICLE_CONTROLLER {
    //As it is very slow to generate a random explosion velocity at runtime
    //when they are created instead a large number of particle explosion velocities
    //are pre-calculated and stored for later use. This is the number to pre-generate.
    //Warning, setting this too low will cause particles to look unrelistic.
    const int NUMBER_OF_RANDOM_SPEEDS = 100000;
    //The maximum amount of points for the video card to render per frame. Enough memory
    //for this amount will be needed. If more particles are created (than can be stored)
    //the extra particles will not be stored or processed.
    const int MAX_POINTS = 500000;

    //The code for the particle shader program's vertex shader. It is written in GLSL.
    //It will automatically modify the position by adding the particles speed to it.
    //The new position will then be written back into a buffer using transform feedback.
    //This is to reduce the amount of data that needs to be sent between the CPU and GPU and
    //to offload much of the processing from the CPU to the GPU which is more suited for it.
    const char* const VERTEX_CODE =
    "#version 130\n"
    ""
    "in vec2 position2dIn;"
    "in vec2 speed2dIn;"
    "in vec3 colourIn;"
    ""
    "out vec2 position2d;"
    "out vec2 speed2d;"
    "out vec3 colour;"
    ""
    "void main() {"
        "position2d = position2dIn + speed2dIn;"
        "speed2d = speed2dIn;"
        "colour = colourIn;"
        "gl_Position = vec4(position2dIn.x, position2dIn.y, 0.999f, 1.0f);"
    "}";

    //The code for the particle shader program's fragment shader. It is written in GLSL.
    //This will simply apply the colour it is passed to the particle.
    const char* const FRAGMENT_CODE =
    "#version 130\n"
    ""
    "in vec3 colour;"
    "out vec4 particleColour;"
    ""
    "void main() {"
        "particleColour = vec4(colour.r, colour.g, colour.b, 1.0f);"
    "}";

    //The parameters are used for the explosion distribution (to generate the speeds of the particles
    //when something explodes). The speeds are generated as an extreme value distribution with the alpha
    //and beta values given below. Any speeds which are less than the min speed before will be discarded
    //and a new speed will be generated instead. This is to prevent very slow moving explosion particles
    //from being generated.
    namespace EXPLOSION_DISTRIBUTION {
            const float ALPHA = 0.015f;
            const float BETA = -0.002f;
            const float MIN_SPEED = 0.005;
    }
    //an estimate of the speed that most particles would move at
    const float AVERAGE_SPEED = EXPLOSION_DISTRIBUTION::ALPHA;
}
