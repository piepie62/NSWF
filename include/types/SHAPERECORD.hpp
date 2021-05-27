#pragma once

#include "types/shapes/CURVEDEDGERECORD.hpp"
#include "types/shapes/ENDSHAPERECORD.hpp"
#include "types/shapes/STRAIGHTEDGERECORD.hpp"
#include "types/shapes/STYLECHANGERECORD.hpp"
#include <variant>

namespace unSWF
{
    struct SHAPERECORD
    {
        std::variant<ENDSHAPERECORD, STYLECHANGERECORD, CURVEDEDGERECORD, STRAIGHTEDGERECORD>
            record;
    };
}
