#pragma once

#include "ACTIONRECORD.hpp"
#include "CLIPEVENTFLAGS.hpp"
#include <cstdint>
#include <optional>
#include <vector>

namespace NSWF
{
    struct CLIPACTIONRECORD
    {
        CLIPEVENTFLAGS events;
        std::optional<uint8_t> keyCode;
        std::vector<ACTIONRECORD> actions;
    };
}
