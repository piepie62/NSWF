#pragma once

#include "types/RGBA.hpp"
#include "types/basic/fixed16.hpp"
#include "types/basic/fixed32.hpp"
#include <cstdint>

namespace NSWF
{
    struct DROPSHADOWFILTER
    {
        RGBA shadowColor;
        fixed32 blurX;
        fixed32 blurY;
        fixed32 angle;
        fixed32 distance;
        fixed16 strength;
        bool innerShadow;
        bool knockout;
        bool compositeSource;
        int passes;
    };
}
