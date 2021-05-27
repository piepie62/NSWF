#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class DefineBitsJPEG2Tag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineBitsJPEG2Tag(SwfStreamReader& reader) : SwfTag(reader)
        {
            characterId = reader.readU16();
            imageData   = reader.readBytes(this->dataSize() - 2);
        }

        uint16_t getCharacterId() const override { return characterId; }

        uint16_t characterId;
        std::vector<unsigned char> imageData;
    };
}
