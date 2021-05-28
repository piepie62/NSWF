#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class RemoveObject2Tag : public SwfTag
    {
    public:
        RemoveObject2Tag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::RemoveObject2, size)
        {
            depth = reader.readU16();
        }
        uint16_t depth;
    };
}
