#pragma once

#include "ZONEDATA.hpp"
#include <vector>

namespace unSWF
{
    struct ZONERECORD
    {
        std::vector<ZONEDATA> zoneData;
        bool hasY;
        bool hasX;
    };
}
