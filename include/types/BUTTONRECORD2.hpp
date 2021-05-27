#pragma once

#include "CXFORMWITHALPHA.hpp"
#include "FILTERLIST.hpp"
#include "MATRIX.hpp"

namespace NSWF
{
    struct BUTTONRECORD2
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
        CXFORMWITHALPHA colorTransform;
        FILTERLIST filters;
        enum BlendMode
        {
            Normal0,
            Normal1,
            Layer,
            Multiply,
            Screen,
            Lighten,
            Darken,
            Difference,
            Add,
            Subtract,
            Invert,
            Alpha,
            Erase,
            Overlay,
            Hardlight
        } blendmode;
    };
}
