#include "CstarController.h"

void CstarController::cover_screen(std::default_random_engine* randomEngine, CparticleController &particleController) {
    int framesToCover = OPENGL::SCREEN_HEIGHT/STAR_CONTROLLER::STAR_SPEED;
    particleController.make_ready_to_add();
    for (int iii = 0; iii < framesToCover; iii++) {
        std::uniform_int_distribution<int> chance(0, STAR_CONTROLLER::STAR_GENERATION);

        if (chance(*randomEngine) == 0) {
            std::uniform_real_distribution<float> speedShift(0.0f, STAR_CONTROLLER::STAR_SPEED_RANDOM_MAX);
            float speed = -STAR_CONTROLLER::STAR_SPEED - speedShift(*randomEngine);

            std::uniform_real_distribution<float> xDistribution(OPENGL::LEFT_SIDE_X, OPENGL::RIGHT_SIDE_X);
            //This keeps equal distribution for the first frame over anywhere a star could be (instead of starting them all at the same offset)
            std::uniform_real_distribution<float> yDistribution(OPENGL::TOP_Y-speed, OPENGL::TOP_Y);

            std::uniform_real_distribution<float> brightnessDistribution(STAR_CONTROLLER::STAR_BRIGHTNESS_MIN, STAR_CONTROLLER::STAR_BRIGHTNESS_MAX);
            std::uniform_real_distribution<float> colourShift(STAR_CONTROLLER::STAR_COLOUR_REDUCTION_MIN, STAR_CONTROLLER::STAR_COLOUR_REDUCTION_MAX);
            float brightness = brightnessDistribution(*randomEngine);

            float y = yDistribution(*randomEngine)+iii*speed;

            if (y > OPENGL::BOTTOM_Y) {
                particleController.add_particle(xDistribution(*randomEngine), y, 0.0f, speed,
                                                brightness-colourShift(*randomEngine), brightness-colourShift(*randomEngine), brightness-colourShift(*randomEngine));
            }
        }
    }
    particleController.finish_adding();
}

void CstarController::step(std::default_random_engine* randomEngine, CparticleController &particleController) {
    std::uniform_int_distribution<int> chance(0, STAR_CONTROLLER::STAR_GENERATION);

    if (chance(*randomEngine) == 0) {
        particleController.make_ready_to_add();
        add_star(randomEngine, particleController);
        particleController.finish_adding();
    }
}

void CstarController::add_star(std::default_random_engine* randomEngine, CparticleController &particleController) {
    std::uniform_real_distribution<float> speedShift(0.0f, STAR_CONTROLLER::STAR_SPEED_RANDOM_MAX);
    float speed = -STAR_CONTROLLER::STAR_SPEED - speedShift(*randomEngine);
    std::uniform_real_distribution<float> xDistribution(OPENGL::LEFT_SIDE_X, OPENGL::RIGHT_SIDE_X);
    //This keeps equal distribution for the first frame over anywhere a star could be (instead of starting them all at the same offset)
    std::uniform_real_distribution<float> yDistribution(OPENGL::TOP_Y-speed, OPENGL::TOP_Y);

    std::uniform_real_distribution<float> brightnessDistribution(STAR_CONTROLLER::STAR_BRIGHTNESS_MIN, STAR_CONTROLLER::STAR_BRIGHTNESS_MAX);
    std::uniform_real_distribution<float> colourShift(STAR_CONTROLLER::STAR_COLOUR_REDUCTION_MIN, STAR_CONTROLLER::STAR_COLOUR_REDUCTION_MAX);
    float brightness = brightnessDistribution(*randomEngine);

    particleController.add_particle(xDistribution(*randomEngine), yDistribution(*randomEngine), 0.0f, speed,
                                    brightness-colourShift(*randomEngine), brightness-colourShift(*randomEngine), brightness-colourShift(*randomEngine));
}
