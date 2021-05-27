#pragma once

#include "types/RGB.hpp"
#include <vector>

namespace NSWF
{
    template <typename ColorElement>
    struct COLORMAPDATA
    {
        std::vector<ColorElement> colorTable;
        std::vector<unsigned char> pixelData;
    };
}
