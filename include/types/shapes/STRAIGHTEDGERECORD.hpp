#pragma once

#include <cstdint>
#include <optional>

namespace unSWF
{
    struct STRAIGHTEDGERECORD
    {
        std::optional<int32_t> deltaX;
        std::optional<int32_t> deltaY;
    };
}
