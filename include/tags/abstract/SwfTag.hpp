#pragma once

#include "enums/SwfTagType.hpp"
#include "utils/SwfStreamReader.hpp"
#include <cstdint>
#include <memory>
#include <vector>

namespace NSWF::tags
{
    class SwfTag
    {
    public:
        SwfTag(SwfTagType type, size_t dataSize) : mType(type), mDataSize(dataSize) {}
        // Stops this from being instantiable
        virtual ~SwfTag() = 0;

        SwfTagType type() const { return this->mType; }
        size_t dataSize() const { return this->mDataSize; }

        size_t tagSize() const
        {
            return this->mDataSize >= 0x3F ? this->mDataSize + 6 : this->mDataSize + 2;
        }

        static std::unique_ptr<SwfTag> parseTag(SwfStreamReader& reader);

    private:
        SwfTagType mType;
        size_t mDataSize;
    };

    inline SwfTag::~SwfTag() {}
}
