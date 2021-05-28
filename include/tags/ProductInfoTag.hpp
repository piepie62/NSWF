#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class ProductInfoTag : public SwfTag
    {
    public:
        ProductInfoTag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::ProductInfo, size)
        {
            productId           = reader.readU32();
            edition             = reader.readU32();
            majorVersion        = reader.readU8();
            minorVersion        = reader.readU8();
            buildLow            = reader.readU32();
            buildHigh           = reader.readU32();
            compilationDateLow  = reader.readU32();
            compilationDateHigh = reader.readU32();
        }

        uint32_t productId;
        uint32_t edition;
        uint8_t majorVersion;
        uint8_t minorVersion;
        uint32_t buildLow;
        uint32_t buildHigh;
        uint32_t compilationDateLow;
        uint32_t compilationDateHigh;
    };
}
