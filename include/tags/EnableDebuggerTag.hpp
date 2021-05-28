#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class EnableDebuggerTag : public SwfTag
    {
    public:
        EnableDebuggerTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::EnableDebugger, size)
        {
            password = reader.readNTString();
        }

        std::string password;
    };
}
