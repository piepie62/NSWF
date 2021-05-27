#pragma once

#include <cstdint>

namespace unSWF
{
    struct KERNINGRECORD
    {
        uint16_t char1;
        uint16_t char2;
        int16_t adjustment;
    };
}
