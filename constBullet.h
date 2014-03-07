#pragma once

namespace BULLET {
    //The min and max depth that the bullets can be rendered at.
    //This is to a range to allow for the use of the z buffer to speed it up.
    const float DEPTH_MIN = 0.5f;
    const float DEPTH_MAX = 0.6f;
    //Default bullet speed in OpenGl units more or less (but without compensation for hoizontal/vertical pixel width difference)
    const float SPEED = 0.02f;
}
