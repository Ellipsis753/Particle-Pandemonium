#pragma once

#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <stdio.h>

class Cvbo {
    public:
    Cvbo();
    void create(GLsizeiptr size);
    void bind();
    void unbind();
    void* map(GLenum type);
    void unmap();
    ~Cvbo();

    GLuint get_id();

    private:
    Cvbo(const Cvbo&) = delete;
    Cvbo& operator = (const Cvbo&) = delete;
    GLuint id;
};
