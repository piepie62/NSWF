#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include <vector>

namespace unSWF::tags
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
            alphaData         = reader.readBytes(this->dataSize() - jpegSize - 8);
        }

        int getCharacterId() const override { return characterId; };

    private:
        int characterId;
        int deblockParam;
        std::vector<unsigned char> jpegData;
        std::vector<unsigned char> alphaData;
    };
}
