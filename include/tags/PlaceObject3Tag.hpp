#pragma once

#include "tags/abstract/SwfTag.hpp"
#include "types/CLIPACTIONRECORD.hpp"

namespace NSWF::tags
{
    class PlaceObject3Tag : public SwfTag
    {
    public:
        enum class BlendMode
        {
            Normal0,
            Normal,
            Layer,
            Multiply,
            Screen,
            Lighten,
            Darken,
            Difference,
            Add,
            Subtract,
            Invert,
            Alpha,
            Erase,
            Overlay,
            Hardlight
        };

        PlaceObject3Tag(SwfStreamReader& _reader, size_t size)
            : SwfTag(SwfTagType::PlaceObject3, size)
        {
            SwfStreamReader reader = _reader.subStream(size, true);

            bool hasClipActions    = reader.readFlag();
            bool hasClipDepth      = reader.readFlag();
            bool hasName           = reader.readFlag();
            bool hasRatio          = reader.readFlag();
            bool hasColorTransform = reader.readFlag();
            bool hasMatrix         = reader.readFlag();
            bool hasCharacter      = reader.readFlag();
            // hasMove, unused
            reader.readFlag();
            // reserved
            reader.readFlag();
            bool opaqueBackground = reader.readFlag();
            bool hasVisible       = reader.readFlag();
            bool hasImage         = reader.readFlag();
            bool hasClassName     = reader.readFlag();
            bool hasCacheAsBitmap = reader.readFlag();
            bool hasBlendMode     = reader.readFlag();
            bool hasFilterList    = reader.readFlag();

            depth = reader.readU16();
            if (hasClassName)
            {
                className = reader.readNTString();
            }
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
                colorTransform = reader.readCxformWithAlpha();
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
            if (hasFilterList)
            {
                surfaceFilters = reader.readFilterList();
            }
            if (hasBlendMode)
            {
                blendMode = BlendMode(reader.readU8());
            }
            if (hasCacheAsBitmap)
            {
                cacheAsBitmap = (bool)reader.readU8();
            }
            if (hasVisible)
            {
                visible = (bool)reader.readU8();
            }
            if (opaqueBackground)
            {
                bgColor = reader.readRGBA();
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
        std::optional<std::string> className;
        std::optional<uint16_t> characterId;
        std::optional<MATRIX> matrix;
        std::optional<CXFORMWITHALPHA> colorTransform;
        std::optional<uint16_t> ratio;
        std::optional<std::string> name;
        std::optional<uint16_t> clipDepth;
        std::optional<std::vector<FILTER>> surfaceFilters;
        std::optional<BlendMode> blendMode;
        std::optional<bool> cacheAsBitmap;
        std::optional<bool> visible;
        std::optional<RGBA> bgColor;
        std::optional<std::vector<CLIPACTIONRECORD>> clipActions;
    };
}
