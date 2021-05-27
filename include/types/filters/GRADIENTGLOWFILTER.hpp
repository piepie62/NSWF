#pragma once

#include "types/RGBA.hpp"
#include "types/basic/fixed16.hpp"
#include "types/basic/fixed32.hpp"
#include <cstdint>
#include <vector>

namespace NSWF
{
    struct GRADIENTGLOWFILTER
    {
        std::vector<RGBA> gradientColors;
        std::vector<uint8_t> gradientRatio;
        fixed32 blurX;
        fixed32 blurY;
        fixed32 angle;
        fixed32 distance;
        fixed16 strength;
        bool innerShadow;
        bool knockout;
        bool compositeSource;
        bool onTop;
        int passes;
    };
}
