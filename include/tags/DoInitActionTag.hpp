#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/ACTIONRECORD.hpp"

namespace NSWF::tags
{
    class DoInitActionTag : public SwfTag, public CharacterIdTag
    {
    public:
        DoInitActionTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::DoInitAction, size)
        {
            spriteId = reader.readU16();

            while (reader.readU8() != 0)
            {
                reader.backtrack();
                actions.emplace_back(reader.readActionRecord());
            }
        }

        uint16_t getCharacterId() const override { return spriteId; }

        uint16_t spriteId;
        std::vector<ACTIONRECORD> actions;
    };
}
