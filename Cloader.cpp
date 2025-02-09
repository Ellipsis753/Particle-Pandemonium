#include "Cloader.h"

Cloader::Cloader(): icon(NULL), loadingSdl(NULL), loadingImage(0), menuImage(0), gameplayImage(0), randomSpeeds(NULL), randomEngine(), menuMusic(NULL), inGameMusic(NULL), loseMusic(NULL), winMusic(NULL), laserEffect(NULL), explosionEffect(NULL), bombEffect(NULL), deathEffect(NULL) {
    //empty
}

bool Cloader::preload() {
    icon = load_image(SDL::ICON_DIR);
    if (icon == NULL) {
        return false;
    }

    loadingSdl = load_image(IMAGES::LOADING::FILE);
    if (loadingSdl == NULL) {
        return false;
    }

    //We preload this to start it ASAP
    menuMusic = Csound::load_music(SOUNDS::MENU_PATH);

    return true;
}

void Cloader::load_loading_image() {
    glActiveTexture(IMAGES::LOADING::OPENGL_TEXTURE);
    loadingImage = convert_image(loadingSdl);
    loadingSdl = NULL;
}

bool Cloader::load() {
    glActiveTexture(IMAGES::STATIC::OPENGL_TEXTURE);
    menuImage = load_and_convert_image(IMAGES::STATIC::FILE);
    if (menuImage == 0) {
        return false;
    }

    glActiveTexture(IMAGES::GAMEPLAY::OPENGL_TEXTURE);
    gameplayImage = load_and_convert_image(IMAGES::GAMEPLAY::FILE, true);
    if (gameplayImage == 0) {
        return false;
    }
    //if ((playerImage = load_image(PLAYER_DIR, 1)) == 0) {
    //    return false;
    //}

    inGameMusic = Csound::load_music(SOUNDS::INGAME_PATH);
    loseMusic = Csound::load_music(SOUNDS::LOSE_PATH);
    winMusic = Csound::load_music(SOUNDS::WIN_PATH);
    laserEffect = Csound::load_effect(SOUNDS::LASER_PATH);
    explosionEffect = Csound::load_effect(SOUNDS::EXPLOSION_PATH);
    bombEffect = Csound::load_effect(SOUNDS::BOMB_PATH);
    deathEffect = Csound::load_effect(SOUNDS::DEATH_PATH);

    Uint32 timeSeed = SDL_GetTicks();
    randomEngine.seed(timeSeed);
    srand(timeSeed);
    generate_random_speeds();

    SDL_Delay(1000);
    return true;
}

SDL_Surface* Cloader::load_image(const char path[], bool colourKey) {
    SDL_Surface* image = IMG_Load(path);
    if (image == NULL) {
        fprintf(stderr, "Could not load %s.\n", path);
        return NULL;
    }
    fprintf(stdout, "Loaded %s.\n", path);

    if (colourKey == true) {
        SDL_Surface* rgbaImage = SDL_CreateRGBSurface(SDL_SWSURFACE, image->w, image->h, 32, SDL::R_MASK, SDL::G_MASK, SDL::B_MASK, SDL::A_MASK);



        SDL_BlitSurface(image, NULL, rgbaImage, NULL);
        SDL_FreeSurface(image);
        image = rgbaImage;
        rgbaImage = NULL;

        if (SDL_MUSTLOCK(image)) {
            SDL_LockSurface(image);
        }

        Uint32* pixels = (Uint32*)image->pixels;

        for (int iii = 0; iii < image->w * image->h; iii++) {
            //Make all solid
            pixels[iii] = pixels[iii] | SDL::A_MASK;
        }

        //top left sets the colour key.
        Uint32 colourKey = pixels[0];

        for (int iii = 0; iii < image->w * image->h; iii++) {
            if (pixels[iii] == colourKey) {
                //remove alpha
                pixels[iii] = pixels[iii] & (~SDL::A_MASK);
            }
        }

        if (SDL_MUSTLOCK(image)) {
            SDL_UnlockSurface(image);
        }
    }
    return image;
}

GLuint Cloader::convert_image(SDL_Surface* image) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (image->format->BytesPerPixel == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    }
    SDL_FreeSurface(image);
    return texture;
}

GLuint Cloader::load_and_convert_image(const char path[], bool colourKey) {
    SDL_Surface* sdlImage = load_image(path, colourKey);
    if (sdlImage == NULL) {
        return 0;
    }
    GLuint glImage = convert_image(sdlImage);
    return glImage;
}

void Cloader::generate_random_speeds() {
    //Too big for stack!
    randomSpeeds = new OPENGL::speed2d[PARTICLE_CONTROLLER::NUMBER_OF_RANDOM_SPEEDS];

    std::extreme_value_distribution<float> explosionDistribution(PARTICLE_CONTROLLER::EXPLOSION_DISTRIBUTION::ALPHA, PARTICLE_CONTROLLER::EXPLOSION_DISTRIBUTION::BETA);

    std::uniform_real_distribution<float> angleDistribution(0, 2*3.14159265358979323846264f);
    for (int iii = 0; iii < PARTICLE_CONTROLLER::NUMBER_OF_RANDOM_SPEEDS; iii++) {
        float speed;
        bool loop = true;
        while (loop == true) {
            speed = explosionDistribution(randomEngine);
            if (speed > PARTICLE_CONTROLLER::EXPLOSION_DISTRIBUTION::MIN_SPEED) {
                loop = false;
            }
        }
        float speedX = speed * OPENGL::PIXEL_RATIO_WIDTH_BY_HEIGHT;
        float speedY = speed;

        float angle = angleDistribution(randomEngine);
        float xSpeed = speedX*sin(angle);
        float ySpeed = speedY*cos(angle);

        randomSpeeds[iii] = {xSpeed, ySpeed};
    }
}

void Cloader::unload() {
    fprintf(stdout, "Unloading images.\n");
    //Do not free loadingSdl, it is already converted and freed.
    SDL_FreeSurface(icon);
    glDeleteTextures(1, &loadingImage);
    glDeleteTextures(1, &menuImage);
    glDeleteTextures(1, &gameplayImage);
    fprintf(stdout, "Unloading music and sound effects.\n");
    Csound::unload_music(menuMusic);
    Csound::unload_music(inGameMusic);
    Csound::unload_effect(laserEffect);
    Csound::unload_effect(explosionEffect);
    Csound::unload_effect(bombEffect);
    Csound::unload_effect(deathEffect);

    Csound::quit();
    Csdl sdl;
    sdl.end();
}

SDL_Surface* Cloader::get_icon() {
    return icon;
}

Mix_Music* Cloader::get_menu_music() {
    return menuMusic;
}

Mix_Music* Cloader::get_in_game_music() {
    return inGameMusic;
}

Mix_Music* Cloader::get_lose_music() {
    return loseMusic;
}

Mix_Music* Cloader::get_win_music() {
    return winMusic;
}

Mix_Chunk* Cloader::get_laser_effect() {
    return laserEffect;
}

Mix_Chunk* Cloader::get_explosion_effect() {
    return explosionEffect;
}

Mix_Chunk* Cloader::get_bomb_effect() {
    return bombEffect;
}

Mix_Chunk* Cloader::get_death_effect() {
    return deathEffect;
}

Cloader::~Cloader() {
    unload();
    delete[] randomSpeeds;
}
