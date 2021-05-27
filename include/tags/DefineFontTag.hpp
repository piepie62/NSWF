#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/SHAPE.hpp"

namespace unSWF::tags
{
    class DefineFontTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineFontTag(SwfStreamReader& reader) : SwfTag(reader)
        {
            fontId        = reader.readU16();
            int numGlyphs = reader.readU16() / 2;
            reader.backtrack(2);
            offsetTable.reserve(numGlyphs);
            shapeTable.reserve(numGlyphs);

            for (int i = 0; i < numGlyphs; i++)
            {
                offsetTable.emplace_back(reader.readU16());
            }
            for (int i = 0; i < numGlyphs; i++)
            {
                shapeTable.emplace_back(reader.readShape(1));
            }
        }

        uint16_t fontId;
        std::vector<uint16_t> offsetTable;
        std::vector<SHAPE> shapeTable;
    };
}
