#include "Cscore.h"

Cscore::Cscore(): text(), score(0) {
    //empty
}

OPENGL::vanillaPoint* Cscore::draw(Copengl &opengl, OPENGL::vanillaPoint* freeSpace) {
    freeSpace = text.draw_string(SCORE::TEXT, SCORE::X, SCORE::Y, opengl, freeSpace);

    float endOfTextOffset = SCORE::LENGTH_OF_TEXT*(opengl.convert_pixel_width(IMAGES::LETTERS::WIDTH)+opengl.convert_pixel_width(TEXT::SPACING));
    freeSpace = text.draw_number(score, SCORE::X+endOfTextOffset, SCORE::Y, opengl, freeSpace);
    for (int iii = 0; iii < SCORE::EXTRA_ZEROS; iii++) {
        freeSpace = text.draw_digit(0, SCORE::X+endOfTextOffset+(TEXT::NUM_DIGITS+iii)*opengl.convert_pixel_width(IMAGES::DIGITS::WIDTH + TEXT::SPACING + TEXT::DIGIT_PADDING_X + TEXT::DIGIT_EXTRA_SPACING), SCORE::Y, opengl, freeSpace);
    }
    return freeSpace;
}

void Cscore::add(int change) {
    score += change;
}

unsigned long Cscore::get_score() {
    return score;
}

void Cscore::set_score(unsigned long setTo) {
    score = setTo;
}
