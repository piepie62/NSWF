#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace unSWF::tags
{
    class DebugIdTag : public SwfTag
    {
    public:
        DebugIdTag(SwfStreamReader& reader) : SwfTag(reader)
        {
            for (auto& byte : debugId)
            {
                byte = reader.readU8();
            }
        }

    private:
        unsigned char debugId[16];
    };
}
