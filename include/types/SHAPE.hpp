#pragma once

#include "SHAPERECORD.hpp"
#include <vector>

namespace unSWF
{
    struct SHAPE
    {
        std::vector<SHAPERECORD> records;
    };
}
