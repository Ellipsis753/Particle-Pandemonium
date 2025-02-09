#pragma once

#include "Copengl.h"
#include "Ctext.h"
#include "constImages.h"
#include "Cscore.h"

/*
The constants relating to the scoreboard class as well as the entry struct.
*/

namespace SCOREBOARD {
    //The clear colour
    const float CLEAR_COLOUR_RED = 0.0f;
    const float CLEAR_COLOUR_GREEN = 0.0f;
    const float CLEAR_COLOUR_BLUE = 0.0f;
    const float CLEAR_COLOUR_ALPHA = 1.0f;

    //The max length of each name. Not including the null terminator
    const int NAME_LENGTH = 10;

    //The message to display when a player gets on the high score board
    const char* const GOT_HIGH_SCORE_MESSAGE = "ENTER NAME:";
    //the length of the above message, not including the null terminator
    const int LENGTH_OF_GOT_HIGH_SCORE_MESSAGE = 11;
    //The position of the message in OpenGL coordinates
    const float GOT_HIGH_SCORE_MESSAGE_X = OPENGL::CENTRE_X-(LENGTH_OF_GOT_HIGH_SCORE_MESSAGE*Copengl::convert_pixel_width(IMAGES::LETTERS::WIDTH+TEXT::SPACING))/2.0f;
    const float GOT_HIGH_SCORE_MESSAGE_Y = OPENGL::CENTRE_Y+Copengl::convert_pixel_height(IMAGES::LETTERS::HEIGHT);
    //The position of your name in OpenGL coordinates
    const float ENTERED_NAME_X = GOT_HIGH_SCORE_MESSAGE_X; //OPENGL::CENTER_X-(NAME_LENGTH*Copengl::convert_pixel_width(IMAGES::LETTERS::WIDTH+TEXT::SPACING))/2.0f;
    const float ENTERED_NAME_Y = GOT_HIGH_SCORE_MESSAGE_Y-Copengl::convert_pixel_height(IMAGES::LETTERS::HEIGHT+5);

    //The number of scores for the score board to have
    const int NUM_ENTRYS = 10;
    //The time to show the scoreboard screen for in ms
    const int DELAY = 12*1000;
    //The depth to draw the background at
    const float BACKGROUND_DEPTH = 0.999f;

    //The position of the top left of the names in OpenGL coordinates
    const float NAMES_X = OPENGL::LEFT_SIDE_X+Copengl::convert_pixel_width(111);
    const float NAMES_Y = OPENGL::TOP_Y-Copengl::convert_pixel_height(132);
    //The position of the top left of the scores in OpenGL coordinates
    const float SCORES_X = OPENGL::RIGHT_SIDE_X-Copengl::convert_pixel_width(107)-(TEXT::NUM_DIGITS+SCORE::EXTRA_ZEROS)*Copengl::convert_pixel_width(IMAGES::DIGITS::WIDTH + TEXT::SPACING + TEXT::DIGIT_PADDING_X + TEXT::DIGIT_EXTRA_SPACING);
    const float SCORES_Y = OPENGL::TOP_Y-Copengl::convert_pixel_height(132);

    //The vertical spacing between lines in the high score table
    //given in OpenGL coordinates
    const float SPACING = Copengl::convert_pixel_height(39); //IMAGES::DIGITS::HEIGHT+TEXT::DIGIT_PADDING_Y+5);

    //A default entry to fill empty spaces in the table with
    const char* const DEFAULT_NAME = "NOBODY";
    const unsigned long DEFAULT_SCORE = 0;

    //The path to the file that the scores are saved in
    const char* const SCORES_PATH = "scores";
}
