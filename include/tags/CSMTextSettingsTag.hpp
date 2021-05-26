#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace unSWF::tags
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
            thickness = reader.readF32();
            sharpness = reader.readF32();
            // reserved
            reader.readU8();
        }

        uint16_t getCharacterId() const override { return textID; }

    private:
        uint16_t textID;
        uint8_t useFlashType;
        uint8_t gridFit;
        float thickness;
        float sharpness;
    };
}
