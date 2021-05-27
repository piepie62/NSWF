#pragma once

#include "GRADRECORD.hpp"
#include <cstdint>
#include <vector>

namespace NSWF
{
    struct GRADIENT
    {
        enum class SpreadMode
        {
            Pad,
            Reflect,
            Repeat
        } spreadMode;
        enum class InterpolationMode
        {
            Normal,
            Linear
        } interpolationMode;
        std::vector<GRADRECORD> gradientRecords;
    };
}
