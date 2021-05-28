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
    class DefineMorphShape2Tag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineMorphShape2Tag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::DefineMorphShape2, size)
        {
            characterId     = reader.readU16();
            startBounds     = reader.readRect();
            endBounds       = reader.readRect();
            startEdgeBounds = reader.readRect();
            endEdgeBounds   = reader.readRect();
            // reserved
            reader.readUnsignedBits(6);
            usesNonScalingStrokes = reader.readFlag();
            usesScalingStrokes    = reader.readFlag();
            // offset to endEdges
            reader.readU32();
            fillStyles = reader.readMorphFillStyleArray();
            lineStyles = reader.readMorphLineStyle2Array();
            startEdges = reader.readShape(2);
            endEdges   = reader.readShape(2);
        }

        uint16_t getCharacterId() const override { return characterId; }

        uint16_t characterId;
        RECT startBounds;
        RECT endBounds;
        RECT startEdgeBounds;
        RECT endEdgeBounds;
        bool usesNonScalingStrokes;
        bool usesScalingStrokes;
        std::vector<MORPHFILLSTYLE> fillStyles;
        std::vector<MORPHLINESTYLE2> lineStyles;
        SHAPE startEdges;
        SHAPE endEdges;
    };
}
