#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include <vector>

namespace NSWF::tags
{
    class DefineBinaryDataTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineBinaryDataTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::DefineBinaryData, size)
        {
            characterId = reader.readU16();
            // reserved
            reader.readU32();
            data = reader.readBytes(size - 6);
        }

        uint16_t getCharacterId() const override { return characterId; }

        uint16_t characterId;
        std::vector<unsigned char> data;
    };
}
