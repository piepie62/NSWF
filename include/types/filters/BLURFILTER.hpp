#pragma once

#include "types/basic/fixed32.hpp"
#include <cstdint>

namespace NSWF
{
    struct BLURFILTER
    {
        fixed32 blurX;
        fixed32 blurY;
        int passes;
    };
}
