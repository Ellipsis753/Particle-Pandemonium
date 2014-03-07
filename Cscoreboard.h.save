#pragma once

#include <stdio.h>
#include <string.h>
#include <fstream>

#include "constScoreboard.h"
#include "Cscore.h"
#include "Cvao.h"
#include "CshaderProgram.h"
#include "Cloader.h"
#include "Copengl.h"
#include "constState.h"
#include "Ctext.h"
#include "Csound.h"

class Cscoreboard {
    public:
    STATE::STATE run(Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl, Cscore &score);

    private:
    bool draw_got_high_score(char name[SCOREBOARD::NAME_LENGTH+1], Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl);
    bool draw_scoreboard(char scoreboardNames[SCOREBOARD::NUM_ENTRYS][SCOREBOARD::NAME_LENGTH+1], unsigned long scoreboardScores[SCOREBOARD::NUM_ENTRYS], Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl);
    void load_scoreboard(char scoreboardNames[SCOREBOARD::NUM_ENTRYS][SCOREBOARD::NAME_LENGTH+1], unsigned long scoreboardScores[SCOREBOARD::NUM_ENTRYS]);
    bool save_scoreboard(char scoreboardNames[SCOREBOARD::NUM_ENTRYS][SCOREBOARD::NAME_LENGTH+1], unsigned long scoreboardScores[SCOREBOARD::NUM_ENTRYS]);
    int make_checksum(char scoreboardNames[SCOREBOARD::NUM_ENTRYS][SCOREBOARD::NAME_LENGTH+1], unsigned long scoreboardScores[SCOREBOARD::NUM_ENTRYS]);
};
