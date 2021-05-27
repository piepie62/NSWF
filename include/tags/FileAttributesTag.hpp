#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class FileAttributesTag : public SwfTag
    {
    public:
        FileAttributesTag(SwfStreamReader& reader) : SwfTag(reader)
        {
            // reserved
            reader.readFlag();
            mUseDirectBlit = reader.readFlag();
            mUseGpu        = reader.readFlag();
            mHasMetadata   = reader.readFlag();
            mAS3           = reader.readFlag();
            // reserved
            reader.readUnsignedBits(2);
            mUseNetwork = reader.readFlag();
            reader.readUnsignedBits(24);
        }

        bool mUseDirectBlit;
        bool mUseGpu;
        bool mHasMetadata;
        bool mAS3;
        bool mUseNetwork;
    };
}
