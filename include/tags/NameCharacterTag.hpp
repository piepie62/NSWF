#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class NameCharacterTag : public SwfTag, public CharacterIdTag
    {
    public:
        NameCharacterTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::NameCharacter, size)
        {
            characterId = reader.readU16();
            name        = reader.readNTString();
        }

        uint16_t getCharacterId() const override { return characterId; }

        uint16_t characterId;
        std::string name;
    };
}
