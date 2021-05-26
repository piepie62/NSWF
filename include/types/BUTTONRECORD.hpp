#pragma once

#include "MATRIX.hpp"

namespace unSWF
{
    struct BUTTONRECORD
    {
        bool hasBlendMode;
        bool hasFilterList;
        bool stateHitTest;
        bool stateDown;
        bool stateOver;
        bool stateUp;
        int characterId;
        int placeDepth;
        MATRIX placeMatrix;
    };
}
