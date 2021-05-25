#pragma once

#include "utils/SwfStreamReader.hpp"

namespace unSWF
{
    class RECT
    {
    public:
        RECT() : mXMin(0), mXMax(0), mYMin(0), mYMax(0) {}
        RECT(SwfStreamReader& reader)
        {
            reader.alignToByte();
            size_t bits = reader.readUnsignedBits(5);
            mXMin       = reader.readSignedBits(bits);
            mXMax       = reader.readSignedBits(bits);
            mYMin       = reader.readSignedBits(bits);
            mYMax       = reader.readSignedBits(bits);
        }

        intmax_t mXMin, mXMax, mYMin, mYMax;
    };
}
