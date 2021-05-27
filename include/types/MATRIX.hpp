#pragma once

#include <cstdint>

namespace NSWF
{
    struct MATRIX
    {
        bool hasScale;
        uint32_t scaleX;
        uint32_t scaleY;
        bool hasRotate;
        uint32_t rotateSkew0;
        uint32_t rotateSkew1;
        int32_t translateX;
        int32_t translateY;
    };
}
