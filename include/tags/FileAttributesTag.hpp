#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class FileAttributesTag : public SwfTag
    {
    public:
        FileAttributesTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::FileAttributes, size)
        {
            // reserved
            reader.readFlag();
            useDirectBlit      = reader.readFlag();
            useGpu             = reader.readFlag();
            hasMetadata        = reader.readFlag();
            AS3                = reader.readFlag();
            noCrossDomainCache = reader.readFlag();
            // reserved
            reader.readFlag();
            useNetwork = reader.readFlag();
            reader.readUnsignedBits(24);
        }

        bool useDirectBlit;
        bool useGpu;
        bool hasMetadata;
        bool AS3;
        bool noCrossDomainCache;
        bool useNetwork;
    };
}
