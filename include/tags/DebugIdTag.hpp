#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class DebugIdTag : public SwfTag
    {
    public:
        DebugIdTag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::DebugID, size)
        {
            for (auto& byte : debugId)
            {
                byte = reader.readU8();
            }
        }

        unsigned char debugId[16];
    };
}
