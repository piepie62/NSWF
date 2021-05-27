#pragma once

#include <cstdint>
#include <vector>

namespace NSWF
{
    struct ACTIONRECORD
    {
        uint8_t actionCode;
        std::vector<unsigned char> actionData;
    };
}
