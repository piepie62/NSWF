#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class FreeCharacterTag : public SwfTag, public CharacterIdTag
    {
    public:
        FreeCharacterTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::FreeCharacter, size)
        {
            characterId = reader.readU16();
        }

        uint16_t getCharacterId() const override { return characterId; }

        uint16_t characterId;
    };
}
