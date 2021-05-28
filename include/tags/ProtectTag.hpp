#pragma once

#include "tags/abstract/SwfTag.hpp"
#include <optional>
#include <string>

namespace NSWF::tags
{
    class ProtectTag : public SwfTag
    {
    public:
        ProtectTag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::Protect, size)
        {
            // reserved
            reader.readU16();
            if (size != 0)
            {
                password = reader.readNTString();
            }
        }

        std::optional<std::string> password;
    };
}
