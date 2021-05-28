#pragma once

#include "types/ACTIONRECORD.hpp"
#include "types/ARGB.hpp"
#include "types/BUTTONCONDACTION.hpp"
#include "types/BUTTONRECORD.hpp"
#include "types/BUTTONRECORD2.hpp"
#include "types/CLIPACTIONRECORD.hpp"
#include "types/CLIPEVENTFLAGS.hpp"
#include "types/CXFORM.hpp"
#include "types/CXFORMWITHALPHA.hpp"
#include "types/FILTER.hpp"
#include "types/GLYPHENTRY.hpp"
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
#include "types/TEXTRECORD.hpp"
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
        SwfStreamReader(const unsigned char* data, size_t size)
            : mData(data), mCurrentByte(0), mBitsLeft(CHAR_BIT), mSize(size)
        {
        }

        SwfStreamReader subStream(size_t size, bool advanceThis = false)
        {
            assert(mCurrentByte + size <= mSize);
            SwfStreamReader ret{mData + mCurrentByte, size};
            if (advanceThis)
            {
                mCurrentByte += size;
            }
            return ret;
        }

        bool finished() const { return mCurrentByte == mSize; }

        bool finishedInLessThanOneByte() const
        {
            return finished() || (mCurrentByte == mSize - 1 && mBitsLeft < CHAR_BIT);
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

        uintmax_t readUnsignedBits(size_t bits)
        {
            assert(bits <= sizeof(uintmax_t) * CHAR_BIT);

            uintmax_t ret = 0;
            while (bits >= mBitsLeft)
            {
                assert(mCurrentByte < mSize);
                ret <<= mBitsLeft;
                ret |= mData[mCurrentByte++] & (UCHAR_MAX >> (CHAR_BIT - mBitsLeft));

                bits -= mBitsLeft;
                mBitsLeft = CHAR_BIT;
            }

            if (bits > 0)
            {
                assert(mCurrentByte < mSize);
                ret <<= bits;
                ret |=
                    (mData[mCurrentByte] >> (mBitsLeft - bits)) & (UCHAR_MAX >> (CHAR_BIT - bits));
                mBitsLeft -= bits;
            }
            if (mBitsLeft == 0)
            {
                mCurrentByte++;
                mBitsLeft = CHAR_BIT;
            }

            return ret;
        }

        bool readFlag() { return (bool)readUnsignedBits(1); }

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
            assert(mCurrentByte + 1 <= mSize);
            return mData[mCurrentByte++];
        }
        int8_t readS8() { return readU8(); }

        uint16_t readU16()
        {
            alignToByte();
            assert(mCurrentByte + 2 <= mSize);
            uint16_t ret = mData[mCurrentByte++];
            ret |= uint16_t(mData[mCurrentByte++]) << 8;
            return ret;
        }
        int16_t readS16() { return readU16(); }

        uint32_t readU32()
        {
            alignToByte();
            assert(mCurrentByte + 4 <= mSize);
            uint32_t ret = mData[mCurrentByte++];
            ret |= uint32_t(mData[mCurrentByte++]) << 8;
            ret |= uint32_t(mData[mCurrentByte++]) << 16;
            ret |= uint32_t(mData[mCurrentByte++]) << 24;

            return ret;
        }
        int32_t readS32() { return readS32(); }

        // If necessary, will change to actual 16-bit floats
        float16 readFloat16() { return {readU16()}; }

        float readFloat32()
        {
            alignToByte();
            assert(mCurrentByte + sizeof(float) <= mSize);
            float ret;
            std::memcpy(&ret, &mData[mCurrentByte], sizeof(ret));
            mCurrentByte += sizeof(ret);

            return ret;
        }

        double readFloat64()
        {
            alignToByte();
            assert(mCurrentByte + sizeof(double) <= mSize);
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
            std::vector<unsigned char> ret(num);
            readBytes(ret.data(), num);

            return ret;
        }

        void readBytes(unsigned char* data, size_t num)
        {
            alignToByte();
            assert(mCurrentByte + num <= mSize);
            std::memcpy(data, mData, num);
            mCurrentByte += num;
        }

        std::string readNTString()
        {
            alignToByte();
            std::string ret((const char*)mData + mCurrentByte);
            assert(mCurrentByte + ret.size() + 1 <= mSize);
            mCurrentByte += ret.size() + 1;
            return ret;
        }

        std::string readString(size_t chars)
        {
            alignToByte();
            assert(mCurrentByte + chars <= mSize);
            std::string ret((const char*)mData + mCurrentByte, chars - 1);
            mCurrentByte += chars;
            return ret;
        }

        RECT readRect()
        {
            size_t bits = readUnsignedBits(5);

            RECT ret;
            ret.xMin = readSignedBits(bits);
            ret.xMax = readSignedBits(bits);
            ret.yMin = readSignedBits(bits);
            ret.yMax = readSignedBits(bits);

            alignToByte();

            return ret;
        }

        RGB readRGB()
        {
            RGB ret;
            ret.red   = readU8();
            ret.green = readU8();
            ret.blue  = readU8();
            return ret;
        }
        RGBA readRGBA()
        {
            RGBA ret;
            ret.red   = readU8();
            ret.green = readU8();
            ret.blue  = readU8();
            ret.alpha = readU8();
            return ret;
        }
        ARGB readARGB()
        {
            ARGB ret;
            ret.alpha = readU8();
            ret.red   = readU8();
            ret.green = readU8();
            ret.blue  = readU8();
            return ret;
        }
        PIX15 readPIX15()
        {
            // reserved
            readFlag();
            PIX15 ret;
            ret.red   = uint8_t(readUnsignedBits(5));
            ret.green = uint8_t(readUnsignedBits(5));
            ret.blue  = uint8_t(readUnsignedBits(5));
            return ret;
        }
        PIX24 readPIX24()
        {
            // reserved
            readU8();
            PIX24 ret;
            ret.red   = readU8();
            ret.green = readU8();
            ret.blue  = readU8();
            return ret;
        }

        MATRIX readMatrix()
        {
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

            alignToByte();

            return ret;
        }

        CXFORM readCxform()
        {
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

            alignToByte();

            return ret;
        }

        CXFORMWITHALPHA readCxformWithAlpha()
        {
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

            alignToByte();

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
                    BEVELFILTER ret;
                    ret.shadowColor     = readRGBA();
                    ret.highlightColor  = readRGBA();
                    ret.blurX           = readFixed32();
                    ret.blurY           = readFixed32();
                    ret.angle           = readFixed32();
                    ret.distance        = readFixed32();
                    ret.strength        = readFixed16();
                    ret.innerShadow     = readFlag();
                    ret.knockout        = readFlag();
                    ret.compositeSource = readFlag();
                    ret.onTop           = readFlag();
                    return {ret};
                }
                case FILTER::Blur:
                {
                    BLURFILTER ret;
                    ret.blurX  = readFixed32();
                    ret.blurY  = readFixed32();
                    ret.passes = (int)readUnsignedBits(5);
                    return {ret};
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
                    DROPSHADOWFILTER ret;
                    ret.shadowColor     = readRGBA();
                    ret.blurX           = readFixed32();
                    ret.blurY           = readFixed32();
                    ret.angle           = readFixed32();
                    ret.distance        = readFixed32();
                    ret.strength        = readFixed16();
                    ret.innerShadow     = readFlag();
                    ret.knockout        = readFlag();
                    ret.compositeSource = readFlag();
                    ret.passes          = (int)readUnsignedBits(5);
                    return {ret};
                }
                case FILTER::Glow:
                {
                    GLOWFILTER ret;
                    ret.shadowColor     = readRGBA();
                    ret.blurX           = readFixed32();
                    ret.blurY           = readFixed32();
                    ret.strength        = readFixed16();
                    ret.innerGlow       = readFlag();
                    ret.knockout        = readFlag();
                    ret.compositeSource = readFlag();
                    ret.passes          = (int)readUnsignedBits(5);
                    return {ret};
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

        std::vector<FILTER> readFilterList()
        {
            int numFilters = readU8();
            std::vector<FILTER> ret(numFilters);
            for (auto& filter : ret)
            {
                filter = readFilter();
            }
            return ret;
        }

        BUTTONRECORD readButtonRecord()
        {
            // reserved
            readUnsignedBits(2);
            BUTTONRECORD ret;
            ret.hasBlendMode  = readFlag();
            ret.hasFilterList = readFlag();
            ret.stateHitTest  = readFlag();
            ret.stateDown     = readFlag();
            ret.stateOver     = readFlag();
            ret.stateUp       = readFlag();
            ret.characterId   = readU16();
            ret.placeDepth    = readU16();
            ret.placeMatrix   = readMatrix();
            return ret;
        }

        BUTTONRECORD2 readButtonRecord2()
        {
            // reserved
            readUnsignedBits(2);
            BUTTONRECORD2 ret;
            ret.hasBlendMode   = readFlag();
            ret.hasFilterList  = readFlag();
            ret.stateHitTest   = readFlag();
            ret.stateDown      = readFlag();
            ret.stateOver      = readFlag();
            ret.stateUp        = readFlag();
            ret.characterId    = readU16();
            ret.placeDepth     = readU16();
            ret.placeMatrix    = readMatrix();
            ret.colorTransform = readCxformWithAlpha();
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
            BUTTONCONDACTION ret;
            ret.size              = readU16();
            ret.idleToOverDown    = readFlag();
            ret.outDownToIdle     = readFlag();
            ret.outDownToOverDown = readFlag();
            ret.overDownToOutDown = readFlag();
            ret.overDownToOverUp  = readFlag();
            ret.overUpToOverDown  = readFlag();
            ret.overUpToIdle      = readFlag();
            ret.idleToOverUp      = readFlag();
            ret.keyPress          = (uint8_t)readUnsignedBits(7);
            ret.overDownToIdle    = readFlag();

            while (readU8() != 0)
            {
                backtrack();
                ret.actions.emplace_back(readActionRecord());
            }

            return ret;
        }

        SOUNDENVELOPE readSoundEnvelope()
        {
            SOUNDENVELOPE ret;
            ret.pos44      = readU32();
            ret.leftLevel  = readU16();
            ret.rightLevel = readU16();
            return ret;
        }

        SOUNDINFO readSoundInfo()
        {
            // reserved
            readUnsignedBits(2);
            SOUNDINFO ret;
            ret.syncStop       = readFlag();
            ret.syncNoMultiple = readFlag();
            ret.hasEnvelope    = readFlag();
            ret.hasLoops       = readFlag();
            ret.hasOutPoint    = readFlag();
            ret.hasInPoint     = readFlag();

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

        SHAPERECORD readShapeRecord(int shapeTagNumber, int& fillBits, int& lineBits)
        {
            if (readFlag()) // Is an edge
            {
                if (readFlag()) // is straight
                {
                    int numBits      = (int)readUnsignedBits(4) + 2;
                    bool generalLine = readFlag();
                    STRAIGHTEDGERECORD ret;
                    if (generalLine)
                    {
                        ret.deltaX = readSignedBits(numBits);
                        ret.deltaY = readSignedBits(numBits);
                    }
                    else
                    {
                        if (readFlag()) // is vertical
                        {
                            ret.deltaY = readSignedBits(numBits);
                        }
                        else
                        {
                            ret.deltaX = readSignedBits(numBits);
                        }
                    }
                    return SHAPERECORD{ret};
                }
                else
                {
                    int numBits = readUnsignedBits(4) + 2;
                    CURVEDEDGERECORD ret;
                    ret.controlDeltaX = (int32_t)readSignedBits(numBits);
                    ret.controlDeltaY = (int32_t)readSignedBits(numBits);
                    ret.anchorDeltaX  = (int32_t)readSignedBits(numBits);
                    ret.anchorDeltaY  = (int32_t)readSignedBits(numBits);
                    return SHAPERECORD{ret};
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
            GRADIENT ret;
            ret.spreadMode        = GRADIENT::SpreadMode(readUnsignedBits(2));
            ret.interpolationMode = GRADIENT::InterpolationMode(readUnsignedBits(2));
            int gradients         = (int)readUnsignedBits(4);
            ret.gradientRecords   = std::vector<GRADRECORD>(gradients);
            for (auto& record : ret.gradientRecords)
            {
                record = readGradRecord(rgba);
            }

            return ret;
        }

        FOCALGRADIENT readFocalGradient(bool rgba)
        {
            FOCALGRADIENT ret;
            ret.spreadMode        = FOCALGRADIENT::SpreadMode(readUnsignedBits(2));
            ret.interpolationMode = FOCALGRADIENT::InterpolationMode(readUnsignedBits(2));
            int gradients         = (int)readUnsignedBits(4);
            ret.gradientRecords   = std::vector<GRADRECORD>(gradients);
            for (auto& record : ret.gradientRecords)
            {
                record = readGradRecord(rgba);
            }
            ret.focalPoint = readFixed16();

            return ret;
        }

        GRADRECORD readGradRecord(bool rgba)
        {
            GRADRECORD ret;
            ret.ratio = readU8();
            ret.color = rgba ? readRGBA() : readRGB();
            return ret;
        }

        LINESTYLE readLineStyle(bool rgba)
        {
            LINESTYLE ret;
            ret.width = readU16();
            ret.color = rgba ? readRGBA() : readRGB();
            return ret;
        }

        LINESTYLE2 readLineStyle2()
        {
            LINESTYLE2 ret;
            ret.width         = readU16();
            ret.startCapStyle = LINESTYLE2::CapStyle(readUnsignedBits(2));
            ret.joinStyle     = LINESTYLE2::JoinStyle(readUnsignedBits(2));

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
            alignToByte();

            return ret;
        }

        SHAPEWITHSTYLE readShapeWithStyle(int shapeTagNumber)
        {
            SHAPEWITHSTYLE ret;
            ret.fillStyles = readFillStyleArray(shapeTagNumber >= 3);
            ret.lineStyles = readLineStyleArray(shapeTagNumber);

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
            KERNINGRECORD ret;
            ret.char1      = wideCodes ? readU16() : (uint16_t)readU8();
            ret.char2      = wideCodes ? readU16() : (uint16_t)readU8();
            ret.adjustment = readS16();
            return ret;
        }

        ZONEDATA readZoneData()
        {
            ZONEDATA ret;
            ret.alignmentCoordinate = readFloat16();
            ret.range               = readFloat16();
            return ret;
        }

        ZONERECORD readZoneRecord()
        {
            int numData = readU8();
            ZONERECORD ret{std::vector<ZONEDATA>(numData)};
            for (auto& data : ret.zoneData)
            {
                data = readZoneData();
            }
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
            MORPHLINESTYLE ret;
            ret.startWidth = readU16();
            ret.endWidth   = readU16();
            ret.startColor = readRGBA();
            ret.endColor   = readRGBA();
            return ret;
        }

        MORPHLINESTYLE2 readMorphLineStyle2()
        {
            MORPHLINESTYLE2 ret;
            ret.startWidth            = readU16();
            ret.endWidth              = readU16();
            ret.startCapStyle         = MORPHLINESTYLE2::CapStyle(readUnsignedBits(2));
            ret.joinStyle             = MORPHLINESTYLE2::JoinStyle(readUnsignedBits(2));
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
            MORPHGRADIENT ret;
            ret.spreadMode        = MORPHGRADIENT::SpreadMode(readUnsignedBits(2));
            ret.interpolationMode = MORPHGRADIENT::InterpolationMode(readUnsignedBits(2));
            ret.gradientRecords   = std::vector<MORPHGRADRECORD>(numGrads);

            for (auto& record : ret.gradientRecords)
            {
                record = readMorphGradRecord();
            }

            return ret;
        }

        MORPHGRADRECORD readMorphGradRecord()
        {
            MORPHGRADRECORD ret;
            ret.startRatio = readU8();
            ret.startColor = readRGBA();
            ret.endRatio   = readU8();
            ret.endColor   = readRGBA();
            return ret;
        }

        TEXTRECORD readTextRecord(int defineTagNum, int glyphBits, int advanceBits)
        {
            // type (always 1) and 3 reserved flags
            readUnsignedBits(4);
            bool hasFont    = readFlag();
            bool hasColor   = readFlag();
            bool hasYOffset = readFlag();
            bool hasXOffset = readFlag();

            TEXTRECORD ret;
            if (hasFont)
            {
                ret.fontId = readU16();
            }
            if (hasColor)
            {
                ret.color = defineTagNum == 1 ? readRGB() : readRGBA();
            }
            if (hasXOffset)
            {
                ret.xOffset = readS16();
            }
            if (hasYOffset)
            {
                ret.yOffset = readS16();
            }
            if (hasFont)
            {
                ret.textHeight = readU16();
            }

            int glyphCount = readU8();
            ret.glyphs.reserve(glyphCount);
            for (int i = 0; i < glyphCount; i++)
            {
                ret.glyphs.emplace_back(readGlyphEntry(glyphBits, advanceBits));
            }

            alignToByte();

            return ret;
        }

        GLYPHENTRY readGlyphEntry(int glyphBits, int advanceBits)
        {
            GLYPHENTRY ret;
            ret.index   = readUnsignedBits(glyphBits);
            ret.advance = readUnsignedBits(advanceBits);
            return ret;
        }

        CLIPACTIONRECORD readClipActionRecord()
        {
            CLIPACTIONRECORD ret{readClipEventFlags()};
            // Unnecessary
            size_t recordsSize = readU32();
            if (ret.events.clipEventKeyPress)
            {
                ret.keyCode = readU8();
            }
            size_t readSize = 0;
            while (readSize < recordsSize)
            {
                ret.actions.emplace_back(readActionRecord());
                readSize += ret.actions.back().actionData.size() + 1;
            }

            return ret;
        }

        CLIPEVENTFLAGS readClipEventFlags()
        {
            CLIPEVENTFLAGS ret;
            ret.clipEventKeyUp          = readFlag();
            ret.clipEventKeyDown        = readFlag();
            ret.clipEventMouseUp        = readFlag();
            ret.clipEventMouseDown      = readFlag();
            ret.clipEventMouseMove      = readFlag();
            ret.clipEventUnload         = readFlag();
            ret.clipEventEnterFrame     = readFlag();
            ret.clipEventLoad           = readFlag();
            ret.clipEventDragOver       = readFlag();
            ret.clipEventRollOut        = readFlag();
            ret.clipEventRollOver       = readFlag();
            ret.clipEventReleaseOutside = readFlag();
            ret.clipEventRelease        = readFlag();
            ret.clipEventPress          = readFlag();
            ret.clipEventInitialize     = readFlag();
            ret.clipEventData           = readFlag();
            // reserved
            readUnsignedBits(5);
            ret.clipEventConstruct = readFlag();
            ret.clipEventKeyPress  = readFlag();
            ret.clipEventDragOut   = readFlag();
            // reserved
            readUnsignedBits(8);

            return ret;
        }

        std::vector<unsigned char> decompressZlibFromStream(
            size_t compressedBytes, size_t startingAlloc = 0);

        std::vector<unsigned char> decompressLzmaFromStream(
            size_t compressedBytes, size_t startingAlloc = 0);

    private:
        const unsigned char* mData;
        size_t mCurrentByte;
        size_t mBitsLeft;
        size_t mSize;
    };
}
