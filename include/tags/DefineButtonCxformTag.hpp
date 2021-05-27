#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/CXFORM.hpp"
#include <vector>

namespace NSWF::tags
{
    class DefineButtonCxformTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineButtonCxformTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::DefineButtonCxform, size)
        {
            buttonId       = reader.readU16();
            colorTransform = reader.readCxform();
        }

        uint16_t getCharacterId() const override { return buttonId; }

        uint16_t buttonId;
        CXFORM colorTransform;
    };
}
