#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/MATRIX.hpp"
#include "types/RECT.hpp"
#include "types/TEXTRECORD.hpp"

namespace NSWF::tags
{
    class DefineText2Tag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineText2Tag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::DefineText, size)
        {
            characterId = reader.readU16();
            textBounds  = reader.readRect();
            textMatrix  = reader.readMatrix();

            int glyphBits   = reader.readU8();
            int advanceBits = reader.readU8();

            while (reader.readU8() != 0)
            {
                reader.backtrack();
                records.emplace_back(reader.readTextRecord(2, glyphBits, advanceBits));
            }
        }

        uint16_t getCharacterId() const override { return characterId; }

        uint16_t characterId;
        RECT textBounds;
        MATRIX textMatrix;
        std::vector<TEXTRECORD> records;
    };
}
