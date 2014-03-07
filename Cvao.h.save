#pragma once

#define NO_SDL_GLEXT
#include <GL/glew.h>

#include "Cvbo.h"

class Cvao {
    public:
    Cvao();
    void create(GLsizeiptr size);
    void bind();
    void unbind();
    void bind_vbo();
    void unbind_vbo();
    void* map_vbo(GLenum type);
    void unmap_vbo();
    ~Cvao();

    GLuint get_id();
    Cvbo* get_vbo();

    private:
    Cvao(const Cvao&) = delete;
    Cvao& operator = (const Cvao&) = delete;
    GLuint id;
    Cvbo vbo;
};

