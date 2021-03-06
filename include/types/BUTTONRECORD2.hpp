#pragma once

#include "CXFORMWITHALPHA.hpp"
#include "FILTER.hpp"
#include "MATRIX.hpp"
#include <optional>
#include <vector>

namespace NSWF
{
    struct BUTTONRECORD2
    {
        bool stateHitTest;
        bool stateDown;
        bool stateOver;
        bool stateUp;
        int characterId;
        int placeDepth;
        MATRIX placeMatrix;
        CXFORMWITHALPHA colorTransform;
        std::optional<std::vector<FILTER>> filters;
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
        };
        std::optional<BlendMode> blendmode;
    };
}
