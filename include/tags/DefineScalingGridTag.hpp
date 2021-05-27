#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class DefineScalingGridTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineScalingGridTag(SwfStreamReader& reader) : SwfTag(reader)
        {
            characterId = reader.readU16();
            splitter    = reader.readRect();
        }

        uint16_t getCharacterId() const override { return characterId; }

        uint16_t characterId;
        RECT splitter;
    };
}
