#pragma once

#include "FILLSTYLE.hpp"
#include "RGBA.hpp"
#include "types/basic/fixed16.hpp"
#include <cstdint>
#include <optional>
#include <variant>

namespace unSWF
{
    struct LINESTYLE2
    {
        uint16_t width;
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
        std::variant<RGBA, FILLSTYLE> fill;
    };
}
