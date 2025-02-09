#include "CshaderProgram.h"

CshaderProgram::CshaderProgram(): id(0) {
    //empty
}

void CshaderProgram::init() {
    id = glCreateProgram();
}

bool CshaderProgram::set_code(const char vertexCode[], const char fragmentCode[]) {
    Cshader vertexShader(GL_VERTEX_SHADER);
    Cshader fragmentShader(GL_FRAGMENT_SHADER);

    if (vertexShader.set_code(vertexCode) == false) {
        return false;
    }
    if (fragmentShader.set_code(fragmentCode) == false) {
        return false;
    }

    glAttachShader(id, vertexShader.get_id());
    glAttachShader(id, fragmentShader.get_id());
    glLinkProgram(id);
    //glDetachShader(id, vertexShader.get_id());
    //glDetachShader(id, fragmentShader.get_id());

    GLint status = GL_FALSE;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        fprintf(stderr, "Could not create shader program with id: %d.\n", id);
        info_log_to_stderr();
        return false;
    }
    fprintf(stdout, "Created shader program with id: %d.\n", id);
    return true;
}

void CshaderProgram::use() {
    glUseProgram(id);
}

void CshaderProgram::info_log_to_stderr() {
    int lengthWithNull = 0;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &lengthWithNull);
    char* log = new char[lengthWithNull];
    glGetProgramInfoLog(id, lengthWithNull, NULL, log);
    if (lengthWithNull > 1) {
        fprintf(stderr, "Log: %s.\n", log);
    }
    delete[] log;
}

GLint CshaderProgram::get_AttribLocation(const char name[]) {
    GLint location = glGetAttribLocation(id, name);
    if (location == -1) {
        fprintf(stderr, "Could not get location of %s.\n", name);
    }
    return location;
}

GLint CshaderProgram::get_UniformLocation(const char name[]) {
    GLint location = glGetUniformLocation(id, name);
    if (location == -1) {
        fprintf(stderr, "Could not get location of %s.\n", name);
    }
    return location;
}

GLuint CshaderProgram::get_id() {
    return id;
}

CshaderProgram::~CshaderProgram() {
    fprintf(stdout, "Freeing shader program with id: %d.\n", id);
    glDeleteProgram(id);
}
