#pragma once

#include "types/ACTIONRECORD.hpp"
#include "types/ARGB.hpp"
#include "types/BUTTONRECORD.hpp"
#include "types/BUTTONRECORD2.hpp"
#include "types/CXFORM.hpp"
#include "types/CXFORMWITHALPHA.hpp"
#include "types/FILTER.hpp"
#include "types/FILTERLIST.hpp"
#include "types/MATRIX.hpp"
#include "types/PIX15.hpp"
#include "types/PIX24.hpp"
#include "types/RECT.hpp"
#include "types/RGB.hpp"
#include "types/RGBA.hpp"
#include <cassert>
#include <climits>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

namespace unSWF
{
    class SwfStreamReader
    {
    public:
        static_assert(CHAR_BIT == 8);

        static constexpr size_t DECOMPRESS_BLOCK = 1024;

        // NON-OWNING pointer to the data
        SwfStreamReader(const unsigned char* data)
            : mData(data), mCurrentByte(0), mBitsLeft(CHAR_BIT)
        {
        }

        uintmax_t readUnsignedBits(size_t bits)
        {
            assert(bits <= sizeof(uintmax_t) * CHAR_BIT);

            uintmax_t ret = 0;
            while (bits >= mBitsLeft)
            {
                ret <<= mBitsLeft;
                ret |= mData[mCurrentByte++] & (UCHAR_MAX >> (CHAR_BIT - mBitsLeft));

                mBitsLeft = CHAR_BIT;
            }

            if (bits > 0)
            {
                ret <<= bits;
                ret |=
                    (mData[mCurrentByte] >> (CHAR_BIT - bits)) & (UCHAR_MAX >> (CHAR_BIT - bits));
                mBitsLeft -= bits;
            }

            return ret;
        }

        intmax_t readSignedBits(size_t bits)
        {
            uintmax_t ret = readUnsignedBits(bits);

            if (ret & (1 << (bits - 1)))
            {
                ret |= UINTMAX_MAX << bits;
            }

            return ret;
        }

        void alignToByte()
        {
            if (mBitsLeft != CHAR_BIT)
            {
                mCurrentByte++;
                mBitsLeft = CHAR_BIT;
            }
        }

        uint8_t readU8()
        {
            alignToByte();
            return mData[mCurrentByte++];
        }
        int8_t readS8() { return readU8(); }

        uint16_t readU16()
        {
            alignToByte();
            uint16_t ret = uint16_t(mData[mCurrentByte++]) << 8;
            ret |= mData[mCurrentByte++];
            return ret;
        }
        int16_t readS16() { return readU16(); }

        uint32_t readU32()
        {
            alignToByte();
            uint32_t ret = uint32_t(mData[mCurrentByte++]) << 24;
            ret |= uint32_t(mData[mCurrentByte++]) << 16;
            ret |= uint32_t(mData[mCurrentByte++]) << 8;
            ret |= mData[mCurrentByte++];

            return ret;
        }
        int32_t readS32() { return readS32(); }

        // If necessary, will change to actual 16-bit floats
        uint16_t readF16() { return readU16(); }

        float readF32()
        {
            uint32_t read = readU32();
            float ret;
            std::memcpy(&ret, &read, sizeof(ret));

            return ret;
        }

        double readF64()
        {
            uint64_t read = (uint64_t(readU32()) << 32) | readU32();
            double ret;
            std::memcpy(&ret, &read, sizeof(ret));

            return ret;
        }

        std::vector<unsigned char> readBytes(size_t num)
        {
            alignToByte();
            std::vector<unsigned char> ret(num);
            readBytes(ret.data(), num);

            return ret;
        }

        void readBytes(unsigned char* data, size_t num)
        {
            alignToByte();
            std::memcpy(data, mData, num);
            mCurrentByte += num;
        }

        RECT readRect()
        {
            alignToByte();
            size_t bits = readUnsignedBits(5);

            return {readSignedBits(bits), readSignedBits(bits), readSignedBits(bits),
                readSignedBits(bits)};
        }

        RGB readRGB() { return {readU8(), readU8(), readU8()}; }
        RGBA readRGBA() { return {readU8(), readU8(), readU8(), readU8()}; }
        ARGB readARGB() { return {readU8(), readU8(), readU8(), readU8()}; }
        PIX15 readPIX15()
        {
            alignToByte();
            return {uint8_t(readUnsignedBits(1)), uint8_t(readUnsignedBits(5)),
                uint8_t(readUnsignedBits(5)), uint8_t(readUnsignedBits(5))};
        }
        PIX24 readPIX24() { return {readU8(), readU8(), readU8(), readU8()}; }

