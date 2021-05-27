#pragma once

#include "enums/SwfTagType.hpp"
#include "utils/SwfStreamReader.hpp"
#include <cstdint>
#include <vector>

namespace NSWF::tags
{
    class SwfTag
    {
    public:
        SwfTag(SwfTagType type, size_t dataSize) : mType(type), mDataSize(dataSize) {}
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
