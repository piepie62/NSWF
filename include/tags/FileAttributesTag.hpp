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
            reader.readUnsignedBits(1);
            mUseDirectBlit = reader.readUnsignedBits(1);
            mUseGpu        = reader.readUnsignedBits(1);
            mHasMetadata   = reader.readUnsignedBits(1);
            mAS3           = reader.readUnsignedBits(1);
            // reserved
            reader.readUnsignedBits(2);
            mUseNetwork = reader.readUnsignedBits(1);
            reader.readUnsignedBits(24);
        }

        bool mUseDirectBlit;
        bool mUseGpu;
        bool mHasMetadata;
        bool mAS3;
        bool mUseNetwork;
    };
}
