#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/RECT.hpp"
#include "types/SHAPEWITHSTYLE.hpp"
#include <cstdint>

namespace NSWF::tags
{
    class DefineShape3Tag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineShape3Tag(SwfStreamReader& reader) : SwfTag(reader)
        {
            shapeId     = reader.readU16();
            shapeBounds = reader.readRect();
            shape       = reader.readShapeWithStyle(3);
        }

        uint16_t getCharacterId() const override { return shapeId; }

        uint16_t shapeId;
        RECT shapeBounds;
        SHAPEWITHSTYLE shape;
    };
}
