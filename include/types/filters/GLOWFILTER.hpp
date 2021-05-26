#pragma once

#include "types/RGBA.hpp"
#include <cstdint>

namespace unSWF
{
    struct GLOWFILTER
    {
        RGBA shadowColor;
        uint32_t blurX;
        uint32_t blurY;
        uint16_t strength;
        bool innerGlow;
        bool knockout;
        bool compositeSource;
        int passes;
    };
}
