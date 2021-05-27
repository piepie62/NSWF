#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/BUTTONCONDACTION.hpp"
#include "types/BUTTONRECORD.hpp"
#include <vector>

namespace NSWF::tags
{
    class DefineButton2Tag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineButton2Tag(SwfStreamReader& reader) : SwfTag(reader)
        {
            buttonId = reader.readU16();
            // reserved
            reader.readUnsignedBits(7);
            trackAsMenu           = (bool)reader.readUnsignedBits(1);
            uint16_t actionOffset = reader.readU16();
            while (reader.readU8() != 0)
            {
                reader.backtrack();
                characters.emplace_back(reader.readButtonRecord());
            }

            if (actionOffset != 0)
            {
                size_t leftoverSize = dataSize() - 3 - actionOffset;

                while (leftoverSize != 0)
                {
                    actions.emplace_back(reader.readButtonCondAction());
                    leftoverSize -= actions.back().size;
                }
            }
        }

        uint16_t getCharacterId() const override { return buttonId; }

        uint16_t buttonId;
        bool trackAsMenu;
        std::vector<BUTTONRECORD> characters;
        std::vector<BUTTONCONDACTION> actions;
    };
}
