#pragma once

#include <stdio.h>
#include "SDL.h"

#include "constImages.h"

class Cbutton {
    public:
    Cbutton(float x, float y, float w, float h);
    bool isClicked(float mouseX, float mouseY);

    private:
    float x;
    float y;
    float w;
    float h;
};

