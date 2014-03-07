#include "CstateManager.h"

STATE::STATE CstateManager::set_state(STATE::STATE state, Cvao &vanilla, CshaderProgram &vanillaProgram, Cloader &loader, Copengl &opengl, Cscore &score) {
    switch(state) {
        case STATE::START_GAME: {
            fprintf(stdout, "Starting up.\n");
            CstartGame startGame;
            return startGame.run(vanilla, vanillaProgram, loader, opengl);
        }
        break;

        case STATE::LOAD: {
            fprintf(stdout, "Loading.\n");
            Cload load;
            return load.run(vanilla, vanillaProgram, loader, opengl);
        }
        break;

        case STATE::MENU: {
            fprintf(stdout, "Entering menu.\n");
            Cmenu menu;
            return menu.run(vanilla, vanillaProgram, loader, opengl);
        }
        break;

        case STATE::TUTORIAL: {
            fprintf(stdout, "Entering tutorial screen.\n");
            Ctutorial tutorial;
            return tutorial.run(vanilla, vanillaProgram, loader, opengl);
        }
        break;

        case STATE::GAMEPLAY: {
            fprintf(stdout, "Entering main game.\n");
            Cgameplay gameplay;
            return gameplay.run(vanilla, vanillaProgram, loader, opengl, score);
        }
        break;

        case STATE::LOSE: {
            fprintf(stdout, "Game over.\n");
            Close lose;
            return lose.run(vanilla, vanillaProgram, loader, opengl);
        }
        break;

        case STATE::WIN: {
            fprintf(stdout, "You win.\n");
            Cwin win;
            return win.run(vanilla, vanillaProgram, loader, opengl);
        }
        break;

        case STATE::SCOREBOARD: {
            fprintf(stdout, "Showing high scores.\n");
            Cscoreboard scoreboard;
            return scoreboard.run(vanilla, vanillaProgram, loader, opengl, score);
        }
        break;

        default: {
            fprintf(stdout, "Set to invalid state %d.\n", state);
            return STATE::ENCOUNTERED_ERROR;
        }
        break;
    }
}

