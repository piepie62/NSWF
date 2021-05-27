#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/MORPHFILLSTYLE.hpp"
#include "types/MORPHLINESTYLE.hpp"
#include "types/RECT.hpp"
#include <cstdint>
#include <vector>

namespace NSWF::tags
{
    class DefineMorphShapeTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineMorphShapeTag(SwfStreamReader& reader) : SwfTag(reader)
        {
            characterId = reader.readU16();
            startBounds = reader.readRect();
            endBounds   = reader.readRect();
            // Offset to endEdges
            reader.readU32();
            fillStyles = reader.readMorphFillStyleArray();
            lineStyles = reader.readMorphLineStyleArray();
            startEdges = reader.readShape(1);
            endEdges   = reader.readShape(1);
        }

        uint16_t getCharacterId() const override { return characterId; }

        uint16_t characterId;
        RECT startBounds;
        RECT endBounds;
        std::vector<MORPHFILLSTYLE> fillStyles;
        std::vector<MORPHLINESTYLE> lineStyles;
        SHAPE startEdges;
        SHAPE endEdges;
    };
}
