#include "Csdl.h"

bool Csdl::init() {
    if (SDL_Init(SDL::INIT_ARGUMENT) < 0) {
        fprintf(stderr, "Could not start SDL: %s.\n", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8);
    SDL_WM_SetCaption(SDL::WINDOW_TITLE, SDL::WINDOW_ICON_TITLE);

    return true;
}

bool Csdl::create_window(SDL_Surface* icon) {
    if (SDL_SetVideoMode(SDL::WINDOW_WIDTH, SDL::WINDOW_HEIGHT, SDL::WINDOW_BPP, SDL_OPENGL) == NULL) {
        fprintf(stderr, "Could not set video mode: %s.\n", SDL_GetError());
        return false;
    }
    SDL_WM_SetIcon(icon, NULL);
    return true;
}

void Csdl::end() {
    fprintf(stdout, "Stopping sdl.\n");
    SDL_Quit();
}
