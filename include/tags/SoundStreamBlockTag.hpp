#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class SoundStreamBlockTag : public SwfTag
    {
    public:
        SoundStreamBlockTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::SoundStreamBlock, size)
        {
            soundData = reader.readBytes(size);
        }

        std::vector<unsigned char> soundData;
    };
}
