#pragma once

#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <GL/gl.h>

#include "Copengl.h"

/*
The path to load each image as well as it's width and
height given in pixels. Also the OpenGL dimentions of
each image or sprite.
*/

namespace IMAGES {
    namespace LOADING {
        const char* const FILE = "loading.png";
        const int WIDTH = 333;
        const int HEIGHT = 50;
        const GLenum OPENGL_TEXTURE = GL_TEXTURE0;
        const int SHADER_TEXTURE = 0;
        const float TEX_X = 0.0f;
        const float TEX_Y = 0.0f;
        const float TEX_W = 1.0f;
        const float TEX_H = 1.0f;
    }

    namespace STATIC {
        const char* const FILE = "static.png";
        const int WIDTH = 3000;
        const int HEIGHT = 650;
        const GLenum OPENGL_TEXTURE = GL_TEXTURE1;
        const int SHADER_TEXTURE = 1;
    }

    namespace MENU {
        const int WIDTH = 600;
        const int HEIGHT = 650;
        const int TEX_PIXEL_X = 0;
        const int TEX_PIXEL_Y = 0;
        const float TEX_X = float(TEX_PIXEL_X)/STATIC::WIDTH;
        const float TEX_Y = float(TEX_PIXEL_Y)/STATIC::HEIGHT;
        const float TEX_W = float(WIDTH)/STATIC::WIDTH;
        const float TEX_H = float(HEIGHT)/STATIC::HEIGHT;
    }

    namespace TUTORIAL {
        const int WIDTH = 600;
        const int HEIGHT = 650;
        const int TEX_PIXEL_X = MENU::WIDTH;
        const int TEX_PIXEL_Y = 0;
        const float TEX_X = float(TEX_PIXEL_X)/STATIC::WIDTH;
        const float TEX_Y = float(TEX_PIXEL_Y)/STATIC::HEIGHT;
        const float TEX_W = float(WIDTH)/STATIC::WIDTH;
        const float TEX_H = float(HEIGHT)/STATIC::HEIGHT;
    }

    namespace WIN {
        const int WIDTH = 600;
        const int HEIGHT = 650;
        const int TEX_PIXEL_X = TUTORIAL::TEX_PIXEL_X+TUTORIAL::WIDTH;
        const int TEX_PIXEL_Y = 0;
        const float TEX_X = float(TEX_PIXEL_X)/STATIC::WIDTH;
        const float TEX_Y = float(TEX_PIXEL_Y)/STATIC::HEIGHT;
        const float TEX_W = float(WIDTH)/STATIC::WIDTH;
        const float TEX_H = float(HEIGHT)/STATIC::HEIGHT;
    }

    namespace LOSE {
        const int WIDTH = 600;
        const int HEIGHT = 650;
        const int TEX_PIXEL_X = WIN::TEX_PIXEL_X+WIN::WIDTH;
        const int TEX_PIXEL_Y = 0;
        const float TEX_X = float(TEX_PIXEL_X)/STATIC::WIDTH;
        const float TEX_Y = float(TEX_PIXEL_Y)/STATIC::HEIGHT;
        const float TEX_W = float(WIDTH)/STATIC::WIDTH;
        const float TEX_H = float(HEIGHT)/STATIC::HEIGHT;
    }

    namespace SCOREBOARD {
        const int WIDTH = 600;
        const int HEIGHT = 650;
        const int TEX_PIXEL_X = LOSE::TEX_PIXEL_X+LOSE::WIDTH;
        const int TEX_PIXEL_Y = 0;
        const float TEX_X = float(TEX_PIXEL_X)/STATIC::WIDTH;
        const float TEX_Y = float(TEX_PIXEL_Y)/STATIC::HEIGHT;
        const float TEX_W = float(WIDTH)/STATIC::WIDTH;
        const float TEX_H = float(HEIGHT)/STATIC::HEIGHT;
    }


    namespace GAMEPLAY {
        //common to all images in the main game
        const int WIDTH = 351;
        const int HEIGHT = 57;
        const char* const FILE = "gameplay.png";
        const GLenum OPENGL_TEXTURE = GL_TEXTURE2;
        const int SHADER_TEXTURE = 2;
    }

