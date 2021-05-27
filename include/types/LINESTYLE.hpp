#pragma once

#include "RGBA.hpp"
#include <cstdint>

namespace NSWF
{
    struct LINESTYLE
    {
        uint16_t width;
        RGBA color;
    };
}
