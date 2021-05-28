#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class EnableDebugger2Tag : public SwfTag
    {
    public:
        EnableDebugger2Tag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::EnableDebugger, size)
        {
            // reserved
            reader.readU16();
            password = reader.readNTString();
        }

        std::string password;
    };
}
