#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class MetadataTag : public SwfTag
    {
    public:
        MetadataTag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::Metadata, size)
        {
            metadata = reader.readNTString();
        }

        std::string metadata;
    };
}
