#pragma once

#include "types/FILLSTYLE.hpp"
#include "types/LINESTYLE.hpp"
#include "types/LINESTYLE2.hpp"
#include <cstdint>
#include <optional>
#include <variant>
#include <vector>

namespace NSWF
{
    struct STYLECHANGERECORD
    {
        bool stateNewStyles;
        bool stateLineStyle;
        bool stateFillStyle1;
        bool stateFillStyle0;
        bool stateMoveTo;

        std::optional<uint8_t> moveBits;
        std::optional<int32_t> moveDeltaX;
        std::optional<int32_t> moveDeltaY;

        std::optional<uint16_t> fillStyle0;
        std::optional<uint16_t> fillStyle1;
        std::optional<uint16_t> lineStyle;
        std::optional<std::vector<FILLSTYLE>> fillStyles;
        std::optional<std::variant<std::vector<LINESTYLE>, std::vector<LINESTYLE2>>> lineStyles;
    };
}
