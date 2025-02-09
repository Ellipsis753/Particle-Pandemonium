#pragma once

#include <stdio.h>
#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <SDL/SDL_opengl.h>

#include "Cshader.h"

class CshaderProgram {
    public:
    CshaderProgram();
    void init();
    bool set_code(const char vertexCode[], const char fragmentCode[]);
    void use();
    void info_log_to_stderr();
    GLint get_AttribLocation(const char name[]);
    GLint get_UniformLocation(const char name[]);
    ~CshaderProgram();

    GLuint get_id();

    private:
    GLuint id;
};
