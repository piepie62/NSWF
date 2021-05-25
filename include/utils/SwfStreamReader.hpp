#pragma once

#include <cassert>
#include <climits>
#include <cstdint>
#include <cstring>
#include <vector>

namespace unSWF
{
    class SwfStreamReader
    {
    public:
        static_assert(CHAR_BIT == 8);

        SwfStreamReader(unsigned char* data) : mData(data), mCurrentByte(0), mBitsLeft(CHAR_BIT) {}

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

    private:
        unsigned char* mData;
        size_t mCurrentByte;
        int mBitsLeft;
    };
}
