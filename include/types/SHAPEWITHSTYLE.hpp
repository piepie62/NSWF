#pragma once

#include "FILLSTYLE.hpp"
#include "LINESTYLE.hpp"
#include "LINESTYLE2.hpp"
#include "SHAPERECORD.hpp"
#include <variant>
#include <vector>

namespace unSWF
{
    struct SHAPEWITHSTYLE
    {
        std::vector<FILLSTYLE> fillStyles;
        std::variant<std::vector<LINESTYLE>, std::vector<LINESTYLE2>> lineStyles;
        std::vector<SHAPERECORD> records;
    };
}
