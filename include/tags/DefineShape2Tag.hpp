#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/RECT.hpp"
#include "types/SHAPEWITHSTYLE.hpp"
#include <cstdint>

namespace NSWF::tags
{
    class DefineShape2Tag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineShape2Tag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::DefineShape2, size)
        {
            shapeId     = reader.readU16();
            shapeBounds = reader.readRect();
            shape       = reader.readShapeWithStyle(2);
        }

        uint16_t getCharacterId() const override { return shapeId; }

        uint16_t shapeId;
        RECT shapeBounds;
        SHAPEWITHSTYLE shape;
    };
}
