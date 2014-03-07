#include "Cload.h"

STATE::STATE Cload::run(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl) {
    //We don't want to listen to mouse clicks during the loading or they will be processed after it
    //and this would be confusing (it could be as if they clicked something they didn't).
    SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);

    Csound::play_music(loader.get_menu_music());

    loader.load_loading_image();
    if (draw_loading_screen(vanilla, vanillaProgram, loader, opengl) == false) {
        return STATE::ENCOUNTERED_ERROR;
    }

    if (loader.load() == false) {
        return STATE::ENCOUNTERED_ERROR;
    };
    SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
    return STATE::MENU;
}

bool Cload::draw_loading_screen(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    vanilla.bind_vbo();

    OPENGL::vanillaPoint* freeSpace = (OPENGL::vanillaPoint*)vanilla.map_vbo(GL_WRITE_ONLY);
    if (freeSpace == NULL) {
        fprintf(stderr, "Could not map Vanilla.\n");
        return false;
    }

    freeSpace = opengl.add_rectangle(OPENGL::CENTRE_X-(opengl.convert_pixel_width(IMAGES::LOADING::WIDTH)/2),
                                     OPENGL::CENTRE_Y+(opengl.convert_pixel_height(IMAGES::LOADING::HEIGHT)/2), 0.0f,
                                     opengl.convert_pixel_width(IMAGES::LOADING::WIDTH), opengl.convert_pixel_height(IMAGES::LOADING::HEIGHT),
                                     IMAGES::LOADING::TEX_X, IMAGES::LOADING::TEX_Y, IMAGES::LOADING::TEX_W, IMAGES::LOADING::TEX_H, freeSpace);
    vanilla.unmap_vbo();

    opengl.set_shader_texture(IMAGES::LOADING::SHADER_TEXTURE);

    glDrawArrays(GL_TRIANGLES, 0, 2*3);
    SDL_GL_SwapBuffers();
    return true;
}
