#pragma once

#include "tags/abstract/SwfTag.hpp"
#include "types/CLIPACTIONRECORD.hpp"

namespace NSWF::tags
{
    class PlaceObject2Tag : public SwfTag
    {
    public:
        PlaceObject2Tag(SwfStreamReader& _reader, size_t size)
            : SwfTag(SwfTagType::PlaceObject2, size)
        {
            SwfStreamReader reader = _reader.subStream(size, true);

            bool hasClipActions    = reader.readFlag();
            bool hasClipDepth      = reader.readFlag();
            bool hasName           = reader.readFlag();
            bool hasRatio          = reader.readFlag();
            bool hasColorTransform = reader.readFlag();
            bool hasMatrix         = reader.readFlag();
            bool hasCharacter      = reader.readFlag();
            bool hasMove           = reader.readFlag();
            depth                  = reader.readU16();
            if (hasCharacter)
            {
                characterId = reader.readU16();
            }
            if (hasMatrix)
            {
                matrix = reader.readMatrix();
            }
            if (hasColorTransform)
            {
                colorTransform = reader.readCxform();
            }
            if (hasRatio)
            {
                ratio = reader.readU16();
            }
            if (hasName)
            {
                name = reader.readNTString();
            }
            if (hasClipDepth)
            {
                clipDepth = reader.readU16();
            }
            if (hasClipActions)
            {
                // reserved
                reader.readU16();
                // Unnecessary
                reader.readClipEventFlags();
                clipActions = std::vector<CLIPACTIONRECORD>();
                while (reader.readU32() != 0)
                {
                    reader.backtrack(4);
                    clipActions->emplace_back(reader.readClipActionRecord());
                }
            }
        }

        uint16_t depth;
        std::optional<uint16_t> characterId;
        std::optional<MATRIX> matrix;
        std::optional<CXFORM> colorTransform;
        std::optional<uint16_t> ratio;
        std::optional<std::string> name;
        std::optional<uint16_t> clipDepth;
        std::optional<std::vector<CLIPACTIONRECORD>> clipActions;
    };
}
