#include "Cgameplay.h"

Cgameplay::Cgameplay(): particleController(), starController(), enemyController(), bullets(), playerBullets(), enemies(), player(PLAYER::SPAWN_X, PLAYER::SPAWN_Y), bombs(),
                        startGameTime(SDL_GetTicks()), frameCount(0), drawsInLastSecond(0), endGame(false), quit(false), menu(false), win(false) {
    //empty
}

STATE::STATE Cgameplay::run(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl, Cscore &score) {
    init(loader, opengl, score);
    while (endGame == false) {
        if (frame(vanilla, vanillaProgram, loader, opengl, score) == false) {
            return STATE::ENCOUNTERED_ERROR;
        }
    }

    if (quit == true) {
        return STATE::END_GAME;
    } else if (menu == true) {
        return STATE::MENU;
    } if (win == true) {
        return STATE::WIN;
    }
    //they lost. Game over.
    return STATE::LOSE;
}

void Cgameplay::init(Cloader &loader, Copengl &opengl, Cscore &score) {
    Csound::play_music(loader.get_in_game_music());
    opengl.set_shader_texture(IMAGES::GAMEPLAY::SHADER_TEXTURE);
    glClearColor(GAMEPLAY::CLEAR_COLOUR_RED, GAMEPLAY::CLEAR_COLOUR_GREEN, GAMEPLAY::CLEAR_COLOUR_BLUE, GAMEPLAY::CLEAR_COLOUR_ALPHA);
    starController.cover_screen(loader.get_random_engine(), particleController);
    //Reset your score to 0 for the start of the game
    score.set_score(0);
    //Start the game on level 1
    enemyController.set_level(1);
}

bool Cgameplay::frame(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl, Cscore &score) {
    Uint32 startFrameTime = SDL_GetTicks();

    handleEvents();

    starController.step(loader.get_random_engine(), particleController);

    if (enemyController.step(enemies, bullets) == true) {
        //Player has won
        win = true;
        endGame = true;
        return true;
    }

    for (std::vector<Cbullet*>::iterator iter = bullets.begin(); iter != bullets.end();) {
        if ((*iter)->step() == true) {
            delete (*iter);
            iter = bullets.erase(iter);
        } else {
            iter++;
        }
    }

    for (std::vector<CplayerBullet*>::iterator iter = playerBullets.begin(); iter != playerBullets.end();) {
        if ((*iter)->step() == true) {
            delete (*iter);
            iter = playerBullets.erase(iter);
        } else {
            iter++;
        }
    }

    for (std::vector<Cenemy*>::iterator iter = enemies.begin(); iter != enemies.end();) {
        ENEMY::STEP returnValue = (*iter)->step(loader, playerBullets, bullets, particleController, score, player.get_x(), player.get_y());
        if (returnValue == ENEMY::DELETE_ME) {
            //delete them
            delete (*iter);
            iter = enemies.erase(iter);
        } else if (returnValue == ENEMY::ERROR_ENCOUNTERED) {
            //They have returned an error so we should pass it back
            return false;
        } else {
            iter++;
        }
    }

    Uint8* keyboardState = SDL_GetKeyState(NULL);
    PLAYER::STEP returnValue = player.step(loader, keyboardState, bullets, playerBullets, bombs, enemies, particleController);
    if (returnValue == PLAYER::DELETE_ME) {
        //They lost all lives. Game over
        endGame = true;
        return true;
    } else if (returnValue == PLAYER::ERROR_ENCOUNTERED) {
        //They have returned an error so we should pass it back
        return false;
    }

    for (std::vector<Cbomb*>::iterator iter = bombs.begin(); iter != bombs.end();) {
        BOMB::STEP returnValue = (*iter)->step(score, loader, particleController, enemies, bullets);
        if (returnValue != BOMB::OK) {
            //kill it asks to be deleted then delete it
            if (returnValue == BOMB::DELETE_ME) {
                delete (*iter);
                iter = bombs.erase(iter);
            } else {
                //They have returned an error so we should pass it back
                return false;
            }
        } else {
            iter++;
        }
    }

    //draw
    Uint32 gameTime = SDL_GetTicks() - startGameTime;
    //Work out the frame we should be on ideally.
    unsigned int predictedFrame = (gameTime/1000.0f)*SDL::FPS;
    //Add one for this frame
    predictedFrame++;
    if (frameCount < predictedFrame) {
        //We are behind so step without drawing to catch up
        particleController.step();
        vanillaProgram.use();
    } else {
        drawsInLastSecond++;
        if (draw(vanilla, vanillaProgram, loader, opengl, score) == false) {
            return false;
        }
    }

    frameCount++;
    //If we're more than a second behind we'lll have to just lag.
    if (frameCount+SDL::FPS < predictedFrame) {
        frameCount = predictedFrame;
    } else if (frameCount > predictedFrame) {
        int delay = (frameCount-predictedFrame)*(1000/SDL::FPS) - (SDL_GetTicks()-startFrameTime);
        //Normally 10 in the smallest delay
        if (delay >= 10) {
            SDL_Delay(delay);
        }
    }

    if (frameCount % (SDL::FPS) == 0) {
        fprintf(stdout, "FPS: %d/%d.\n", drawsInLastSecond, SDL::FPS);
        drawsInLastSecond = 0;
    }
    return true;
}

