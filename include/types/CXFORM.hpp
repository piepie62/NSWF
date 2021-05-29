#pragma once

#include <optional>

namespace NSWF
{
    struct CXFORM
    {
        std::optional<int> redMultTerm;
        std::optional<int> greenMultTerm;
        std::optional<int> blueMultTerm;
        std::optional<int> redAddTerm;
        std::optional<int> greenAddTerm;
        std::optional<int> blueAddTerm;
    };
}
