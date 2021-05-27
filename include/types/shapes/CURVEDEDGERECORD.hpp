#pragma once

#include <cstdint>

namespace NSWF
{
    struct CURVEDEDGERECORD
    {
        int32_t controlDeltaX;
        int32_t controlDeltaY;
        int32_t anchorDeltaX;
        int32_t anchorDeltay;
    };
}
