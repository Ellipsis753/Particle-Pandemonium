#include "Cscoreboard.h"

STATE::STATE Cscoreboard::run(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl, Cscore &score) {
    glClearColor(SCOREBOARD::CLEAR_COLOUR_RED, SCOREBOARD::CLEAR_COLOUR_GREEN, SCOREBOARD::CLEAR_COLOUR_BLUE, SCOREBOARD::CLEAR_COLOUR_ALPHA);
    //get the current scoreboard and load it into scoreboard
    //make sure to leave space for the null terminator
    char scoreboardNames[SCOREBOARD::NUM_ENTRYS][SCOREBOARD::NAME_LENGTH+1];
    unsigned long scoreboardScores[SCOREBOARD::NUM_ENTRYS];
    load_scoreboard(scoreboardNames, scoreboardScores);

    //To start with we would insert after end of array (not insert)
    int insertPosition = SCOREBOARD::NUM_ENTRYS;
    //Work out if they are in the high scores
    //We must start at the end of the array (so as arrays start at 0 this is -1).
    for (int iii=(SCOREBOARD::NUM_ENTRYS-1); iii >= 0; iii--) {
        if (score.get_score() >= scoreboardScores[iii]) {
            //They are better than this score so should at least insert here
            insertPosition = iii;
        }
    }
    //now insertPosition has the place that they should be added.
    //Last entry is not shifted but instead dropped.
    if (insertPosition < SCOREBOARD::NUM_ENTRYS) {
        //They should be added. Ask for name.
        //Make a buffer for the player's name and add 1 for the null terminator.
        char name[SCOREBOARD::NAME_LENGTH+1] = "";
        //Show the text first before doing anything else
        draw_got_high_score(name, vanilla, vanillaProgram, loader, opengl);
        //They have not typed yet
        int lettersUsed = 0;
        //We need the unicode values of letters pressed so must turn it on
        SDL_EnableUNICODE(SDL_ENABLE);
        bool loop = true;
        while (loop == true) {
            SDL_Event event;
            SDL_WaitEvent(&event);
            if (event.type == SDL_KEYDOWN) {
                if (lettersUsed < SCOREBOARD::NAME_LENGTH) {
                    if (event.key.keysym.unicode <= 'Z' && event.key.keysym.unicode >= 'A') {
                        //add to the name string
                        name[lettersUsed] = event.key.keysym.unicode;
                        lettersUsed++;
                        name[lettersUsed] = '\0';
                        Csound::play_effect(loader.get_explosion_effect());
                        //update display
                        draw_got_high_score(name, vanilla, vanillaProgram, loader, opengl);
                    } else if (event.key.keysym.unicode <= 'z' && event.key.keysym.unicode >= 'a') {
                        //They entered a lower case letter so we must change it to uppercase before adding it
                        char lowerToUpperDifference = 'a'-'A';
                        char letter = event.key.keysym.unicode-lowerToUpperDifference;
                        name[lettersUsed] = letter;
                        lettersUsed++;
                        name[lettersUsed] = '\0';
                        Csound::play_effect(loader.get_explosion_effect());
                        //update display
                        draw_got_high_score(name, vanilla, vanillaProgram, loader, opengl);
                    }
                }
                if (event.key.keysym.sym == SDLK_BACKSPACE && lettersUsed > 0) {
                    //shrink name one letter
                    name[lettersUsed-1] = '\0';
                    lettersUsed--;
                    Csound::play_effect(loader.get_explosion_effect());
                    //update display
                    draw_got_high_score(name, vanilla, vanillaProgram, loader, opengl);
                } else if (event.key.keysym.sym == SDLK_RETURN && lettersUsed > 0) {
                    loop = false;
                }
            }

        }
        //turn unicode back off as we won't need it again
        SDL_EnableUNICODE(SDL_DISABLE);

        Csound::play_effect(loader.get_bomb_effect());

        //copy everyone after them down one space
        for (int iii = (SCOREBOARD::NUM_ENTRYS-1); iii >= insertPosition; iii--) {
            strcpy(scoreboardNames[iii], scoreboardNames[iii-1]);
            scoreboardScores[iii] = scoreboardScores[iii-1];
        }
        //Now we can copy them where they belong
        strcpy(scoreboardNames[insertPosition], name);
        scoreboardScores[insertPosition] = score.get_score();

        if (save_scoreboard(scoreboardNames, scoreboardScores) == false) {
            return STATE::ENCOUNTERED_ERROR;
        }
    }

    //Show the scoreboard
    if (draw_scoreboard(scoreboardNames, scoreboardScores, vanilla, vanillaProgram, loader, opengl) == false) {
        return STATE::ENCOUNTERED_ERROR;
    }

    while (true) {
        //Wait for the user to press a key to continue
        SDL_Event event;
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) {
            return STATE::END_GAME;
        } else if (event.type == SDL_KEYDOWN) {
            return STATE::MENU;
        }
    }
}

