#pragma once

#include <stdio.h>
#include "SDL.h"
#include <SDL/SDL_image.h>

#include "constSdl.h"

class Csdl {
    public:
    bool init();
    bool create_window(SDL_Surface* icon);
    void end();

    private:
};
