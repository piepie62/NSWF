#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/RECT.hpp"
#include "types/SHAPEWITHSTYLE.hpp"
#include <cstdint>

namespace NSWF::tags
{
    class DefineShapeTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineShapeTag(SwfStreamReader& reader) : SwfTag(reader)
        {
            shapeId     = reader.readU16();
            shapeBounds = reader.readRect();
            shape       = reader.readShapeWithStyle(1);
        }

        uint16_t getCharacterId() const override { return shapeId; }

        uint16_t shapeId;
        RECT shapeBounds;
        SHAPEWITHSTYLE shape;
    };
}
