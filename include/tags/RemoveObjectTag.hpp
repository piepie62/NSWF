#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class RemoveObjectTag : public SwfTag, public CharacterIdTag
    {
    public:
        RemoveObjectTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::RemoveObject, size)
        {
            characterId = reader.readU16();
            depth       = reader.readU16();
        }

        uint16_t getCharacterId() const override { return characterId; }

        uint16_t characterId;
        uint16_t depth;
    };
}
