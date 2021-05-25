#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include <vector>

namespace unSWF::tags
{
    class DefineBitsJPEG3Tag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineBitsJPEG3Tag(SwfStreamReader& reader) : SwfTag(reader)
        {
            characterId       = reader.readU16();
            uint32_t jpegSize = reader.readU32();
            jpegData          = reader.readBytes(jpegSize);
            alphaData         = reader.readBytes(this->dataSize() - jpegSize - 6);
        }

        int getCharacterId() const override { return characterId; };

    private:
        int characterId;
        std::vector<unsigned char> jpegData;
        std::vector<unsigned char> alphaData;
    };
}
