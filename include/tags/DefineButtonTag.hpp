#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/ACTIONRECORD.hpp"
#include "types/BUTTONRECORD.hpp"
#include <vector>

namespace NSWF::tags
{
    class DefineButtonTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineButtonTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::DefineButton, size)
        {
            buttonId = reader.readU16();
            while (reader.readU8() != 0)
            {
                reader.backtrack();
                characters.emplace_back(reader.readButtonRecord());
            }

            while (reader.readU8() != 0)
            {
                reader.backtrack();
                actions.emplace_back(reader.readActionRecord());
            }
        }

        uint16_t getCharacterId() const override { return buttonId; }

        uint16_t buttonId;
        std::vector<BUTTONRECORD> characters;
        std::vector<ACTIONRECORD> actions;
    };
}
