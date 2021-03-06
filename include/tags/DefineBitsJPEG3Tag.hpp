#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include <vector>

namespace NSWF::tags
{
    class DefineBitsJPEG3Tag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineBitsJPEG3Tag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::DefineBitsJPEG3, size)
        {
            characterId       = reader.readU16();
            uint32_t jpegSize = reader.readU32();
            jpegData          = reader.readBytes(jpegSize);
            alphaData         = reader.decompressZlibFromStream(size - jpegSize - 6);
        }

        uint16_t getCharacterId() const override { return characterId; };

        uint16_t characterId;
        std::vector<unsigned char> jpegData;
        std::vector<unsigned char> alphaData;
    };
}
