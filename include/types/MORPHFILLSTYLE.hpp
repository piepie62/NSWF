#pragma once

#include "MATRIX.hpp"
#include "MORPHGRADIENT.hpp"
#include "RGBA.hpp"
#include <optional>

namespace NSWF
{
    struct MORPHFILLSTYLE
    {
        enum class Type
        {
            Solid                      = 0,
            LinearGradient             = 0x10,
            RadialGradient             = 0x12,
            FocalRadialGradient        = 0x13,
            RepeatingBitmap            = 0x40,
            ClippedBitmap              = 0x41,
            NonSmoothedRepeatingBitmap = 0x42,
            NonSmoothedClippedBitmap   = 0x43
        } type;
        std::optional<RGBA> startColor;
        std::optional<RGBA> endColor;
        std::optional<MATRIX> startGradientMatrix;
        std::optional<MATRIX> endGradientMatrix;
        std::optional<MORPHGRADIENT> gradient;
        std::optional<uint16_t> bitmapId;
        std::optional<MATRIX> startBitmapMatrix;
        std::optional<MATRIX> endBitmapMatrix;
    };
}
