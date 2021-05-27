#pragma once

#include "types/RGBA.hpp"
#include "types/basic/fixed16.hpp"
#include "types/basic/fixed32.hpp"
#include <cstdint>

namespace NSWF
{
    struct GLOWFILTER
    {
        RGBA shadowColor;
        fixed32 blurX;
        fixed32 blurY;
        fixed16 strength;
        bool innerGlow;
        bool knockout;
        bool compositeSource;
        int passes;
    };
}
