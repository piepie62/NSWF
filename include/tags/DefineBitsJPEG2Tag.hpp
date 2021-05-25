#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace unSWF::tags
{
    class DefineBitsJPEG2Tag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineBitsJPEG2Tag(SwfStreamReader& reader) : SwfTag(reader)
        {
            characterId = reader.readU16();
            imageData   = reader.readBytes(this->dataSize() - 2);
        }

        int getCharacterId() const override { return characterId; }

    private:
        int characterId;
        std::vector<unsigned char> imageData;
    };
}