        MATRIX readMatrix()
        {
            alignToByte();
            MATRIX ret{};
            ret.hasScale = (bool)readUnsignedBits(1);
            if (ret.hasScale)
            {
                int nScaleBits = readUnsignedBits(5);
                ret.scaleX     = readUnsignedBits(nScaleBits);
                ret.scaleY     = readUnsignedBits(nScaleBits);
            }
            ret.hasRotate = (bool)readUnsignedBits(1);
            if (ret.hasRotate)
            {
                int nRotateBits = readUnsignedBits(5);
                ret.rotateSkew0 = readUnsignedBits(nRotateBits);
                ret.rotateSkew1 = readUnsignedBits(nRotateBits);
            }
            int nTranslateBits = readUnsignedBits(5);
            ret.translateX     = readSignedBits(nTranslateBits);
            ret.translateY     = readSignedBits(nTranslateBits);

            return ret;
        }

        CXFORM readCxform()
        {
            alignToByte();
            CXFORM ret{};
            ret.hasAddTerms  = readUnsignedBits(1);
            ret.hasMultTerms = readUnsignedBits(1);
            int nBits        = readUnsignedBits(4);
            if (ret.hasMultTerms)
            {
                ret.redMultTerm   = readSignedBits(nBits);
                ret.blueMultTerm  = readSignedBits(nBits);
                ret.greenMultTerm = readSignedBits(nBits);
            }
            if (ret.hasAddTerms)
            {
                ret.redAddTerm   = readSignedBits(nBits);
                ret.blueAddTerm  = readSignedBits(nBits);
                ret.greenAddTerm = readSignedBits(nBits);
            }

            return ret;
        }

        CXFORMWITHALPHA readCxformWithAlpha()
        {
            alignToByte();
            CXFORMWITHALPHA ret{};
            ret.hasAddTerms  = readUnsignedBits(1);
            ret.hasMultTerms = readUnsignedBits(1);
            int nBits        = readUnsignedBits(4);
            if (ret.hasMultTerms)
            {
                ret.redMultTerm   = readSignedBits(nBits);
                ret.blueMultTerm  = readSignedBits(nBits);
                ret.greenMultTerm = readSignedBits(nBits);
                ret.alphaMultTerm = readSignedBits(nBits);
            }
            if (ret.hasAddTerms)
            {
                ret.redAddTerm    = readSignedBits(nBits);
                ret.blueAddTerm   = readSignedBits(nBits);
                ret.greenAddTerm  = readSignedBits(nBits);
                ret.alphaMultTerm = readSignedBits(nBits);
            }

            return ret;
        }

