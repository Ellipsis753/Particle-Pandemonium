#pragma once

#include "SDL.h"

/*
Constants relating to SDL related functionalities.
*/

namespace SDL {
    //The argument that the SDL system will be initialised with.
    const Uint32 INIT_ARGUMENT = SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER;
    //The dimentions in pixels of the SDL screen surface, used internally for speeds etc.
    const int SCREEN_WIDTH = 600;
    const int SCREEN_HEIGHT = 650;
    //The size of the game window. Changing it will stretch the game without effecting gameplay.
    const int WINDOW_WIDTH = SCREEN_WIDTH;
    const int WINDOW_HEIGHT = SCREEN_HEIGHT;
    //The bits per pixel. If set to 0 then current display bits per pixel will be used used.
    //This will prevent the need for conversions and can provide a speed boost
    const int WINDOW_BPP = 0;
    //The internal frames per second that the game will calculate. Less frames may be rendered/displayed
    //depending on the speed of the computer. Should be kept high to avoid objects "skipping" through each other
    //without detecting a collision and so that the game will appear very smooth on high end computers.
    const int FPS = 60;
    //The title of the game window
    const char* const WINDOW_TITLE = "Particle Pandemonium";
    //The title to be displayed in the menu bar or desktop when the window is minimized.
    const char* const WINDOW_ICON_TITLE = WINDOW_TITLE;
    //The path to the icon image file used.
    const char* const ICON_DIR = "icon.png";

    //The position of the red, green, blue and alpha channels in an sdl pixel with 32 bits per pixel.
    //Used when pixels need to be manipulated by SDL. Must be conditionally to allow this to work on both
    //little endian and big endian computers where the byte order can be reversed.
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        const Uint32 R_MASK = 0xFF000000;
        const Uint32 G_MASK = 0x00FF0000;
        const Uint32 B_MASK = 0x0000FF00;
        const Uint32 A_MASK = 0x000000FF;
    #else
        const Uint32 R_MASK = 0x000000FF;
        const Uint32 G_MASK = 0x0000FF00;
        const Uint32 B_MASK = 0x00FF0000;
        const Uint32 A_MASK = 0xFF000000;
    #endif
}
