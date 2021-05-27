#pragma once

#include <cstdint>

namespace NSWF
{
    struct SOUNDENVELOPE
    {
        uint32_t pos44;
        uint16_t leftLevel;
        uint16_t rightLevel;
    };
}
