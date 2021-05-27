#pragma once

#include "MORPHFILLSTYLE.hpp"
#include "RGBA.hpp"
#include "types/basic/fixed16.hpp"
#include <cstdint>
#include <optional>
#include <variant>

namespace NSWF
{
    struct MORPHLINESTYLE2
    {
        uint16_t startWidth;
        uint16_t endWidth;
        enum class CapStyle
        {
            Round,
            None,
            Square
        } startCapStyle;
        enum class JoinStyle
        {
            Round,
            Bevel,
            Miter
        } joinStyle;
        bool noHorizThicknessScale;
        bool noVertThicknessScale;
        bool pixelHinting;
        bool noClose;
        CapStyle endCapStyle;
        std::optional<fixed16> miterLimitFactor;
        std::optional<RGBA> startColor;
        std::optional<RGBA> endColor;
        std::optional<MORPHFILLSTYLE> fill;
    };
}
