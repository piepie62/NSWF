#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/BITMAPDATA15.hpp"
#include "types/BITMAPDATA24.hpp"
#include "types/COLORMAPDATA.hpp"
#include <stdexcept>
#include <variant>

namespace unSWF::tags
{
    class DefineBitsLosslessTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineBitsLosslessTag(SwfStreamReader& reader) : SwfTag(reader)
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

                    bitmapData = COLORMAPDATA<RGB>{std::vector<RGB>(colorTableSize + 1),
                        std::vector<uint8_t>(alignedWidth * height)};
                    COLORMAPDATA<RGB>& colorMap = std::get<COLORMAPDATA<RGB>>(bitmapData);

                    for (auto& color : colorMap.colorTable)
                    {
                        color = bitmapReader.readRGB();
                    }

                    bitmapReader.readBytes(colorMap.pixelData.data(), colorMap.pixelData.size());
                }
                break;
                case PixelFormat::RGB555:
                {
                    int alignedWidth = width;
                    if (alignedWidth % 2 != 0)
                    {
                        alignedWidth += 2 - (alignedWidth % 4);
                    }

                    bitmapData           = BITMAPDATA15{std::vector<PIX15>(alignedWidth * height)};
                    BITMAPDATA15 mapData = std::get<BITMAPDATA15>(bitmapData);

                    for (auto& pixel : mapData.pixels)
                    {
                        pixel = bitmapReader.readPIX15();
                    }
                }
                break;
                case PixelFormat::RGB888:
                {
                    bitmapData           = BITMAPDATA24{std::vector<PIX24>(width * height)};
                    BITMAPDATA24 mapData = std::get<BITMAPDATA24>(bitmapData);

                    for (auto& pixel : mapData.pixels)
                    {
                        pixel = bitmapReader.readPIX24();
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
            RGB555    = 4,
            RGB888    = 5
        } pixelFormat;
        uint16_t width;
        uint16_t height;
        std::variant<COLORMAPDATA<RGB>, BITMAPDATA15, BITMAPDATA24> bitmapData;
    };
}
