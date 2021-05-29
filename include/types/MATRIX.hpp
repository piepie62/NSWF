#pragma once

#include <cstdint>
#include <optional>

namespace NSWF
{
    struct MATRIX
    {
        std::optional<uint32_t> scaleX;
        std::optional<uint32_t> scaleY;
        std::optional<uint32_t> rotateSkew0;
        std::optional<uint32_t> rotateSkew1;
        int32_t translateX;
        int32_t translateY;
    };
}
