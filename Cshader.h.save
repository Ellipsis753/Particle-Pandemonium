#pragma once

#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <stdio.h>

class Cshader {
    public:
    Cshader(GLenum type);
    bool set_code(const char inputCode[]);
    void info_log_to_stderr();
    ~Cshader();

    GLuint get_id();
    GLenum get_type();

    private:
    GLenum type;
    GLuint id;
};
