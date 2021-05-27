#pragma once

#include "types/ACTIONRECORD.hpp"
#include "types/ARGB.hpp"
#include "types/BUTTONCONDACTION.hpp"
#include "types/BUTTONRECORD.hpp"
#include "types/BUTTONRECORD2.hpp"
#include "types/CXFORM.hpp"
#include "types/CXFORMWITHALPHA.hpp"
#include "types/FILTER.hpp"
#include "types/FILTERLIST.hpp"
#include "types/KERNINGRECORD.hpp"
#include "types/MATRIX.hpp"
#include "types/MORPHFILLSTYLE.hpp"
#include "types/MORPHGRADIENT.hpp"
#include "types/MORPHGRADRECORD.hpp"
#include "types/MORPHLINESTYLE.hpp"
#include "types/MORPHLINESTYLE2.hpp"
#include "types/PIX15.hpp"
#include "types/PIX24.hpp"
#include "types/RECT.hpp"
#include "types/RGB.hpp"
#include "types/RGBA.hpp"
#include "types/SHAPE.hpp"
#include "types/SHAPERECORD.hpp"
#include "types/SHAPEWITHSTYLE.hpp"
#include "types/SOUNDENVELOPE.hpp"
#include "types/SOUNDINFO.hpp"
#include "types/ZONEDATA.hpp"
#include "types/ZONERECORD.hpp"
#include "types/basic/fixed16.hpp"
#include "types/basic/fixed32.hpp"
#include "types/basic/float16.hpp"
#include <cassert>
#include <climits>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

namespace NSWF
{
    class SwfStreamReader
    {
    public:
        static_assert(CHAR_BIT == 8);
        static_assert(sizeof(float) == 4);
        static_assert(sizeof(double) == 8);

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

        bool readFlag() { return readFlag(); }

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
        float16 readFloat16() { return {readU16()}; }

        float readFloat32()
        {
            alignToByte();
            float ret;
            std::memcpy(&ret, &mData[mCurrentByte], sizeof(ret));
            mCurrentByte += sizeof(ret);

            return ret;
        }

        double readFloat64()
        {
            alignToByte();
            double ret;
            std::memcpy(&ret, &mData[mCurrentByte], sizeof(ret));
            mCurrentByte += sizeof(ret);

            return ret;
        }
        double readDouble() { return readFloat64(); }

        fixed16 readFixed16() { return {readU16()}; }

        fixed32 readFixed32() { return {readU32()}; }

        uint32_t readEncodedU32()
        {
            alignToByte();
            uint32_t ret = readU8();
            if (!(ret & 0x00000080))
            {
                return ret;
            }
            ret = (ret & 0x0000007f) | uint32_t(readU8()) << 7;
            if (!(ret & 0x00004000))
            {
                return ret;
            }
            ret = (ret & 0x00003fff) | uint32_t(readU8()) << 14;
            if (!(ret & 0x00200000))
            {
                return ret;
            }
            ret = (ret & 0x001fffff) | uint32_t(readU8()) << 21;
            if (!(ret & 0x10000000))
            {
                return ret;
            }
            ret = (ret & 0x0fffffff) | uint32_t(readU8()) << 28;
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
            return {uint8_t(readFlag()), uint8_t(readUnsignedBits(5)), uint8_t(readUnsignedBits(5)),
                uint8_t(readUnsignedBits(5))};
        }
        PIX24 readPIX24() { return {readU8(), readU8(), readU8(), readU8()}; }

