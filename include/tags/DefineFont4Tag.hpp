#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include <cstdint>

namespace NSWF::tags
{
    class DefineFont4Tag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineFont4Tag(SwfStreamReader& reader) : SwfTag(reader)
        {
            fontId = reader.readU16();
            // Reserved
            reader.readUnsignedBits(5);
            bool hasFontData = (bool)reader.readUnsignedBits(1);
            italic           = (bool)reader.readUnsignedBits(1);
            bold             = (bool)reader.readUnsignedBits(1);
            fontName         = reader.readNTString();
            if (hasFontData)
            {
                fontData = reader.readBytes(this->dataSize() - fontName.size() - 1 - 3);
            }
        }

        uint16_t getCharacterId() const override { return fontId; }

        uint16_t fontId;
        bool italic;
        bool bold;
        std::string fontName;
        std::optional<std::vector<unsigned char>> fontData;
    }
}
