#pragma once

#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <stdio.h>

#include "CshaderProgram.h"
#include "constOpengl.h"
#include "Cvao.h"
#include "CshaderProgram.h"
#include "constVanilla.h"

class Copengl {
    public:
    Copengl();
    bool init(Cvao &vanilla, CshaderProgram &vanillaProgram);
    bool init_vanilla(Cvao &vanilla, CshaderProgram &vanillaProgram);
    bool check_for_errors();
    static float convert_pixel_width(int x);
    static float convert_pixel_height(int y);
    static float convert_to_opengl_x(int x);
    static float convert_to_opengl_y(int y);
    static float convert_to_opengl_from_window_x(int x);
    static float convert_to_opengl_from_window_y(int y);
    OPENGL::vanillaPoint* add_rectangle(float x, float y, float z, float w,
                               float h, float texX, float texY,
                               float texW, float texH, OPENGL::vanillaPoint* freeSpace);

    OPENGL::vanillaPoint* add_triangle(float x1, float y1, float texX1, float texY1,
                              float x2, float y2, float texX2, float texY2,
                              float x3, float y3, float texX3, float texY3, float z, OPENGL::vanillaPoint* freeSpace);

    OPENGL::vanillaPoint* add_point(float x, float y, float z, float texX, float texY, OPENGL::vanillaPoint* freeSpace);

    void set_shader_texture(GLint texture);

    private:
    Copengl(const Copengl&) = delete;
    Copengl& operator = (const Copengl&) = delete;

    CshaderProgram* vanillaProgram;
    GLint currentTextureLocation;
};

inline
float Copengl::convert_pixel_width(int x) {
    return x*OPENGL::PIXEL_WIDTH;
}

inline
float Copengl::convert_pixel_height(int y) {
    return y*OPENGL::PIXEL_HEIGHT;
}

inline
OPENGL::vanillaPoint* Copengl::add_rectangle(float x, float y, float z, float w,
                                    float h, float texX, float texY,
                                    float texW, float texH, OPENGL::vanillaPoint* freeSpace) {
    freeSpace = add_triangle(x, y, texX, texY,
                             x+w, y, texX+texW, texY,
                             x, y-h, texX, texY+texH, z, freeSpace);
    freeSpace = add_triangle(x+w, y, texX+texW, texY,
                             x+w, y-h, texX+texW, texY+texH,
                             x, y-h, texX, texY+texH, z, freeSpace);
    return freeSpace;
}

inline
OPENGL::vanillaPoint* Copengl::add_triangle(float x1, float y1, float texX1, float texY1,
                                   float x2, float y2, float texX2, float texY2,
                                   float x3, float y3, float texX3, float texY3, float z, OPENGL::vanillaPoint* freeSpace) {
    freeSpace = add_point(x1, y1, z, texX1, texY1, freeSpace);
    freeSpace = add_point(x2, y2, z, texX2, texY2, freeSpace);
    freeSpace = add_point(x3, y3, z, texX3, texY3, freeSpace);
    return freeSpace;
}

inline
OPENGL::vanillaPoint* Copengl::add_point(float x, float y, float z, float texX, float texY, OPENGL::vanillaPoint* freeSpace) {
    *freeSpace = {{x, y, z}, {texX, texY}};
    freeSpace++;
    return freeSpace;
}
