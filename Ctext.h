#pragma once

#include "constOpengl.h"
#include "constText.h"
#include "constImages.h"

class Ctext {
    public:
    OPENGL::vanillaPoint* draw_number(unsigned long number, float x, float y, Copengl &opengl, OPENGL::vanillaPoint* freeSpace, int places=TEXT::NUM_DIGITS);
    OPENGL::vanillaPoint* draw_digit(char number, float x, float y, Copengl &opengl, OPENGL::vanillaPoint* freeSpace);
    OPENGL::vanillaPoint* draw_string(const char* const string, float x, float y, Copengl &opengl, OPENGL::vanillaPoint* freeSpace);
    OPENGL::vanillaPoint* draw_letter(char letter, float x, float y, Copengl &opengl, OPENGL::vanillaPoint* freeSpace);

    private:
};
