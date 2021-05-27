#pragma once

#include "SHAPERECORD.hpp"
#include <vector>

namespace NSWF
{
    struct SHAPE
    {
        std::vector<SHAPERECORD> records;
    };
}
