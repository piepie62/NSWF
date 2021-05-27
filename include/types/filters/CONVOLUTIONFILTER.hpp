#pragma once

#include "types/RGBA.hpp"
#include <vector>

namespace NSWF
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