void Cgameplay::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    endGame = true;
                    menu = true;
                }
            }
            break;

            case SDL_QUIT: {
                endGame = true;
                quit = true;
            }
            break;

            default: {
                //do nothing
            }
            break;
        }
    }
}

bool Cgameplay::draw(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl, Cscore &score) {
    vanilla.bind();
    vanilla.bind_vbo();
    OPENGL::vanillaPoint* startOfVanilla = (OPENGL::vanillaPoint*)vanilla.map_vbo(GL_WRITE_ONLY);
    OPENGL::vanillaPoint* freeSpace = startOfVanilla;

    if (freeSpace == NULL) {
        fprintf(stderr, "Could not map Vanilla.\n");
        return false;
    }

    float small = (BULLET::DEPTH_MAX-BULLET::DEPTH_MIN)/1000000.0f;
    int iii = 0;
    for (std::vector<Cbullet*>::iterator iter = bullets.begin(); iter != bullets.end(); iter++) {
        freeSpace = (*iter)->draw(opengl, freeSpace, BULLET::DEPTH_MIN+iii*small);
        iii++;
    }
    for (std::vector<CplayerBullet*>::iterator iter = playerBullets.begin(); iter != playerBullets.end(); iter++) {
        freeSpace = (*iter)->draw(opengl, freeSpace);
    }
    for (std::vector<Cenemy*>::iterator iter = enemies.begin(); iter != enemies.end(); iter++) {
        freeSpace = (*iter)->draw(opengl, freeSpace);
    }
    for (std::vector<Cbomb*>::iterator iter = bombs.begin(); iter != bombs.end(); iter++) {
        freeSpace = (*iter)->draw(opengl, freeSpace);
    }

    freeSpace = score.draw(opengl, freeSpace);
    freeSpace = Clives::draw(player.get_lives(), opengl, freeSpace);
    freeSpace = Cbombs::draw(player.get_bomb_count(), opengl, freeSpace);

    //We draw the player last so we can easily tell if they don't turn up.
    //If the player doesn't show we know that we're not rendering enough triangles.
    freeSpace = player.draw(opengl, freeSpace);

    vanilla.unmap_vbo();

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    long verticesToRender = freeSpace-startOfVanilla;
    glDrawArrays(GL_TRIANGLES, 0, verticesToRender);

    particleController.draw_and_step();
    vanillaProgram.use();
    SDL_GL_SwapBuffers();
    return true;
}

Cgameplay::~Cgameplay() {
    fprintf(stdout, "Clearing up gameplay related resources.\n");
    for (std::vector<Cbullet*>::iterator iter = bullets.begin(); iter != bullets.end(); iter++) {
        delete (*iter);
    }
    for (std::vector<CplayerBullet*>::iterator iter = playerBullets.begin(); iter != playerBullets.end(); iter++) {
        delete (*iter);
    }
    for (std::vector<Cenemy*>::iterator iter = enemies.begin(); iter != enemies.end(); iter++) {
        delete (*iter);
    }
    for (std::vector<Cbomb*>::iterator iter = bombs.begin(); iter != bombs.end(); iter++) {
        delete (*iter);
    }
}
