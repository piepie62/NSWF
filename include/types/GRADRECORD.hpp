#pragma once

#include "RGBA.hpp"
#include <cstdint>

namespace unSWF
{
    struct GRADRECORD
    {
        uint8_t ratio;
        RGBA color;
    };
}
