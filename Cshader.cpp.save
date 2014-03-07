#include "Cshader.h"

Cshader::Cshader(GLenum type): type(type), id(glCreateShader(type)) {
    //empty
}

bool Cshader::set_code(const char inputCode[]) {
    const GLchar* code[1] = {inputCode};
    glShaderSource(id, 1, code, NULL);
    glCompileShader(id);

    GLint compiled = GL_FALSE;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);

    if (compiled != GL_TRUE) {
        fprintf(stderr, "Could not compile shader with id: %d.\n", id);
        info_log_to_stderr();
        return false;
    }
    return true;
}

void Cshader::info_log_to_stderr() {
    int lengthWithNull = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lengthWithNull);
    char* log = new char[lengthWithNull];
    glGetShaderInfoLog(id, lengthWithNull, NULL, log);
    fprintf(stderr, "Log:\n%s.\n", log);
    delete[] log;
}

GLuint Cshader::get_id() {
    return id;
}

GLenum Cshader::get_type() {
    return type;
}

Cshader::~Cshader() {
    glDeleteShader(id);
}
