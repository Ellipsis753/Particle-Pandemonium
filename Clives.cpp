#include "Clives.h"

OPENGL::vanillaPoint* Clives::draw(int lives, Copengl &opengl, OPENGL::vanillaPoint* freeSpace) {
    Ctext text;
    freeSpace = text.draw_string(LIVES::TEXT, LIVES::X, LIVES::Y, opengl, freeSpace);

    //Limit to prevent player having negative lives when they die for the last time but before game over.
    if (lives < 0) {
        lives = 0;
    }

    return text.draw_number(lives, LIVES::X+LIVES::LENGTH_OF_TEXT*opengl.convert_pixel_width(IMAGES::LETTERS::WIDTH+TEXT::SPACING), LIVES::Y, opengl, freeSpace, LIVES::PLACES);
}
