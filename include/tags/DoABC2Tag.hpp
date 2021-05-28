#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class DoABC2Tag : public SwfTag
    {
    public:
        DoABC2Tag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::DoABC2, size)
        {
            flags    = reader.readU32();
            name     = reader.readNTString();
            bytecode = reader.readBytes(size - 4 - name.size() - 1);
        }

        uint32_t flags;
        std::string name;
        // ABC bytecode;
        std::vector<unsigned char> bytecode;
    };
}
