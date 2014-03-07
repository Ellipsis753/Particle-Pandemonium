#include "Cbombs.h"

OPENGL::vanillaPoint* Cbombs::draw(unsigned int bombs, Copengl &opengl, OPENGL::vanillaPoint* freeSpace) {
    Ctext text;
    freeSpace = text.draw_string(BOMBS::TEXT, BOMBS::X, BOMBS::Y, opengl, freeSpace);

    return text.draw_number(bombs, BOMBS::X+BOMBS::LENGTH_OF_TEXT*opengl.convert_pixel_width(IMAGES::LETTERS::WIDTH+TEXT::SPACING), BOMBS::Y, opengl, freeSpace, BOMBS::PLACES);
}

