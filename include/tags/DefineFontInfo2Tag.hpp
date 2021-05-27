#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include <cstdint>

namespace unSWF::tags
{
    class DefineFontInfo2Tag : public SwfTag, CharacterIdTag
    {
    public:
        DefineFontInfo2Tag(SwfStreamReader& reader) : SwfTag(reader)
        {
            fontId   = reader.readU16();
            fontName = reader.readString(reader.readU8());
            // reserved
            reader.readUnsignedBits(2);
            smallText = (bool)reader.readUnsignedBits(1);
            shiftJIS  = (bool)reader.readUnsignedBits(1);
            ANSI      = (bool)reader.readUnsignedBits(1);
            italic    = (bool)reader.readUnsignedBits(1);
            bold      = (bool)reader.readUnsignedBits(1);

            bool wideCharCodes = (bool)reader.readUnsignedBits(1);

            language = reader.readU8();

            size_t nChars = this->dataSize() - 5 - fontName.size();

            if (wideCharCodes)
            {
                nChars /= 2;
            }

            codeTable.reserve(nChars);

            while (nChars > 0)
            {
                codeTable.emplace_back(wideCharCodes ? reader.readU16() : reader.readU8());
            }
        }

        uint16_t getCharacterId() const override { return fontId; }

        uint16_t fontId;
        std::string fontName;
        bool smallText;
        bool shiftJIS;
        bool ANSI;
        bool italic;
        bool bold;
        uint8_t language;
        std::vector<uint16_t> codeTable;
    };
}