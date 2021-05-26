#pragma once

#include <cstdint>
#include <vector>

namespace unSWF
{
    struct ACTIONRECORD
    {
        uint8_t actionCode;
        std::vector<unsigned char> actionData;
    };
}
