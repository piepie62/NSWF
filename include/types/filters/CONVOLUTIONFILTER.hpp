#pragma once

#include "types/RGBA.hpp"
#include <vector>

namespace unSWF
{
    struct CONVOLUTIONFILTER
    {
        int matrixX;
        int matrixY;
        float divisor;
        float bias;
        std::vector<float> matrix;
        RGBA defaultColor;
        bool clamp;
        bool preserveAlpha;
    };
}
