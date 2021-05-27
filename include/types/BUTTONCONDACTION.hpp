#pragma once

#include "types/ACTIONRECORD.hpp"
#include <cstdint>
#include <vector>

namespace unSWF
{
    struct BUTTONCONDACTION
    {
        uint16_t size;
        bool idleToOverDown;
        bool outDownToIdle;
        bool outDownToOverDown;
        bool overDownToOutDown;
        bool overDownToOverUp;
        bool overUpToOverDown;
        bool overUpToIdle;
        bool idleToOverUp;
        uint8_t keyPress;
        bool overDownToIdle;
        std::vector<ACTIONRECORD> actions;
    };
}
