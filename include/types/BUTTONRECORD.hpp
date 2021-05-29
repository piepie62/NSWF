#pragma once

#include "MATRIX.hpp"
#include <vector>

namespace NSWF
{
    struct BUTTONRECORD
    {
        bool stateHitTest;
        bool stateDown;
        bool stateOver;
        bool stateUp;
        int characterId;
        int placeDepth;
        MATRIX placeMatrix;
    };
}
