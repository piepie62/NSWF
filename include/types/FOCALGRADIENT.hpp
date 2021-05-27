#pragma once

#include "GRADRECORD.hpp"
#include "types/basic/fixed16.hpp"
#include <cstdint>
#include <vector>

namespace unSWF
{
    struct FOCALGRADIENT
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
        fixed16 focalPoint;
    };
}
