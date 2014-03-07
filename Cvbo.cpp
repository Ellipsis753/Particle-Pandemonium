#include "Cvbo.h"

Cvbo::Cvbo(): id(0) {
    //empty
}

void Cvbo::create(GLsizeiptr size) {
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STREAM_DRAW);
    fprintf(stdout, "Created VBO with size %lu bytes and id: %d.\n", (long)size, id);
    unbind();
}

void Cvbo::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void Cvbo::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void* Cvbo::map(GLenum type) {
    return glMapBuffer(GL_ARRAY_BUFFER, type);
}

void Cvbo::unmap() {
    glUnmapBuffer(GL_ARRAY_BUFFER);
}

GLuint Cvbo::get_id() {
    return id;
}

Cvbo::~Cvbo() {
    fprintf(stdout, "Destroying VBO with id: %d.\n", id);
    unbind();
    glDeleteBuffers(1, &id);
}
