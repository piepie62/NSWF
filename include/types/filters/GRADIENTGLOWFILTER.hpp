#pragma once

#include "types/RGBA.hpp"
#include <cstdint>
#include <vector>

namespace unSWF
{
    struct GRADIENTGLOWFILTER
    {
        std::vector<RGBA> gradientColors;
        std::vector<uint8_t> gradientRatio;
        uint32_t blurX;
        uint32_t blurY;
        uint32_t angle;
        uint32_t distance;
        uint16_t strength;
        bool innerShadow;
        bool knockout;
        bool compositeSource;
        bool onTop;
        int passes;
    };
}
