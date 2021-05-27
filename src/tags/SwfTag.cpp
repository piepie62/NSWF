#include "tags/abstract/SwfTag.hpp"
#include <stdexcept>

std::unique_ptr<NSWF::tags::SwfTag> NSWF::tags::SwfTag::parseTag(SwfStreamReader& reader)
{
    SwfTagType type = SwfTagType(reader.readUnsignedBits(10));
    size_t size     = (size_t)reader.readUnsignedBits(6);
    if (size == 0x3F)
    {
        size = reader.readU32();
    }

    switch (type)
    {
        default:
            throw std::invalid_argument("Unrecognized SWF tag type");
    }
}
