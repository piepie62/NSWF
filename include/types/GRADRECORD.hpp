#pragma once

#include "RGBA.hpp"
#include <cstdint>

namespace NSWF
{
    struct GRADRECORD
    {
        uint8_t ratio;
        RGBA color;
    };
}
