#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/ZONERECORD.hpp"
#include <cassert>
#include <cstdint>
#include <vector>

namespace unSWF::tags
{
    class DefineFontAlignZonesTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineFontAlignZonesTag(SwfStreamReader& reader) : SwfTag(reader)
        {
            fontId    = reader.readU16();
            tableHint = CSMTableHint(reader.readUnsignedBits(2));
            // reserved
            reader.readUnsignedBits(6);
            // I don't get where I'm supposed to get glyphCount from, so... there are only ever
            // supposed to be 2 ZoneData entries, making the size of ZoneRecord predictable.
            // I hate it here
            int glyphCount = (this->dataSize() - 3) / 10;

            zoneTable.reserve(glyphCount);
            for (int i = 0; i < glyphCount; i++)
            {
                zoneTable.emplace_back(reader.readZoneRecord());
                assert(zoneTable.back().zoneData.size() == 2);
            }
        }

        uint16_t getCharacterId() const override { return fontId; }

        uint16_t fontId;

        enum class CSMTableHint
        {
            Thin,
            Medium,
            Thick
        } tableHint;

        std::vector<ZONERECORD> zoneTable;
    };
}
