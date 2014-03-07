#include "Cmenu.h"

STATE::STATE Cmenu::run(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl) {
    //This flag lets us set if we should restart the menu music next time the menu is entered
    //To start with we don't play menu music as the loading screen will have already started it and
    //we don't want to restart it.
    static bool shouldStartMenuMusic = false;
    if (shouldStartMenuMusic == true) {
        Csound::play_music(loader.get_menu_music());
    }
    //Should always be set to restart by default.
    shouldStartMenuMusic = true;

    if (init(vanilla, vanillaProgram, loader, opengl) == false) {
        return STATE::ENCOUNTERED_ERROR;
    }

    Cbutton startGame(MENU::START_GAME::X, MENU::START_GAME::Y, MENU::START_GAME::W, MENU::START_GAME::H);
    Cbutton tutorial(MENU::TUTORIAL::X, MENU::TUTORIAL::Y, MENU::TUTORIAL::W, MENU::TUTORIAL::H);
    Cbutton quitGame(MENU::QUIT_GAME::X, MENU::QUIT_GAME::Y, MENU::QUIT_GAME::W, MENU::QUIT_GAME::H);

    while (true) {
        SDL_Event event;
        SDL_WaitEvent(&event);

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            float x = opengl.convert_to_opengl_from_window_x(event.button.x);
            float y = opengl.convert_to_opengl_from_window_y(event.button.y);
            if (startGame.isClicked(x, y) == true) {
                return STATE::GAMEPLAY;
            } else if (tutorial.isClicked(x, y) == true) {
                //We're going to the tutorial but will be back soon.
                //The current music should just keep going (not restart when they return to the menu).
                shouldStartMenuMusic = false;
                return STATE::TUTORIAL;
            } else if (quitGame.isClicked(x, y) == true) {
                return STATE::END_GAME;
            }
        } else if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
            return STATE::END_GAME;
        }
    }
}

bool Cmenu::init(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    vanillaProgram.use();
    vanilla.bind_vbo();
    OPENGL::vanillaPoint* freeSpace = (OPENGL::vanillaPoint*)vanilla.map_vbo(GL_WRITE_ONLY);
    if (freeSpace == NULL) {
        fprintf(stderr, "Could not map Vanilla.\n");
        return false;
    }

    freeSpace = opengl.add_rectangle(OPENGL::LEFT_SIDE_X, OPENGL::TOP_Y, 0.0f, OPENGL::SCREEN_WIDTH, OPENGL::SCREEN_HEIGHT,
                                     IMAGES::MENU::TEX_X, IMAGES::MENU::TEX_Y, IMAGES::MENU::TEX_W, IMAGES::MENU::TEX_H, freeSpace);
    vanilla.unmap_vbo();

    opengl.set_shader_texture(IMAGES::STATIC::SHADER_TEXTURE);

    vanilla.bind();
    glDrawArrays(GL_TRIANGLES, 0, 2*3);
    SDL_GL_SwapBuffers();
    return true;
}
