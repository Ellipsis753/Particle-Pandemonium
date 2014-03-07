#include "Ctutorial.h"

STATE::STATE Ctutorial::run(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl) {
    if (init(vanilla, vanillaProgram, loader, opengl) == false) {
        return STATE::ENCOUNTERED_ERROR;
    }

    Cbutton back(TUTORIAL::BACK::X, TUTORIAL::BACK::Y, TUTORIAL::BACK::W, TUTORIAL::BACK::H);

    while (true) {
        SDL_Event event;
        SDL_WaitEvent(&event);

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            float x = opengl.convert_to_opengl_from_window_x(event.button.x);
            float y = opengl.convert_to_opengl_from_window_y(event.button.y);
            if (back.isClicked(x, y) == true) {
                return STATE::MENU;
            }
        } else if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
            return STATE::MENU;
        }
    }
}

bool Ctutorial::init(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    vanillaProgram.use();
    vanilla.bind_vbo();
    OPENGL::vanillaPoint* freeSpace = (OPENGL::vanillaPoint*)vanilla.map_vbo(GL_WRITE_ONLY);
    if (freeSpace == NULL) {
        fprintf(stderr, "Could not map Vanilla.\n");
        return false;
    }

    freeSpace = opengl.add_rectangle(OPENGL::LEFT_SIDE_X, OPENGL::TOP_Y, 0.0f, OPENGL::SCREEN_WIDTH, OPENGL::SCREEN_HEIGHT,
                                     IMAGES::TUTORIAL::TEX_X, IMAGES::TUTORIAL::TEX_Y, IMAGES::TUTORIAL::TEX_W, IMAGES::TUTORIAL::TEX_H, freeSpace);
    vanilla.unmap_vbo();

    opengl.set_shader_texture(IMAGES::STATIC::SHADER_TEXTURE);

    vanilla.bind();
    glDrawArrays(GL_TRIANGLES, 0, 2*3);
    SDL_GL_SwapBuffers();
    return true;
}

