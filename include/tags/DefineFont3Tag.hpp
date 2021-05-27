#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/KERNINGRECORD.hpp"
#include "types/RECT.hpp"
#include "types/SHAPE.hpp"
#include <cstdint>

namespace NSWF::tags
{
    class DefineFont3Tag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineFont3Tag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::DefineFont3, size)
        {
            fontId           = reader.readU16();
            bool hasLayout   = reader.readFlag();
            shiftJIS         = reader.readFlag();
            smallText        = reader.readFlag();
            ANSI             = reader.readFlag();
            bool wideOffsets = reader.readFlag();
            bool wideCodes   = reader.readFlag();
            italic           = reader.readFlag();
            bold             = reader.readFlag();
            language         = reader.readU8();
            fontName         = reader.readString(reader.readU8());
            int numGlyphs    = reader.readU16();

            offsetTable.reserve(numGlyphs);
            for (int i = 0; i < numGlyphs; i++)
            {
                offsetTable.emplace_back(wideOffsets ? reader.readU32() : reader.readU16());
            }

            // Code table offset? Not sure what this could be useful for
            if (wideOffsets)
            {
                reader.readU32();
            }
            else
            {
                reader.readU16();
            }

            shapeTable.reserve(numGlyphs);
            for (int i = 0; i < numGlyphs; i++)
            {
                shapeTable.emplace_back(reader.readShape(2));
            }

            codeTable.reserve(numGlyphs);
            for (int i = 0; i < numGlyphs; i++)
            {
                codeTable.emplace_back(reader.readU16());
            }

            if (hasLayout)
            {
                ascent  = reader.readU16();
                descent = reader.readU16();
                leading = reader.readS16();

                advanceTable = std::vector<int16_t>(numGlyphs);
                for (int i = 0; i < numGlyphs; i++)
                {
                    advanceTable->emplace_back(reader.readS16());
                }

                boundsTable = std::vector<RECT>(numGlyphs);
                for (int i = 0; i < numGlyphs; i++)
                {
                    boundsTable->emplace_back(reader.readRect());
                }

                int kerningCount = reader.readU16();
                kerningTable     = std::vector<KERNINGRECORD>(kerningCount);
                for (int i = 0; i < kerningCount; i++)
                {
                    kerningTable->emplace_back(reader.readKerningRecord(wideCodes));
                }
            }
        }

        uint16_t getCharacterId() const override { return fontId; }

        uint16_t fontId;
        bool shiftJIS;
        bool smallText;
        bool ANSI;
        bool italic;
        bool bold;
        uint8_t language;
        std::string fontName;
        std::vector<uint32_t> offsetTable;
        std::vector<SHAPE> shapeTable;
        std::vector<uint16_t> codeTable;
        std::optional<uint16_t> ascent;
        std::optional<uint16_t> descent;
        std::optional<int16_t> leading;
        std::optional<std::vector<int16_t>> advanceTable;
        std::optional<std::vector<RECT>> boundsTable;
        std::optional<std::vector<KERNINGRECORD>> kerningTable;
    };
}
