#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class CSMTextSettingsTag : public SwfTag, public CharacterIdTag
    {
    public:
        CSMTextSettingsTag(SwfStreamReader& reader) : SwfTag(reader)
        {
            textID       = reader.readU16();
            useFlashType = reader.readUnsignedBits(2);
            gridFit      = reader.readUnsignedBits(3);
            // reserved
            reader.readUnsignedBits(3);
            thickness = reader.readFloat32();
            sharpness = reader.readFloat32();
            // reserved
            reader.readU8();
        }

        uint16_t getCharacterId() const override { return textID; }

        uint16_t textID;
        uint8_t useFlashType;
        uint8_t gridFit;
        float thickness;
        float sharpness;
    };
}
