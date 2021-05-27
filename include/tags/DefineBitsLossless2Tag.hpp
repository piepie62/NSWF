#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/ALPHABITMAPDATA.hpp"
#include "types/ARGB.hpp"
#include "types/COLORMAPDATA.hpp"
#include "types/RGBA.hpp"
#include <stdexcept>
#include <variant>

namespace unSWF::tags
{
    class DefineBitsLossless2Tag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineBitsLossless2Tag(SwfStreamReader& reader) : SwfTag(reader)
        {
            characterId        = reader.readU16();
            pixelFormat        = PixelFormat(reader.readU8());
            width              = reader.readU16();
            height             = reader.readU16();
            int colorTableSize = 0;
            if (pixelFormat == PixelFormat::ColorMap8)
            {
                colorTableSize = reader.readU8();
            }

            std::vector<unsigned char> rawData = reader.decompressZlibFromStream(
                pixelFormat == PixelFormat::ColorMap8 ? this->dataSize() - 8
                                                      : this->dataSize() - 7);

            SwfStreamReader bitmapReader{rawData.data()};
            switch (pixelFormat)
            {
                case PixelFormat::ColorMap8:
                {
                    int alignedWidth = width;
                    if (alignedWidth % 4 != 0)
                    {
                        alignedWidth += 4 - (alignedWidth % 4);
                    }

                    bitmapData = COLORMAPDATA<RGBA>{std::vector<RGBA>(colorTableSize + 1),
                        std::vector<uint8_t>(alignedWidth * height)};
                    COLORMAPDATA<RGBA>& colorMap = std::get<COLORMAPDATA<RGBA>>(bitmapData);

                    for (auto& color : colorMap.colorTable)
                    {
                        color = bitmapReader.readRGBA();
                    }

                    bitmapReader.readBytes(colorMap.pixelData.data(), colorMap.pixelData.size());
                }
                break;
                case PixelFormat::ARGB8888:
                {
                    bitmapData              = ALPHABITMAPDATA{std::vector<ARGB>(width * height)};
                    ALPHABITMAPDATA mapData = std::get<ALPHABITMAPDATA>(bitmapData);

                    for (auto& pixel : mapData.pixels)
                    {
                        pixel = bitmapReader.readARGB();
                    }
                }
                break;
                default:
                    throw std::invalid_argument("Invalid pixel format");
            }
        }

        uint16_t getCharacterId() const override { return characterId; }

        uint16_t characterId;
        enum class PixelFormat
        {
            ColorMap8 = 3,
            ARGB8888  = 5
        } pixelFormat;
        uint16_t width;
        uint16_t height;
        std::variant<COLORMAPDATA<RGBA>, ALPHABITMAPDATA> bitmapData;
    };
}
