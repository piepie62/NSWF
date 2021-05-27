#pragma once

#include "MORPHGRADRECORD.hpp"
#include <cstdint>
#include <vector>

namespace NSWF
{
    struct MORPHGRADIENT
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
        std::vector<MORPHGRADRECORD> gradientRecords;
    };
}
