#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace unSWF::tags
{
    class DefineBitsTag : public SwfTag, public CharacterIdTag
    {
        static constexpr unsigned char ERROR_HEADER[] = {0xFF, 0xD9, 0xFF, 0xD8};

    public:
        DefineBitsTag(SwfStreamReader& reader) : SwfTag(reader)
        {
            characterId = reader.readU16();
            imageData   = reader.readBytes(this->dataSize() - 2);
            if (!memcmp(ERROR_HEADER, imageData.data(), 4))
            {
                imageData.erase(imageData.begin(), imageData.begin() + 4);
            }
        }

        uint16_t getCharacterId() const override { return characterId; }

    private:
        uint16_t characterId;
        std::vector<unsigned char> imageData;
    };
}
