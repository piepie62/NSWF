#pragma once

#include "types/GLYPHENTRY.hpp"
#include "types/RGBA.hpp"
#include <optional>
#include <vector>

namespace NSWF
{
    struct TEXTRECORD
    {
        std::optional<uint16_t> fontId;
        std::optional<RGBA> color;
        std::optional<int16_t> xOffset;
        std::optional<int16_t> yOffset;
        std::optional<uint16_t> textHeight;
        std::vector<GLYPHENTRY> glyphs;
    };
}
