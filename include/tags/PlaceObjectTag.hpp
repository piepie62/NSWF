#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class PlaceObjectTag : public SwfTag, public CharacterIdTag
    {
    public:
        PlaceObjectTag(SwfStreamReader& _reader, size_t size)
            : SwfTag(SwfTagType::PlaceObject, size)
        {
            SwfStreamReader reader = _reader.subStream(size, true);
            characterId            = reader.readU16();
            depth                  = reader.readU16();
            matrix                 = reader.readMatrix();
            if (!reader.finishedInLessThanOneByte())
            {
                colorTransform = reader.readCxform();
            }
        }

        uint16_t getCharacterId() const override { return characterId; }

        uint16_t characterId;
        uint16_t depth;
        MATRIX matrix;
        std::optional<CXFORM> colorTransform;
    };
}
