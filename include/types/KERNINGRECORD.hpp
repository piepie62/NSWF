#pragma once

#include <cstdint>

namespace NSWF
{
    struct KERNINGRECORD
    {
        uint16_t char1;
        uint16_t char2;
        int16_t adjustment;
    };
}
