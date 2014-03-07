#include "Close.h"

STATE::STATE Close::run(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl) {
    //Stop the user being able to mess with stuff on future screens by not logging what they do into the queue.
    SDL_EventState(Uint8(SDL_ALLEVENTS), SDL_IGNORE);
    Csound::play_music(loader.get_lose_music());

    if (init(vanilla, vanillaProgram, loader, opengl) == false) {
        return STATE::ENCOUNTERED_ERROR;
    }

    SDL_Delay(LOSE::DELAY);
    //Re-enable so the user can interact again.
    SDL_EventState(Uint8(SDL_ALLEVENTS), SDL_ENABLE);
    return STATE::SCOREBOARD;
}

bool Close::init(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    vanillaProgram.use();
    vanilla.bind_vbo();
    OPENGL::vanillaPoint* freeSpace = (OPENGL::vanillaPoint*)vanilla.map_vbo(GL_WRITE_ONLY);
    if (freeSpace == NULL) {
        fprintf(stderr, "Could not map Vanilla.\n");
        return false;
    }

    freeSpace = opengl.add_rectangle(OPENGL::LEFT_SIDE_X, OPENGL::TOP_Y, 0.0f, OPENGL::SCREEN_WIDTH, OPENGL::SCREEN_HEIGHT,
                                     IMAGES::LOSE::TEX_X, IMAGES::LOSE::TEX_Y, IMAGES::LOSE::TEX_W, IMAGES::LOSE::TEX_H, freeSpace);
    vanilla.unmap_vbo();

    opengl.set_shader_texture(IMAGES::STATIC::SHADER_TEXTURE);

    vanilla.bind();
    glDrawArrays(GL_TRIANGLES, 0, 2*3);
    SDL_GL_SwapBuffers();
    return true;
}
