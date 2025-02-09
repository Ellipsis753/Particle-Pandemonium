#include "CenemyController.h"

CenemyController::CenemyController(): level(0), stepCount(0) {
    //empty
}

bool CenemyController::step(std::vector<Cenemy*> &enemies, std::vector<Cbullet*> &bullets) {
    bool endOfLevel = false;
    switch (level) {
        case 1: {
            endOfLevel = step_level_1(enemies, bullets);
        }
        break;

        default: {
            //This should never happen
            fprintf(stderr, "Enemy controller set to non-existent level.\n");
        }
        break;
    }
    stepCount++;
    return endOfLevel;
}

bool CenemyController::step_level_1(std::vector<Cenemy*> &enemies, std::vector<Cbullet*> &bullets) {
    const int SCREEN_WIDTH = SDL::SCREEN_WIDTH;
    const int SCREEN_HEIGHT = SDL::SCREEN_HEIGHT;
    //For random streams start and end points
    static float startX = 0.0f;
    static float endX = 0.0f;
    switch (stepCount) {
        //Short delay with nothing at the start
        //make a bunch in a line from top left.
        case 150:
        case 170:
        case 190:
        case 210:
        case 230:
        case 250: {
            Cenemy* enemy = pixels_create_enemy(100, -30, 100, SCREEN_HEIGHT);
            enemy->move_at_pixels(40, SCREEN_WIDTH, SCREEN_HEIGHT+90);
            for (int iii = 0; iii<4; iii++) {
                enemy->shoot_angle(80, (3.141592f)/4.0f+((2*3.141592f)/(10.0f))*iii);
            }
            enemy->delete_self(600);
            enemies.push_back(enemy);

            //enemy->add_action(0, MOVE_AT, LEFT_SIDE_X+gl.convert_pixel_width(100), BOTTOM_Y-gl.convert_pixel_height(50));
            //enemy->add_action(40, MOVE_AT, RIGHT_SIDE_X, BOTTOM_Y-gl.convert_pixel_height(90));
            //for (int iii = 0; iii<4; iii++) {
            //    enemy->add_action(80, SHOOT_ANGLE, (3.141592f)/4.0f+((2*3.141592f)/(10.0f))*iii);
            //}
            //enemy->add_action(600, DELETE_SELF);
            //enemies.push_back(enemy);
        }
        break;
        /*
        //second stream on right
        case 260:
        case 280:
        case 300:
        case 320:
        case 340:
        case 360: {
            Cenemy* enemy = new Cenemy(RIGHT_SIDE_X-gl.convert_pixel_width(100), TOP_Y+gl.convert_pixel_height(HEIGHT+30));
            enemy->add_action(0, MOVE_AT, RIGHT_SIDE_X-gl.convert_pixel_width(100), BOTTOM_Y-gl.convert_pixel_height(50));
            enemy->add_action(70, MOVE_AT, LEFT_SIDE_X, BOTTOM_Y-gl.convert_pixel_height(90));
            for (int iii = 0; iii<4; iii++) {
                enemy->add_action(80, SHOOT_ANGLE, (-3.141592f)/4.0f+((2*3.141592f)/(-10.0f))*iii);
            }
            enemy->add_action(600, DELETE_SELF);
            enemies.push_back(enemy);
        }
        break;

        case 470: {
            for (int iii=0; iii < 4; iii++) {
                Cenemy* enemy = new Cenemy(LEFT_SIDE_X+iii*(SCREEN_WIDTH/4.0f), TOP_Y+gl.convert_pixel_height(HEIGHT));
                enemy->add_action(0, MOVE_AT, LEFT_SIDE_X+iii*(SCREEN_WIDTH/4.0f), BOTTOM_Y-gl.convert_pixel_height(50));
                enemy->add_action(600, DELETE_SELF);
                enemies.push_back(enemy);
            }
        }
        break;

        case 460: {
            //Make 2 specials that just flood the screen if you let them
            Cenemy* enemy1 = new Cenemy(LEFT_SIDE_X+gl.convert_pixel_width(100), TOP_Y+gl.convert_pixel_height(HEIGHT), TYPE::SPECIAL, 5);
            Cenemy* enemy2 = new Cenemy(RIGHT_SIDE_X-gl.convert_pixel_width(100), TOP_Y+gl.convert_pixel_height(HEIGHT), TYPE::SPECIAL, 5);
            enemy1->add_action(0, MOVE_AT, LEFT_SIDE_X+gl.convert_pixel_width(100), TOP_Y-gl.convert_pixel_height(60));
            enemy2->add_action(0, MOVE_AT, RIGHT_SIDE_X-gl.convert_pixel_width(100), TOP_Y-gl.convert_pixel_height(60));
            for (int iii = 0; iii < 50; iii++) {
                enemy1->add_action(100+iii*30, SHOOT_AT, (float(rand())/(RAND_MAX/SCREEN_WIDTH))-(SCREEN_WIDTH/2.0f), BOTTOM_Y, 0.01f);
                enemy2->add_action(100+iii*30, SHOOT_AT, (float(rand())/(RAND_MAX/SCREEN_WIDTH))-(SCREEN_WIDTH/2.0f), BOTTOM_Y, 0.01f);
            }

            enemy1->add_action(50*30, MOVE_AT, LEFT_SIDE_X+gl.convert_pixel_width(100), TOP_Y+gl.convert_pixel_height(HEIGHT));
            enemy2->add_action(50*30, MOVE_AT, RIGHT_SIDE_X-gl.convert_pixel_width(100), TOP_Y+gl.convert_pixel_height(HEIGHT));

            enemy1->add_action(50*30+500, DELETE_SELF);
            enemy2->add_action(50*30+500, DELETE_SELF);
            enemies.push_back(enemy1);
            enemies.push_back(enemy2);
        }
        break;

        //A randomly placed stream that all fires at you at once.
        case 500: {
            //set random start and end points for stream
            startX = (float(rand())/(float(RAND_MAX)/SCREEN_WIDTH))-(SCREEN_WIDTH/2.0f);
            endX = (float(rand())/(float(RAND_MAX)/SCREEN_WIDTH))-(SCREEN_WIDTH/2.0f);
        }
        //Fall through
        case 520:
        case 540:
        case 560:
        case 580: {
            Cenemy* enemy = new Cenemy(startX, TOP_Y+gl.convert_pixel_height(HEIGHT+30));
            enemy->add_action(0, MOVE_AT, endX, BOTTOM_Y-gl.convert_pixel_height(50));
            //enemy->add_action(100, MOVE_AT, (-1)*endX, BOTTOM_Y-gl.convert_pixel_height(90));
            enemy->add_action(580-stepCount, SHOOT_PLAYER);
            enemy->add_action(800, DELETE_SELF);
            enemies.push_back(enemy);
        }
        break;

        //A random stream like the last but this time it switches direction part way
        case 660: {
            //set random start and end points for stream
            startX = (float(rand())/(float(RAND_MAX)/SCREEN_WIDTH))-(SCREEN_WIDTH/2.0f);
            endX = (float(rand())/(float(RAND_MAX)/SCREEN_WIDTH))-(SCREEN_WIDTH/2.0f);
        }
        //Fall through
        case 680:
        case 700:
        case 720:
        case 740:
        case 760:
        case 780:
        case 800:
        case 820:
        case 840:
        case 860: {
            Cenemy* enemy = new Cenemy(startX, TOP_Y+gl.convert_pixel_height(HEIGHT+30));
            enemy->add_action(0, MOVE_AT, endX, BOTTOM_Y-gl.convert_pixel_height(50));
            enemy->add_action(100, MOVE_AT, (-1)*endX, BOTTOM_Y-gl.convert_pixel_height(90));
            enemy->add_action(800, DELETE_SELF);
            enemies.push_back(enemy);
        }
        break;

        case 950: {
            for (int iii=0; iii < 15; iii++) {
                Cenemy* enemy = new Cenemy(LEFT_SIDE_X+iii*(SCREEN_WIDTH/15.0f), TOP_Y+gl.convert_pixel_height(HEIGHT));
                enemy->add_action(0, MOVE_AT, LEFT_SIDE_X+iii*(SCREEN_WIDTH/15.0f), BOTTOM_Y-gl.convert_pixel_height(50));
                enemy->add_action(600, DELETE_SELF);
                enemies.push_back(enemy);
            }
        }
        break;

        //Just goes down the middle blindly shooting at you.
        case 960: {
            Cenemy* enemy = new Cenemy(CENTRE_X, TOP_Y+gl.convert_pixel_height(HEIGHT));
            enemy->add_action(0, MOVE_AT, CENTRE_X, BOTTOM_Y-gl.convert_pixel_height(50));
            for (int iii=0; iii < 20; iii++) {
                enemy->add_action(iii*50, SHOOT_PLAYER);
            }
            enemy->add_action(600, DELETE_SELF);
            enemies.push_back(enemy);
        }
        break;

        //left to right making explosions
        case 1050: {
            Cenemy* enemy = new Cenemy(LEFT_SIDE_X-gl.convert_pixel_width(50), TOP_Y-gl.convert_pixel_height(100));
            enemy->add_action(0, MOVE_AT, RIGHT_SIDE_X+gl.convert_pixel_width(50), TOP_Y-gl.convert_pixel_height(100));
            for (int iii=0; iii < 20; iii++) {
                for (int jjj=0; jjj<10; jjj++) {
                    enemy->add_action(iii*50, SHOOT_ANGLE, ((2*3.141592f)/(10.0f))*jjj, 0, 0.01f);
                }
            }
            enemy->add_action(600, DELETE_SELF);
            enemies.push_back(enemy);
        }
        break;*/



        case 1500: {
            //They win.
            return true;
        }
        break;

        default: {
            //Do nothing
        }
        break;
    }
    return false;
}

void CenemyController::set_level(int level) {
    this->level = level;
    //reset the step counter to the start of that level
    stepCount = 0;
}

int CenemyController::get_level() {
    return level;
}