        FILTER readFilter()
        {
            alignToByte();
            FILTER::FilterType type = FILTER::FilterType(readU8());
            switch (type)
            {
                case FILTER::Bevel:
                {
                    return {BEVELFILTER{readRGBA(), readRGBA(), readU32(), readU32(), readU32(),
                        readU32(), readU16(), (bool)readUnsignedBits(1), (bool)readUnsignedBits(1),
                        (bool)readUnsignedBits(1), (bool)readUnsignedBits(1)}};
                }
                case FILTER::Blur:
                {
                    return {BLURFILTER{readU32(), readU32(), (int)readUnsignedBits(5)}};
                }
                case FILTER::ColorMatrix:
                {
                    COLORMATRIXFILTER ret;
                    for (auto& color : ret.matrix)
                    {
                        color = readF32();
                    }
                    return {ret};
                }
                case FILTER::Convolution:
                {
                    CONVOLUTIONFILTER ret;
                    ret.matrixX = readU8();
                    ret.matrixY = readU8();
                    ret.divisor = readF32();
                    ret.bias    = readF32();
                    ret.matrix  = std::vector<float>(ret.matrixX * ret.matrixY);
                    for (auto& val : ret.matrix)
                    {
                        val = readF32();
                    }
                    ret.defaultColor = readRGBA();
                    // reserved
                    readUnsignedBits(6);
                    ret.clamp         = readUnsignedBits(1);
                    ret.preserveAlpha = readUnsignedBits(1);
                    return {ret};
                }
                case FILTER::DropShadow:
                {
                    return {DROPSHADOWFILTER{readRGBA(), readU32(), readU32(), readU32(), readU32(),
                        readU16(), (bool)readUnsignedBits(1), (bool)readUnsignedBits(1),
                        (bool)readUnsignedBits(1), (int)readUnsignedBits(5)}};
                }
                case FILTER::Glow:
                {
                    return {GLOWFILTER{readRGBA(), readU32(), readU32(), readU16(),
                        (bool)readUnsignedBits(1), (bool)readUnsignedBits(1),
                        (bool)readUnsignedBits(1), (int)readUnsignedBits(5)}};
                }
                case FILTER::GradientBevel:
                {
                    int numColors = readU8();
                    GRADIENTBEVELFILTER ret{
                        std::vector<RGBA>(numColors), std::vector<unsigned char>(numColors)};
                    for (auto& color : ret.gradientColors)
                    {
                        color = readRGBA();
                    }
                    for (auto& ratio : ret.gradientRatio)
                    {
                        ratio = readU8();
                    }
                    ret.blurX           = readU32();
                    ret.blurY           = readU32();
                    ret.angle           = readU32();
                    ret.distance        = readU32();
                    ret.strength        = readU16();
                    ret.innerShadow     = (bool)readUnsignedBits(1);
                    ret.knockout        = (bool)readUnsignedBits(1);
                    ret.compositeSource = (bool)readUnsignedBits(1);
                    ret.onTop           = (bool)readUnsignedBits(1);
                    ret.passes          = (int)readUnsignedBits(4);

                    return {ret};
                }
                case FILTER::GradientGlow:
                {
                    int numColors = readU8();
                    GRADIENTGLOWFILTER ret{
                        std::vector<RGBA>(numColors), std::vector<unsigned char>(numColors)};
                    for (auto& color : ret.gradientColors)
                    {
                        color = readRGBA();
                    }
                    for (auto& ratio : ret.gradientRatio)
                    {
                        ratio = readU8();
                    }
                    ret.blurX           = readU32();
                    ret.blurY           = readU32();
                    ret.angle           = readU32();
                    ret.distance        = readU32();
                    ret.strength        = readU16();
                    ret.innerShadow     = (bool)readUnsignedBits(1);
                    ret.knockout        = (bool)readUnsignedBits(1);
                    ret.compositeSource = (bool)readUnsignedBits(1);
                    ret.onTop           = (bool)readUnsignedBits(1);
                    ret.passes          = (int)readUnsignedBits(4);

                    return {ret};
                }
                default:
                    throw std::invalid_argument("Unknown filter type");
            }
        }

        FILTERLIST readFilterList()
        {
            int numFilters = readU8();
            FILTERLIST ret{std::vector<FILTER>(numFilters)};
            for (auto& filter : ret.filters)
            {
                filter = readFilter();
            }
            return ret;
        }

        void backtrack(size_t amount = 1)
        {
            if (amount > mCurrentByte)
            {
                mCurrentByte = 0;
            }
            else
            {
                mCurrentByte -= amount;
            }
        }

        BUTTONRECORD readButtonRecord()
        {
            // reserved
            readUnsignedBits(2);
            return {(bool)readUnsignedBits(1), (bool)readUnsignedBits(1), (bool)readUnsignedBits(1),
                (bool)readUnsignedBits(1), (bool)readUnsignedBits(1), (bool)readUnsignedBits(1),
                readU16(), readU16(), readMatrix()};
        }

        BUTTONRECORD2 readButtonRecord2()
        { // reserved
            readUnsignedBits(2);
            BUTTONRECORD2 ret{(bool)readUnsignedBits(1), (bool)readUnsignedBits(1),
                (bool)readUnsignedBits(1), (bool)readUnsignedBits(1), (bool)readUnsignedBits(1),
                (bool)readUnsignedBits(1), readU16(), readU16(), readMatrix(),
                readCxformWithAlpha()};
            if (ret.hasFilterList)
            {
                ret.filters = readFilterList();
            }
            if (ret.hasBlendMode)
            {
                ret.blendmode = BUTTONRECORD2::BlendMode(readU8());
            }

            return ret;
        }

        ACTIONRECORD readActionRecord()
        {
            uint8_t code = readU8();
            if (code & 0x80)
            {
                int length = readU16();
                return ACTIONRECORD{code, readBytes(length)};
            }
            return ACTIONRECORD{code};
        }

        std::vector<unsigned char> decompressZlibFromStream(
            size_t compressedBytes, size_t startingAlloc = 0);

        std::vector<unsigned char> decompressLzmaFromStream(
            size_t compressedBytes, size_t startingAlloc = 0);

    private:
        const unsigned char* mData;
        size_t mCurrentByte;
        int mBitsLeft;
    };
}
