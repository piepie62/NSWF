#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class DoABCTag : public SwfTag
    {
    public:
        DoABCTag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::DoABC, size)
        {
            bytecode = reader.readBytes(size);
        }

        // ABC bytecode;
        std::vector<unsigned char> bytecode;
    };
}