bool Cscoreboard::draw_got_high_score(char name[SCOREBOARD::NAME_LENGTH+1], Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //So that we have the correct texture to actually be able to render text
    opengl.set_shader_texture(IMAGES::GAMEPLAY::SHADER_TEXTURE);

    vanilla.bind();
    vanilla.bind_vbo();
    OPENGL::vanillaPoint* startOfVanilla = (OPENGL::vanillaPoint*)vanilla.map_vbo(GL_WRITE_ONLY);
    OPENGL::vanillaPoint* freeSpace = startOfVanilla;
    if (freeSpace == NULL) {
        fprintf(stderr, "Could not map Vanilla.\n");
        return false;
    }

    Ctext text;
    freeSpace = text.draw_string(SCOREBOARD::GOT_HIGH_SCORE_MESSAGE, SCOREBOARD::GOT_HIGH_SCORE_MESSAGE_X, SCOREBOARD::GOT_HIGH_SCORE_MESSAGE_Y, opengl, freeSpace);
    freeSpace = text.draw_string(name, SCOREBOARD::ENTERED_NAME_X, SCOREBOARD::ENTERED_NAME_Y, opengl, freeSpace);
    vanilla.unmap_vbo();

    long verticesToRender = freeSpace-startOfVanilla;
    glDrawArrays(GL_TRIANGLES, 0, verticesToRender);
    //update screen
    SDL_GL_SwapBuffers();
    return true;
}

bool Cscoreboard::draw_scoreboard(char scoreboardNames[SCOREBOARD::NUM_ENTRYS][SCOREBOARD::NAME_LENGTH+1], unsigned long scoreboardScores[SCOREBOARD::NUM_ENTRYS], Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //First draw the background
    vanillaProgram.use();
    vanilla.bind();
    vanilla.bind_vbo();
    OPENGL::vanillaPoint* freeSpace = (OPENGL::vanillaPoint*)vanilla.map_vbo(GL_WRITE_ONLY);
    if (freeSpace == NULL) {
        fprintf(stderr, "Could not map Vanilla.\n");
        return false;
    }

    freeSpace = opengl.add_rectangle(OPENGL::LEFT_SIDE_X, OPENGL::TOP_Y, SCOREBOARD::BACKGROUND_DEPTH, OPENGL::SCREEN_WIDTH, OPENGL::SCREEN_HEIGHT,
                                     IMAGES::SCOREBOARD::TEX_X, IMAGES::SCOREBOARD::TEX_Y, IMAGES::SCOREBOARD::TEX_W, IMAGES::SCOREBOARD::TEX_H, freeSpace);
    vanilla.unmap_vbo();

    opengl.set_shader_texture(IMAGES::STATIC::SHADER_TEXTURE);

    glDrawArrays(GL_TRIANGLES, 0, 2*3);

    //Draw the text over it (to be able to draw text we must change to the texture with the font).
    opengl.set_shader_texture(IMAGES::GAMEPLAY::SHADER_TEXTURE);

    vanilla.bind();
    vanilla.bind_vbo();
    OPENGL::vanillaPoint* startOfVanilla = (OPENGL::vanillaPoint*)vanilla.map_vbo(GL_WRITE_ONLY);
    freeSpace = startOfVanilla;
    if (freeSpace == NULL) {
        fprintf(stderr, "Could not map Vanilla.\n");
        return false;
    }

    Ctext text;
    for (int iii=0; iii<SCOREBOARD::NUM_ENTRYS; iii++) {
        char* name = scoreboardNames[iii];
        unsigned long score = scoreboardScores[iii];
        freeSpace = text.draw_string(name, SCOREBOARD::NAMES_X, SCOREBOARD::NAMES_Y-iii*SCOREBOARD::SPACING, opengl, freeSpace);
        freeSpace = text.draw_number(score, SCOREBOARD::SCORES_X, SCOREBOARD::SCORES_Y-iii*SCOREBOARD::SPACING, opengl, freeSpace);
    }
    vanilla.unmap_vbo();

    long verticesToRender = freeSpace-startOfVanilla;
    glDrawArrays(GL_TRIANGLES, 0, verticesToRender);

    SDL_GL_SwapBuffers();
    return true;
}

