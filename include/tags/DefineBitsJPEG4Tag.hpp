#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include <vector>

namespace NSWF::tags
{
    class DefineBitsJPEG4Tag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineBitsJPEG4Tag(SwfStreamReader& reader) : SwfTag(reader)
        {
            characterId       = reader.readU16();
            uint32_t jpegSize = reader.readU32();
            deblockParam      = reader.readU16();
            jpegData          = reader.readBytes(jpegSize);
            alphaData         = reader.decompressZlibFromStream(dataSize() - jpegSize - 8);
        }

        uint16_t getCharacterId() const override { return characterId; };

        uint16_t characterId;
        uint16_t deblockParam;
        std::vector<unsigned char> jpegData;
        std::vector<unsigned char> alphaData;
    };
}
