#pragma once

#include "SOUNDENVELOPE.hpp"
#include <cstdint>
#include <vector>

namespace NSWF
{
    struct SOUNDINFO
    {
        bool syncStop;
        bool syncNoMultiple;
        std::optional<uint32_t> inPoint;
        std::optional<uint32_t> outPoint;
        std::optional<uint16_t> loopCount;
        std::optional<std::vector<SOUNDENVELOPE>> envelopeRecords;
    };
}