void Cscoreboard::load_scoreboard(char scoreboardNames[SCOREBOARD::NUM_ENTRYS][SCOREBOARD::NAME_LENGTH+1], unsigned long scoreboardScores[SCOREBOARD::NUM_ENTRYS]) {
    std::ifstream file(SCOREBOARD::SCORES_PATH);
    if (file.is_open() == false) {
        fprintf(stderr, "Could not find scores. Making blank scoreboard.\n");
        //Fill with default entries
        for (int iii=0; iii<SCOREBOARD::NUM_ENTRYS; iii++) {
            strcpy(scoreboardNames[iii], SCOREBOARD::DEFAULT_NAME);
            scoreboardScores[iii] = SCOREBOARD::DEFAULT_SCORE;
        }
    } else {
        //file opened OK. Read it.
        for (int iii=0; iii<SCOREBOARD::NUM_ENTRYS; iii++) {
            file.getline(scoreboardNames[iii], SCOREBOARD::NAME_LENGTH+1);
            char buffer[SCOREBOARD::NAME_LENGTH+1] = "";
            file.getline(buffer, SCOREBOARD::NAME_LENGTH+1);
            unsigned long score = strtoul(buffer, NULL, 10);
            scoreboardScores[iii] = score;
        }
        //now we finally get their checksum
        char buffer[SCOREBOARD::NAME_LENGTH+1] = "";
        file.getline(buffer, SCOREBOARD::NAME_LENGTH+1);
        int checksum = atoi(buffer);
        file.close();
        if (checksum != make_checksum(scoreboardNames, scoreboardScores)) {
            fprintf(stderr, "Checksum failed. Making blank scoreboard.\n");
            //Fill with default entries
            for (int iii=0; iii<SCOREBOARD::NUM_ENTRYS; iii++) {
                strcpy(scoreboardNames[iii], SCOREBOARD::DEFAULT_NAME);
                scoreboardScores[iii] = SCOREBOARD::DEFAULT_SCORE;
            }
        } else {
            fprintf(stdout, "Loaded scoreboard.\n");
        }
    }
}

bool Cscoreboard::save_scoreboard(char scoreboardNames[SCOREBOARD::NUM_ENTRYS][SCOREBOARD::NAME_LENGTH+1], unsigned long scoreboardScores[SCOREBOARD::NUM_ENTRYS]) {
    std::ofstream file(SCOREBOARD::SCORES_PATH);
    if (file.is_open() == false) {
        fprintf(stderr, "Could not create \"%s\" file for saving the high scores.\n", SCOREBOARD::SCORES_PATH);
        return false;
    }
    for (int iii=0; iii<SCOREBOARD::NUM_ENTRYS; iii++) {
        file << scoreboardNames[iii] << std::endl;
        file << scoreboardScores[iii] << std::endl;
    }
    //Add a checksum to the end of the file
    file << make_checksum(scoreboardNames, scoreboardScores) << std::endl;
    file.close();
    return true;
}

int Cscoreboard::make_checksum(char scoreboardNames[SCOREBOARD::NUM_ENTRYS][SCOREBOARD::NAME_LENGTH+1], unsigned long scoreboardScores[SCOREBOARD::NUM_ENTRYS]) {
    int total = 0;
    //A fairly random checksum generated using the scores.
    //This is to make it a little bit harder to tamper with the scores.
    for (int iii=0; iii<SCOREBOARD::NUM_ENTRYS; iii++) {
        total += scoreboardScores[iii] % (iii+7);
        total += scoreboardScores[iii] % 3;
        total += scoreboardNames[iii][0];
        total %= 232;
    }
    return total;
}