        MATRIX readMatrix()
        {
            alignToByte();
            MATRIX ret{};
            ret.hasScale = readFlag();
            if (ret.hasScale)
            {
                int nScaleBits = readUnsignedBits(5);
                ret.scaleX     = readUnsignedBits(nScaleBits);
                ret.scaleY     = readUnsignedBits(nScaleBits);
            }
            ret.hasRotate = readFlag();
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
            ret.hasAddTerms  = readFlag();
            ret.hasMultTerms = readFlag();
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
            ret.hasAddTerms  = readFlag();
            ret.hasMultTerms = readFlag();
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
                        readU32(), readU16(), readFlag(), readFlag(), readFlag(), readFlag()}};
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
                        color = readFloat32();
                    }
                    return {ret};
                }
                case FILTER::Convolution:
                {
                    CONVOLUTIONFILTER ret;
                    ret.matrixX = readU8();
                    ret.matrixY = readU8();
                    ret.divisor = readFloat32();
                    ret.bias    = readFloat32();
                    ret.matrix  = std::vector<float>(ret.matrixX * ret.matrixY);
                    for (auto& val : ret.matrix)
                    {
                        val = readFloat32();
                    }
                    ret.defaultColor = readRGBA();
                    // reserved
                    readUnsignedBits(6);
                    ret.clamp         = readFlag();
                    ret.preserveAlpha = readFlag();
                    return {ret};
                }
                case FILTER::DropShadow:
                {
                    return {DROPSHADOWFILTER{readRGBA(), readU32(), readU32(), readU32(), readU32(),
                        readU16(), readFlag(), readFlag(), readFlag(), (int)readUnsignedBits(5)}};
                }
                case FILTER::Glow:
                {
                    return {GLOWFILTER{readRGBA(), readU32(), readU32(), readU16(), readFlag(),
                        readFlag(), readFlag(), (int)readUnsignedBits(5)}};
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
                    ret.blurX           = readFixed32();
                    ret.blurY           = readFixed32();
                    ret.angle           = readFixed32();
                    ret.distance        = readFixed32();
                    ret.strength        = readFixed16();
                    ret.innerShadow     = readFlag();
                    ret.knockout        = readFlag();
                    ret.compositeSource = readFlag();
                    ret.onTop           = readFlag();
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
                    ret.blurX           = readFixed32();
                    ret.blurY           = readFixed32();
                    ret.angle           = readFixed32();
                    ret.distance        = readFixed32();
                    ret.strength        = readFixed16();
                    ret.innerShadow     = readFlag();
                    ret.knockout        = readFlag();
                    ret.compositeSource = readFlag();
                    ret.onTop           = readFlag();
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
            return {readFlag(), readFlag(), readFlag(), readFlag(), readFlag(), readFlag(),
                readU16(), readU16(), readMatrix()};
        }

        BUTTONRECORD2 readButtonRecord2()
        { // reserved
            readUnsignedBits(2);
            BUTTONRECORD2 ret{readFlag(), readFlag(), readFlag(), readFlag(), readFlag(),
                readFlag(), readU16(), readU16(), readMatrix(), readCxformWithAlpha()};
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

        BUTTONCONDACTION readButtonCondAction()
        {
            BUTTONCONDACTION ret{readU16(), readFlag(), readFlag(), readFlag(), readFlag(),
                readFlag(), readFlag(), readFlag(), readFlag(), (uint8_t)readUnsignedBits(7),
                readFlag()};

            while (readU8() != 0)
            {
                backtrack();
                ret.actions.emplace_back(readActionRecord());
            }

            return ret;
        }

        SOUNDENVELOPE readSoundEnvelope() { return SOUNDENVELOPE{readU32(), readU16(), readU16()}; }

        SOUNDINFO readSoundInfo()
        {
            // reserved
            readUnsignedBits(2);
            SOUNDINFO ret{readFlag(), readFlag(), readFlag(), readFlag(), readFlag(), readFlag()};

            if (ret.hasInPoint)
            {
                ret.inPoint = readU32();
            }
            if (ret.hasOutPoint)
            {
                ret.outPoint = readU32();
            }
            if (ret.hasLoops)
            {
                ret.loopCount = readU16();
            }
            if (ret.hasEnvelope)
            {
                ret.envelopeRecords = std::vector<SOUNDENVELOPE>(readU8());
                for (auto& envelope : ret.envelopeRecords)
                {
                    envelope = readSoundEnvelope();
                }
            }

            return ret;
        }

        std::string readNTString()
        {
            alignToByte();
            std::string ret((const char*)mData);
            mCurrentByte += ret.size() + 1;
            return ret;
        }

        std::string readString(size_t chars)
        {
            alignToByte();
            std::string ret((const char*)mData, chars);
            mCurrentByte += chars;
            return ret;
        }

        SHAPERECORD readShapeRecord(int shapeTagNumber, int& fillBits, int& lineBits)
        {
            if (readFlag()) // Is an edge
            {
                if (readFlag()) // is straight
                {
                    int numBits      = (int)readUnsignedBits(4) + 2;
                    bool generalLine = readFlag();
                    if (generalLine)
                    {
                        return SHAPERECORD{
                            STRAIGHTEDGERECORD{readSignedBits(numBits), readSignedBits(numBits)}};
                    }
                    else
                    {
                        if (readFlag()) // is vertical
                        {
                            return SHAPERECORD{
                                STRAIGHTEDGERECORD{std::nullopt, readSignedBits(numBits)}};
                        }
                        else
                        {
                            return SHAPERECORD{STRAIGHTEDGERECORD{readSignedBits(numBits)}};
                        }
                    }
                }
                else
                {
                    int numBits = readUnsignedBits(4) + 2;
                    return SHAPERECORD{CURVEDEDGERECORD{(int32_t)readSignedBits(numBits),
                        (int32_t)readSignedBits(numBits), (int32_t)readSignedBits(numBits),
                        (int32_t)readSignedBits(numBits)}};
                }
            }
            else
            {
                bool stateNewStyles  = readFlag();
                bool stateLineStyle  = readFlag();
                bool stateFillStyle1 = readFlag();
                bool stateFillStyle0 = readFlag();
                bool stateMoveTo     = readFlag();

                if (!stateNewStyles && !stateLineStyle && !stateFillStyle0 && !stateFillStyle1 &&
                    !stateMoveTo)
                {
                    return SHAPERECORD{ENDSHAPERECORD{}};
                }
                else
                {
                    STYLECHANGERECORD ret;
                    if (stateMoveTo)
                    {
                        int bits       = (int)readUnsignedBits(5);
                        ret.moveDeltaX = (int32_t)readSignedBits(bits);
                        ret.moveDeltaY = (int32_t)readSignedBits(bits);
                    }
                    if (stateFillStyle0)
                    {
                        ret.fillStyle0 = (uint16_t)readUnsignedBits(fillBits);
                    }
                    if (stateFillStyle1)
                    {
                        ret.fillStyle1 = (uint16_t)readUnsignedBits(fillBits);
                    }
                    if (stateLineStyle)
                    {
                        ret.lineStyle = (uint16_t)readUnsignedBits(lineBits);
                    }
                    if (stateNewStyles)
                    {
                        ret.fillStyles = readFillStyleArray(shapeTagNumber >= 3);
                        ret.lineStyles = readLineStyleArray(shapeTagNumber);
                        fillBits       = (int)readUnsignedBits(4);
                        lineBits       = (int)readUnsignedBits(4);
                    }

                    return SHAPERECORD{ret};
                }
            }
        }

        FILLSTYLE readFillStyle(bool rgba)
        {
            FILLSTYLE ret{FILLSTYLE::Type(readU8())};
            if (ret.type == FILLSTYLE::Type::Solid)
            {
                ret.color = rgba ? readRGBA() : readRGB();
            }
            else if (ret.type == FILLSTYLE::Type::LinearGradient ||
                     ret.type == FILLSTYLE::Type::RadialGradient)
            {
                ret.gradientMatrix = readMatrix();
                ret.gradient       = readGradient(rgba);
            }
            else if (ret.type == FILLSTYLE::Type::FocalGradient)
            {
                ret.gradientMatrix = readMatrix();
                ret.focalGradient  = readFocalGradient(rgba);
            }
            else if (ret.type == FILLSTYLE::Type::RepeatingBitmap ||
                     ret.type == FILLSTYLE::Type::ClippedBitmap ||
                     ret.type == FILLSTYLE::Type::NonSmoothedRepeatingBitmap ||
                     ret.type == FILLSTYLE::Type::NonSmoothedClippedBitmap)
            {
                ret.bitmapId     = readU16();
                ret.bitmapMatrix = readMatrix();
            }

            return ret;
        }

        std::vector<FILLSTYLE> readFillStyleArray(bool rgba)
        {
            int num = readU8();
            if (num == 0xFF)
            {
                num = readU16();
            }
            std::vector<FILLSTYLE> ret(num);
            for (auto& style : ret)
            {
                style = readFillStyle(rgba);
            }

            return ret;
        }

        GRADIENT readGradient(bool rgba)
        {
            GRADIENT ret{GRADIENT::SpreadMode(readUnsignedBits(2)),
                GRADIENT::InterpolationMode(readUnsignedBits(2))};
            int gradients       = (int)readUnsignedBits(4);
            ret.gradientRecords = std::vector<GRADRECORD>(gradients);
            for (auto& record : ret.gradientRecords)
            {
                record = readGradRecord(rgba);
            }

            return ret;
        }

        FOCALGRADIENT readFocalGradient(bool rgba)
        {
            FOCALGRADIENT ret{FOCALGRADIENT::SpreadMode(readUnsignedBits(2)),
                FOCALGRADIENT::InterpolationMode(readUnsignedBits(2))};
            int gradients       = (int)readUnsignedBits(4);
            ret.gradientRecords = std::vector<GRADRECORD>(gradients);
            for (auto& record : ret.gradientRecords)
            {
                record = readGradRecord(rgba);
            }
            ret.focalPoint = readFixed16();

            return ret;
        }

        GRADRECORD readGradRecord(bool rgba) { return {readU8(), rgba ? readRGBA() : readRGB()}; }

        LINESTYLE readLineStyle(bool rgba) { return {readU16(), rgba ? readRGBA() : readRGB()}; }

        LINESTYLE2 readLineStyle2()
        {
            LINESTYLE2 ret{readU16(), LINESTYLE2::CapStyle(readUnsignedBits(2)),
                LINESTYLE2::JoinStyle(readUnsignedBits(2))};

            bool hasFill              = readFlag();
            ret.noHorizThicknessScale = readFlag();
            ret.noVertThicknessScale  = readFlag();
            ret.pixelHinting          = readFlag();
            // reserved
            readUnsignedBits(5);
            ret.noClose     = readFlag();
            ret.endCapStyle = LINESTYLE2::CapStyle(readUnsignedBits(2));

            if (ret.joinStyle == LINESTYLE2::JoinStyle::Miter)
            {
                ret.miterLimitFactor = readFixed16();
            }
            if (hasFill)
            {
                ret.fill = readFillStyle(true);
            }
            else
            {
                ret.fill = readRGBA();
            }

            return ret;
        }

        std::variant<std::vector<LINESTYLE>, std::vector<LINESTYLE2>> readLineStyleArray(
            int shapeTagNumber)
        {
            int count = readU8();
            if (count == 0xFF)
            {
                count = readU16();
            }
            if (shapeTagNumber == 4)
            {
                std::vector<LINESTYLE2> ret(count);
                for (auto& style : ret)
                {
                    style = readLineStyle2();
                }
                return ret;
            }
            else
            {
                std::vector<LINESTYLE> ret(count);
                for (auto& style : ret)
                {
                    style = readLineStyle(shapeTagNumber == 3);
                }
                return ret;
            }
        }

        SHAPE readShape(int shapeTagNumber)
        {
            int numFillBits = (int)readUnsignedBits(4);
            int numLineBits = (int)readUnsignedBits(4);
            SHAPE ret{{readShapeRecord(shapeTagNumber, numFillBits, numLineBits)}};
            while (ret.records.back().record.index() != 0)
            {
                ret.records.emplace_back(readShapeRecord(shapeTagNumber, numFillBits, numLineBits));
            }

            return ret;
        }

        SHAPEWITHSTYLE readShapeWithStyle(int shapeTagNumber)
        {
            SHAPEWITHSTYLE ret{
                readFillStyleArray(shapeTagNumber >= 3), readLineStyleArray(shapeTagNumber)};

            int numFillBits = (int)readUnsignedBits(4);
            int numLineBits = (int)readUnsignedBits(4);

            ret.records.emplace_back(readShapeRecord(shapeTagNumber, numFillBits, numLineBits));
            while (ret.records.back().record.index() != 0)
            {
                ret.records.emplace_back(readShapeRecord(shapeTagNumber, numFillBits, numLineBits));
            }

            return ret;
        }

        KERNINGRECORD readKerningRecord(bool wideCodes)
        {
            return {wideCodes ? readU16() : (uint16_t)readU8(),
                wideCodes ? readU16() : (uint16_t)readU8(), readS16()};
        }

        ZONEDATA readZoneData() { return {readFloat16(), readFloat16()}; }

        ZONERECORD readZoneRecord()
        {
            int numData = readU8();
            ZONERECORD ret{std::vector<ZONEDATA>(numData)};
            // reserved
            readUnsignedBits(6);
            ret.hasY = readFlag();
            ret.hasX = readFlag();

            return ret;
        }

        std::vector<MORPHLINESTYLE> readMorphLineStyleArray()
        {
            int numStyles = readU8();
            if (numStyles == 0xFF)
            {
                numStyles = readU16();
            }
            std::vector<MORPHLINESTYLE> ret(numStyles);
            for (auto& style : ret)
            {
                style = readMorphLineStyle();
            }

            return ret;
        }

        std::vector<MORPHLINESTYLE2> readMorphLineStyle2Array()
        {
            int numStyles = readU8();
            if (numStyles == 0xFF)
            {
                numStyles = readU16();
            }
            std::vector<MORPHLINESTYLE2> ret(numStyles);
            for (auto& style : ret)
            {
                style = readMorphLineStyle2();
            }

            return ret;
        }

        std::vector<MORPHFILLSTYLE> readMorphFillStyleArray()
        {
            int numStyles = readU8();
            if (numStyles == 0xFF)
            {
                numStyles = readU16();
            }
            std::vector<MORPHFILLSTYLE> ret(numStyles);
            for (auto& style : ret)
            {
                style = readMorphFillStyle();
            }

            return ret;
        }

        MORPHLINESTYLE readMorphLineStyle()
        {
            return {readU16(), readU16(), readRGBA(), readRGBA()};
        }

        MORPHLINESTYLE2 readMorphLineStyle2()
        {
            MORPHLINESTYLE2 ret{readU16(), readU16(),
                MORPHLINESTYLE2::CapStyle(readUnsignedBits(2)),
                MORPHLINESTYLE2::JoinStyle(readUnsignedBits(2))};
            bool hasFill              = readFlag();
            ret.noHorizThicknessScale = readFlag();
            ret.noVertThicknessScale  = readFlag();
            ret.pixelHinting          = readFlag();
            // reserved
            readUnsignedBits(5);
            ret.noClose     = readFlag();
            ret.endCapStyle = MORPHLINESTYLE2::CapStyle(readUnsignedBits(2));
            if (ret.joinStyle == MORPHLINESTYLE2::JoinStyle::Miter)
            {
                ret.miterLimitFactor = readFixed16();
            }
            if (hasFill)
            {
                ret.fill = readMorphFillStyle();
            }
            else
            {
                ret.startColor = readRGBA();
                ret.endColor   = readRGBA();
            }

            return ret;
        }

        MORPHFILLSTYLE readMorphFillStyle()
        {
            MORPHFILLSTYLE ret{MORPHFILLSTYLE::Type(readU8())};
            switch (ret.type)
            {
                case MORPHFILLSTYLE::Type::Solid:
                {
                    ret.startColor = readRGBA();
                    ret.endColor   = readRGBA();
                }
                break;
                case MORPHFILLSTYLE::Type::LinearGradient:
                case MORPHFILLSTYLE::Type::RadialGradient:
                {
                    ret.startGradientMatrix = readMatrix();
                    ret.endGradientMatrix   = readMatrix();
                    ret.gradient            = readMorphGradient();
                }
                break;
                case MORPHFILLSTYLE::Type::RepeatingBitmap:
                case MORPHFILLSTYLE::Type::ClippedBitmap:
                case MORPHFILLSTYLE::Type::NonSmoothedRepeatingBitmap:
                case MORPHFILLSTYLE::Type::NonSmoothedClippedBitmap:
                {
                    ret.bitmapId          = readU16();
                    ret.startBitmapMatrix = readMatrix();
                    ret.endBitmapMatrix   = readMatrix();
                }
                break;
                case MORPHFILLSTYLE::Type::FocalRadialGradient:
                    break;
            }
            return ret;
        }

        MORPHGRADIENT readMorphGradient()
        {
            int numGrads = readU8();
            MORPHGRADIENT ret{MORPHGRADIENT::SpreadMode(readUnsignedBits(2)),
                MORPHGRADIENT::InterpolationMode(readUnsignedBits(2)),
                std::vector<MORPHGRADRECORD>(numGrads)};

            for (auto& record : ret.gradientRecords)
            {
                record = readMorphGradRecord();
            }

            return ret;
        }

        MORPHGRADRECORD readMorphGradRecord()
        {
            return {readU8(), readRGBA(), readU8(), readRGBA()};
        }

        std::vector<unsigned char> decompressZlibFromStream(
            size_t compressedBytes, size_t startingAlloc = 0);

        std::vector<unsigned char> decompressLzmaFromStream(
            size_t compressedBytes, size_t startingAlloc = 0);

    private:
        const unsigned char* mData;
        size_t mCurrentByte;
        size_t mBitsLeft;
    };
}
