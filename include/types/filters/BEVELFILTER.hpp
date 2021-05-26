#pragma once

#include "types/RGBA.hpp"
#include <cstdint>

namespace unSWF
{
    struct BEVELFILTER
    {
        RGBA shadowColor;
        RGBA highlightColor;
        uint32_t blurX;
        uint32_t blurY;
        uint32_t angle;
        uint32_t distance;
        uint16_t strength;
        bool innerShadow;
        bool knockout;
        bool compositeSource;
        bool onTop;
    };
}
