#pragma once

#include "RGBA.hpp"
#include <cstdint>

namespace NSWF
{
    struct MORPHLINESTYLE
    {
        uint16_t startWidth;
        uint16_t endWidth;
        RGBA startColor;
        RGBA endColor;
    };
}
