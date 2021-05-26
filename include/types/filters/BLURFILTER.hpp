#pragma once

#include <cstdint>

namespace unSWF
{
    struct BLURFILTER
    {
        uint32_t blurX;
        uint32_t blurY;
        int passes;
    };
}
