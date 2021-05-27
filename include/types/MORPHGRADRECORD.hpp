#pragma once

#include "RGBA.hpp"
#include <cstdint>

namespace NSWF
{
    struct MORPHGRADRECORD
    {
        uint8_t startRatio;
        RGBA startColor;
        uint8_t endRatio;
        RGBA endColor;
    };
}
