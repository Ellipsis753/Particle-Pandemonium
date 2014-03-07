#include "Copengl.h"

Copengl::Copengl(): vanillaProgram(NULL), currentTextureLocation(0) {
    //empty
}

bool Copengl::init(Cvao &vanilla, CshaderProgram &vanillaProgram) {
    GLenum errorCode = glewInit();
    if (errorCode != GLEW_OK) {
        fprintf(stderr, "Could not start glew: %s.\n", glewGetErrorString(errorCode));
        return false;
    }

    if (!GLEW_VERSION_3_0) {
        fprintf(stderr, "OpenGL version 3.0 or newer is required.\n");
        return false;
    }

    //Although this should never happen as they have opengl 3.0 or newer it does seem to happen sometimes.
    //I think it may be a driver bug. It's very, very strange.
    if (glBindBufferBase == NULL) {
        fprintf(stderr, "OpenGL glBindBufferBase cannot be used. Try updating your graphics card driver.\n");
        return false;
    }

    //this extension is required if they do not have 3.0 or newer.
    //if (!GLEW_EXT_transform_feedback) {
    //    fprintf(stderr, "Sorry, your graphics card does not support the required EXT_transform_feedback extension.\n");
    //    return false;
    //}

    glClearColor(OPENGL::CLEAR_COLOUR_RED, OPENGL::CLEAR_COLOUR_GREEN, OPENGL::CLEAR_COLOUR_BLUE, OPENGL::CLEAR_COLOUR_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //glPointSize(3.0f);

    if (init_vanilla(vanilla, vanillaProgram) == false) {
        return false;
    }

    return check_for_errors();
}

bool Copengl::init_vanilla(Cvao &vanilla, CshaderProgram &vanillaProgram) {
    vanillaProgram.init();
    if (vanillaProgram.set_code(VANILLA::VERTEX_CODE, VANILLA::FRAGMENT_CODE) == false) {
        return false;
    }

    GLint positionInLocation = vanillaProgram.get_AttribLocation("positionIn");
    if (positionInLocation == -1) {
        return false;
    }
    GLint texturePositionInLocation = vanillaProgram.get_AttribLocation("texturePositionIn");
    if (texturePositionInLocation == -1) {
        return false;
    }

    currentTextureLocation = vanillaProgram.get_UniformLocation("currentTexture");
    if (currentTextureLocation == -1) {
        return false;
    }
    vanillaProgram.use();

    vanilla.create(VANILLA::MAX_POINTS*sizeof(OPENGL::vanillaPoint));
    vanilla.bind();
    vanilla.bind_vbo();
    glEnableVertexAttribArray(positionInLocation);
    glEnableVertexAttribArray(texturePositionInLocation);
    glVertexAttribPointer(positionInLocation, 3, GL_FLOAT, GL_FALSE, sizeof(OPENGL::vanillaPoint), (GLvoid*)offsetof(OPENGL::vanillaPoint, pos));
    glVertexAttribPointer(texturePositionInLocation, 2, GL_FLOAT, GL_FALSE, sizeof(OPENGL::vanillaPoint), (GLvoid*)offsetof(OPENGL::vanillaPoint, tex));
    return true;
}

bool Copengl::check_for_errors() {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "An opengl error has occurred. Error #%d.\n", error);
        return false;
    }
    return true;
}

float Copengl::convert_to_opengl_x(int x) {
    return OPENGL::LEFT_SIDE_X + convert_pixel_width(x);
}

float Copengl::convert_to_opengl_y(int y) {
    return OPENGL::TOP_Y - convert_pixel_height(y);
}

float Copengl::convert_to_opengl_from_window_x(int x) {
    return OPENGL::LEFT_SIDE_X + (float(x)/SDL::WINDOW_WIDTH)*OPENGL::SCREEN_WIDTH;
}

float Copengl::convert_to_opengl_from_window_y(int y) {
    return OPENGL::TOP_Y - (float(y)/SDL::WINDOW_HEIGHT)*OPENGL::SCREEN_HEIGHT;
}

void Copengl::set_shader_texture(GLint texture) {
    glUniform1i(currentTextureLocation, texture);
}