    namespace PLAYER {
        const int WIDTH = 11;
        const int HEIGHT = 12;
        const int TEX_PIXEL_X = 0;
        const int TEX_PIXEL_Y = 0;
        const float TEX_X = float(TEX_PIXEL_X)/GAMEPLAY::WIDTH;
        const float TEX_Y = float(TEX_PIXEL_Y)/GAMEPLAY::HEIGHT;
        const float TEX_W = float(WIDTH)/GAMEPLAY::WIDTH;
        const float TEX_H = float(HEIGHT)/GAMEPLAY::HEIGHT;
    }

    namespace DIGITS {
        const int WIDTH = 8;
        const int HEIGHT = 21;
        const int TEX_PIXEL_X = 0;
        const int TEX_PIXEL_Y = PLAYER::HEIGHT;
        const float TEX_X = float(TEX_PIXEL_X)/GAMEPLAY::WIDTH;
        const float TEX_Y = float(TEX_PIXEL_Y)/GAMEPLAY::HEIGHT;
        const float TEX_W = float(WIDTH)/GAMEPLAY::WIDTH;
        const float TEX_H = float(HEIGHT)/GAMEPLAY::HEIGHT;
    }

    namespace LETTERS {
        const int WIDTH = 13;
        const int HEIGHT = 24;
        const int TEX_PIXEL_X = 0;
        const int TEX_PIXEL_Y = DIGITS::TEX_PIXEL_Y+DIGITS::HEIGHT;
        const float TEX_X = float(TEX_PIXEL_X)/GAMEPLAY::WIDTH;
        const float TEX_Y = float(TEX_PIXEL_Y)/GAMEPLAY::HEIGHT;
        const float TEX_W = float(WIDTH)/GAMEPLAY::WIDTH;
        const float TEX_H = float(HEIGHT)/GAMEPLAY::HEIGHT;
    }

    namespace BOMB {
        const int WIDTH = 32;
        const int HEIGHT = 32;
        const int TEX_PIXEL_X = DIGITS::WIDTH*10;
        const int TEX_PIXEL_Y = 0;
        const float TEX_X = float(TEX_PIXEL_X)/GAMEPLAY::WIDTH;
        const float TEX_Y = float(TEX_PIXEL_Y)/GAMEPLAY::HEIGHT;
        const float TEX_W = float(WIDTH)/GAMEPLAY::WIDTH;
        const float TEX_H = float(HEIGHT)/GAMEPLAY::HEIGHT;
    }

    namespace BULLET {
        const int WIDTH = 32;
        const int HEIGHT = 32;
        const float RADIUS = WIDTH/2;
        const int TEX_PIXEL_X = BOMB::TEX_PIXEL_X+BOMB::WIDTH;
        const int TEX_PIXEL_Y = 0;
        const float TEX_X = float(TEX_PIXEL_X)/GAMEPLAY::WIDTH;
        const float TEX_Y = float(TEX_PIXEL_Y)/GAMEPLAY::HEIGHT;
        const float TEX_W = float(WIDTH)/GAMEPLAY::WIDTH;
        const float TEX_H = float(HEIGHT)/GAMEPLAY::HEIGHT;
    }

    namespace PLAYER_BULLET {
        const int WIDTH = 7;
        const int HEIGHT = 32;
        const int TEX_PIXEL_X = BULLET::TEX_PIXEL_X+BULLET::WIDTH;
        const int TEX_PIXEL_Y = 0;
        const float TEX_X = float(TEX_PIXEL_X)/GAMEPLAY::WIDTH;
        const float TEX_Y = float(TEX_PIXEL_Y)/GAMEPLAY::HEIGHT;
        const float TEX_W = float(WIDTH)/GAMEPLAY::WIDTH;
        const float TEX_H = float(HEIGHT)/GAMEPLAY::HEIGHT;
        const float HITBOX_WIDTH = WIDTH;
        const float HITBOX_HEIGHT = 27;
    }

    namespace ENEMY {
        const int WIDTH = 29;
        const int HEIGHT = 27;
        const int TEX_PIXEL_X = PLAYER_BULLET::TEX_PIXEL_X+PLAYER_BULLET::WIDTH;
        const int TEX_PIXEL_Y = 0;
        const float TEX_X = float(TEX_PIXEL_X)/GAMEPLAY::WIDTH;
        const float TEX_Y = float(TEX_PIXEL_Y)/GAMEPLAY::HEIGHT;
        const float TEX_W = float(WIDTH)/GAMEPLAY::WIDTH;
        const float TEX_H = float(HEIGHT)/GAMEPLAY::HEIGHT;
        //offset 15 by 13
    }
}
