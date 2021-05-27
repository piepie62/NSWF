#pragma once

#include "ARGB.hpp"
#include "RGBA.hpp"
#include <cstdint>

namespace unSWF
{
    struct RGB
    {
        operator ARGB() const { return {0, red, green, blue}; }
        operator RGBA() const { return {red, green, blue, 0}; }
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };
}
