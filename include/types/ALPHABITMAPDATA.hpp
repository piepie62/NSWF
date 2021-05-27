#pragma once

#include "ARGB.hpp"
#include <vector>

namespace NSWF
{
    struct ALPHABITMAPDATA
    {
        std::vector<ARGB> pixels;
    };
}
