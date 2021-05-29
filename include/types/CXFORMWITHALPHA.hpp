#pragma once

namespace NSWF
{
    struct CXFORMWITHALPHA
    {
        std::optional<int> redMultTerm;
        std::optional<int> greenMultTerm;
        std::optional<int> blueMultTerm;
        std::optional<int> alphaMultTerm;
        std::optional<int> redAddTerm;
        std::optional<int> greenAddTerm;
        std::optional<int> blueAddTerm;
        std::optional<int> alphaAddTerm;
    };
}
