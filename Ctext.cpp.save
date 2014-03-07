#include "Ctext.h"

OPENGL::vanillaPoint* Ctext::draw_number(unsigned long number, float x, float y, Copengl &opengl, OPENGL::vanillaPoint* freeSpace, int places) {
    for (int iii = places-1; iii >= 0; iii--) {
        freeSpace = draw_digit(number % 10,
                               x + iii*opengl.convert_pixel_width(IMAGES::DIGITS::WIDTH + TEXT::SPACING + TEXT::DIGIT_PADDING_X + TEXT::DIGIT_EXTRA_SPACING),
                               y, opengl, freeSpace);
        number /= 10;
    }
    return freeSpace;
}

OPENGL::vanillaPoint* Ctext::draw_digit(char digit, float x, float y, Copengl &opengl, OPENGL::vanillaPoint* freeSpace) {
    return opengl.add_rectangle(x+opengl.convert_pixel_width(TEXT::DIGIT_PADDING_X), y-opengl.convert_pixel_height(TEXT::DIGIT_PADDING_Y), TEXT::DEPTH,
                            opengl.convert_pixel_width(IMAGES::DIGITS::WIDTH), opengl.convert_pixel_height(IMAGES::DIGITS::HEIGHT),
                            IMAGES::DIGITS::TEX_X+digit*IMAGES::DIGITS::TEX_W, IMAGES::DIGITS::TEX_Y,
                            IMAGES::DIGITS::TEX_W, IMAGES::DIGITS::TEX_H, freeSpace);
}

OPENGL::vanillaPoint* Ctext::draw_string(const char* const string, float x, float y, Copengl &opengl, OPENGL::vanillaPoint* freeSpace) {
    for (int iii = 0; string[iii] != '\0'; iii++) {
        freeSpace = draw_letter(string[iii], x+iii*(opengl.convert_pixel_width(IMAGES::LETTERS::WIDTH)+opengl.convert_pixel_width(TEXT::SPACING)), y, opengl, freeSpace);
    }
    return freeSpace;
}

OPENGL::vanillaPoint* Ctext::draw_letter(char letter, float x, float y, Copengl &opengl, OPENGL::vanillaPoint* freeSpace) {
    if (letter != ' ') {
        if (letter == ':') {
            //Colon is out of the ascii order (in the image) so must be adjusted for.
            letter = TEXT::COLON;
        }
        char offset = letter - 'A';

        return opengl.add_rectangle(x, y, TEXT::DEPTH,
                                opengl.convert_pixel_width(IMAGES::LETTERS::WIDTH), opengl.convert_pixel_height(IMAGES::LETTERS::HEIGHT),
                                IMAGES::LETTERS::TEX_X+offset*IMAGES::LETTERS::TEX_W, IMAGES::LETTERS::TEX_Y,
                                IMAGES::LETTERS::TEX_W, IMAGES::LETTERS::TEX_H, freeSpace);
    }
    return freeSpace;
}
