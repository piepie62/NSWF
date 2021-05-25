#pragma once

#include "enums/SwfTagType.hpp"
#include "utils/SwfStreamReader.hpp"
#include <cstdint>
#include <vector>

namespace unSWF::tags
{
    class SwfTag
    {
    public:
        SwfTag(SwfStreamReader& reader)
        {
            mType     = SwfTagType(reader.readUnsignedBits(10));
            mDataSize = reader.readUnsignedBits(6);
            if (mDataSize == 0x3F)
            {
                mDataSize = reader.readU32();
            }
        }
        virtual ~SwfTag() = default;

        SwfTagType type() const { return this->mType; }
        size_t dataSize() const { return this->mDataSize; }

        size_t tagSize() const
        {
            return this->mDataSize >= 0x3F ? this->mDataSize + 6 : this->mDataSize + 2;
        }

    private:
        SwfTagType mType;
        size_t mDataSize;
    };
}
