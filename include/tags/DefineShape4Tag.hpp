#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/RECT.hpp"
#include "types/SHAPEWITHSTYLE.hpp"
#include <cstdint>

namespace NSWF::tags
{
    class DefineShape4Tag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineShape4Tag(SwfStreamReader& reader) : SwfTag(reader)
        {
            shapeId     = reader.readU16();
            shapeBounds = reader.readRect();
            edgeBounds  = reader.readRect();
            // reserved
            reader.readUnsignedBits(5);
            usesFillWindingRule   = reader.readFlag();
            usesNonScalingStrokes = reader.readFlag();
            usesScalingStrokes    = reader.readFlag();
            shape                 = reader.readShapeWithStyle(4);
        }

        uint16_t getCharacterId() const override { return shapeId; }

        uint16_t shapeId;
        RECT shapeBounds;
        RECT edgeBounds;
        bool usesFillWindingRule;
        bool usesNonScalingStrokes;
        bool usesScalingStrokes;
        SHAPEWITHSTYLE shape;
    };
}
