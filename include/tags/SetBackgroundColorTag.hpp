#pragma once

#include "tags/abstract/SwfTag.hpp"
#include "types/RGB.hpp"

namespace NSWF::tags
{
    class SetBackgroundColorTag : public SwfTag
    {
    public:
        SetBackgroundColorTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::SetBackgroundColor, size)
        {
            bgColor = reader.readRGB();
        }

        RGB bgColor;
    };
}
