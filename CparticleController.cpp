#include "CparticleController.h"

CparticleController::CparticleController(): ping(), pong(), active(&ping), inactive(&pong), program(), frame(1), noFreeUnusedBefore(0), finalUsedIndex(-1), startOfActive(0) {
    ping.create(PARTICLE_CONTROLLER::MAX_POINTS*sizeof(OPENGL::particlePoint));
    pong.create(PARTICLE_CONTROLLER::MAX_POINTS*sizeof(OPENGL::particlePoint));
    for (int iii = 0; iii < PARTICLE_CONTROLLER::MAX_POINTS; iii++) {
        particleDeathsFrames[iii] = 0;
    }
    init();
}

bool CparticleController::init() {
    program.init();

    const GLchar* outputs[3] = {"position2d", "speed2d", "colour"};
    glTransformFeedbackVaryings(program.get_id(), 3, outputs, GL_INTERLEAVED_ATTRIBS);
    if (program.set_code(PARTICLE_CONTROLLER::VERTEX_CODE, PARTICLE_CONTROLLER::FRAGMENT_CODE) == false) {
        return false;
    }

    GLint position2dInLocation = program.get_AttribLocation("position2dIn");
    if (position2dInLocation == -1) {
        return false;
    }
    GLint speed2dInLocation = program.get_AttribLocation("speed2dIn");
    if (speed2dInLocation == -1) {
        return false;
    }
    GLint colourInLocation = program.get_AttribLocation("colourIn");
    if (colourInLocation == -1) {
        return false;
    }

    ping.bind();
    ping.bind_vbo();
    glEnableVertexAttribArray(position2dInLocation);
    glEnableVertexAttribArray(speed2dInLocation);
    glEnableVertexAttribArray(colourInLocation);
    glVertexAttribPointer(position2dInLocation, 2, GL_FLOAT, GL_FALSE, sizeof(OPENGL::particlePoint), (GLvoid*)offsetof(OPENGL::particlePoint, pos2d));
    glVertexAttribPointer(speed2dInLocation, 2, GL_FLOAT, GL_FALSE, sizeof(OPENGL::particlePoint), (GLvoid*)offsetof(OPENGL::particlePoint, spd2d));
    glVertexAttribPointer(colourInLocation, 3, GL_FLOAT, GL_FALSE, sizeof(OPENGL::particlePoint), (GLvoid*)offsetof(OPENGL::particlePoint, col));

    pong.bind();
    pong.bind_vbo();
    glEnableVertexAttribArray(position2dInLocation);
    glEnableVertexAttribArray(speed2dInLocation);
    glEnableVertexAttribArray(colourInLocation);
    glVertexAttribPointer(position2dInLocation, 2, GL_FLOAT, GL_FALSE, sizeof(OPENGL::particlePoint), (GLvoid*)offsetof(OPENGL::particlePoint, pos2d));
    glVertexAttribPointer(speed2dInLocation, 2, GL_FLOAT, GL_FALSE, sizeof(OPENGL::particlePoint), (GLvoid*)offsetof(OPENGL::particlePoint, spd2d));
    glVertexAttribPointer(colourInLocation, 3, GL_FLOAT, GL_FALSE, sizeof(OPENGL::particlePoint), (GLvoid*)offsetof(OPENGL::particlePoint, col));

    pong.unbind();
    pong.unbind_vbo();

    return true;
}

void CparticleController::draw_and_step() {
    if (noFreeUnusedBefore > finalUsedIndex) {
        finalUsedIndex = noFreeUnusedBefore-1;
    } else {
        //try to reduce finalUsedIndex
        while (particleDeathsFrames[finalUsedIndex] < frame) {
            finalUsedIndex--;
        }
    }
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glDepthMask(GL_FALSE);

    program.use();
    active->bind();
    GLuint inactiveId = inactive->get_vbo()->get_id();
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, inactiveId);
    glBeginTransformFeedback(GL_POINTS);
        glDrawArrays(GL_POINTS, 0, finalUsedIndex+1);
    glEndTransformFeedback();

    glDepthMask(GL_TRUE);
    glDisable(GL_MULTISAMPLE);
    glDisable(GL_BLEND);

    if (active == &ping) {
        active = &pong;
        inactive = &ping;
    } else {
        active = &ping;
        inactive = &pong;
    }
    noFreeUnusedBefore = 0;
    frame++;
}

void CparticleController::step() {
    glEnable(GL_RASTERIZER_DISCARD);
    draw_and_step();
    glDisable(GL_RASTERIZER_DISCARD);
}

bool CparticleController::make_ready_to_add() {
    active->bind_vbo();
    startOfActive = (OPENGL::particlePoint*)active->map_vbo(GL_WRITE_ONLY);
    if (startOfActive == NULL) {
        fprintf(stderr, "Could not map active particle buffer.\n");
        return false;
    }
    return true;
}

void CparticleController::finish_adding() {
    active->unmap_vbo();
    startOfActive = NULL;
}

void CparticleController::add_particle(float x, float y, float speedX, float speedY, float r, float g, float b) {
    while (particleDeathsFrames[noFreeUnusedBefore] >= frame) {
        noFreeUnusedBefore++;
    }
    if (noFreeUnusedBefore >= PARTICLE_CONTROLLER::MAX_POINTS) {
        //no space! Do nothing.
        return;
    }

    startOfActive[noFreeUnusedBefore] = {{x, y}, {speedX, speedY}, {r, g, b}};

    //work out frame that particle will be offscreen at
    float distanceFromEdgeX;
    if (speedX > 0.0f) {
        distanceFromEdgeX = OPENGL::RIGHT_SIDE_X - x;
    } else {
        //will be negative but that's ok as it's divided by a negative next.
        distanceFromEdgeX = OPENGL::LEFT_SIDE_X - x;
    }
    int timeUntilEdgeX = distanceFromEdgeX / speedX;

    float distanceFromEdgeY;
    if (speedY > 0.0f) {
        distanceFromEdgeY = OPENGL::TOP_Y - y;
    } else {
        //will be negative but that's ok as it's divided by a negative next.
        distanceFromEdgeY = OPENGL::BOTTOM_Y - y;
    }
    int timeUntilEdgeY = distanceFromEdgeY / speedY;

    //These basically catch divide by 0 related problems
    if (timeUntilEdgeX < 0) {
        timeUntilEdgeX = 2000;
    }
    if (timeUntilEdgeY < 0) {
        timeUntilEdgeY = 2000;
    }

    //we only care about smallest as after that it's offscreen
    if (timeUntilEdgeX < timeUntilEdgeY) {
        particleDeathsFrames[noFreeUnusedBefore] = timeUntilEdgeX+frame;
    } else {
        particleDeathsFrames[noFreeUnusedBefore] = timeUntilEdgeY+frame;
    }

    noFreeUnusedBefore++;
}

CparticleController::~CparticleController() {
    //empty
}
