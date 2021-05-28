#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class SetTabIndexTag : public SwfTag
    {
    public:
        SetTabIndexTag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::SetTabIndex, size)
        {
            depth    = reader.readU16();
            tabIndex = reader.readU16();
        }

        uint16_t depth;
        uint16_t tabIndex;
    };
}
