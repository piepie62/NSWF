
#pragma once

#include "types/filters/BEVELFILTER.hpp"
#include "types/filters/BLURFILTER.hpp"
#include "types/filters/COLORMATRIXFILTER.hpp"
#include "types/filters/CONVOLUTIONFILTER.hpp"
#include "types/filters/DROPSHADOWFILTER.hpp"
#include "types/filters/GLOWFILTER.hpp"
#include "types/filters/GRADIENTBEVELFILTER.hpp"
#include "types/filters/GRADIENTGLOWFILTER.hpp"
#include <variant>

namespace NSWF
{
    struct FILTER
    {
        enum FilterType
        {
            DropShadow,
            Blur,
            Glow,
            Bevel,
            GradientGlow,
            Convolution,
            ColorMatrix,
            GradientBevel
        };

        std::variant<DROPSHADOWFILTER, BLURFILTER, GLOWFILTER, BEVELFILTER, GRADIENTGLOWFILTER,
            CONVOLUTIONFILTER, COLORMATRIXFILTER, GRADIENTBEVELFILTER>
            filter;
    };
}
