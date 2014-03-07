#include "Cvao.h"

Cvao::Cvao(): id(0), vbo() {
    //empty
}

void Cvao::create(GLsizeiptr size) {
    glGenVertexArrays(1, &id);
    bind();
    vbo.create(size);
    fprintf(stdout, "Created VAO with id: %d.\n", id);
    unbind();
}

void Cvao::bind() {
    glBindVertexArray(id);
}

void Cvao::unbind() {
    glBindVertexArray(0);
}

void Cvao::bind_vbo() {
    vbo.bind();
}

void Cvao::unbind_vbo() {
    vbo.unbind();
}

void* Cvao::map_vbo(GLenum type) {
    return vbo.map(type);
}

void Cvao::unmap_vbo() {
    vbo.unmap();
}

GLuint Cvao::get_id() {
    return id;
}

Cvbo* Cvao::get_vbo() {
    return &vbo;
}

Cvao::~Cvao() {
    fprintf(stdout, "Destroying VAO with id: %d.\n", id);
    unbind();
    glDeleteBuffers(1, &id);
}
