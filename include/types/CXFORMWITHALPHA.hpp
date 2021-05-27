#pragma once

namespace NSWF
{
    struct CXFORMWITHALPHA
    {
        bool hasAddTerms;
        bool hasMultTerms;
        int redMultTerm;
        int greenMultTerm;
        int blueMultTerm;
        int alphaMultTerm;
        int redAddTerm;
        int greenAddTerm;
        int blueAddTerm;
        int alphaAddTerm;
    };
}
