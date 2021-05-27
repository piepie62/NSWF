#pragma once

#include "ZONEDATA.hpp"
#include <vector>

namespace NSWF
{
    struct ZONERECORD
    {
        std::vector<ZONEDATA> zoneData;
        bool hasY;
        bool hasX;
    };
}
