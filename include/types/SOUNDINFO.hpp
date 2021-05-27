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
        bool hasEnvelope;
        bool hasLoops;
        bool hasOutPoint;
        bool hasInPoint;
        uint32_t inPoint;
        uint32_t outPoint;
        uint16_t loopCount;
        std::vector<SOUNDENVELOPE> envelopeRecords;
    };
}
