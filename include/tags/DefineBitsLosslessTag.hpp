#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace unSWF::tags
{
    class DefineBitsLosslessTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineBitsLosslessTag(SwfStreamReader& reader) : SwfTag(reader)
        {
            characterId = reader.readU16();
            pixelFormat = PixelFormat(reader.readU8());
            width       = reader.readU16();
            height      = reader.readU16();
            if (pixelFormat == PixelFormat::ColorMap8)
            {
                colorTableSize = reader.readU8();
            }
            else
            {
                colorTableSize = 0;
            }

            zlibBmpData =
                reader.readBytes(pixelFormat == PixelFormat::ColorMap8 ? this->dataSize() - 8
                                                                       : this->dataSize() - 7);
        }

        int getCharacterId() const override { return characterId; }

    private:
        int characterId;
        enum class PixelFormat
        {
            ColorMap8 = 3,
            RGB555    = 4,
            RGB888    = 5
        } pixelFormat;
        int width;
        int height;
        int colorTableSize;
        std::vector<unsigned char> zlibBmpData;
    };
}
