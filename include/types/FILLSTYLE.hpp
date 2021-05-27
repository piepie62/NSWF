#pragma once

#include "FOCALGRADIENT.hpp"
#include "GRADIENT.hpp"
#include "MATRIX.hpp"
#include "RGB.hpp"
#include "RGBA.hpp"
#include <optional>

namespace unSWF
{
    struct FILLSTYLE
    {
        enum class Type
        {
            Solid                      = 0,
            LinearGradient             = 0x10,
            RadialGradient             = 0x12,
            FocalGradient              = 0x13,
            RepeatingBitmap            = 0x40,
            ClippedBitmap              = 0x41,
            NonSmoothedRepeatingBitmap = 0x42,
            NonSmoothedClippedBitmap   = 0x43
        } type;
        std::optional<RGBA> color;
        std::optional<MATRIX> gradientMatrix;
        std::optional<GRADIENT> gradient;
        std::optional<FOCALGRADIENT> focalGradient;
        std::optional<uint16_t> bitmapId;
        std::optional<MATRIX> bitmapMatrix;
    };
}
