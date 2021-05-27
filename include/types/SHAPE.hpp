#pragma once

#include "SHAPERECORD.hpp"
#include <cstdint>
#include <vector>

namespace unSWF
{
    struct SHAPE
    {
        uint8_t numFillBits;
        uint8_t numLineBits;
        std::vector<SHAPERECORD> records;
    };
}
