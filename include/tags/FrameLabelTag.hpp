#pragma once

#include "tags/abstract/SwfTag.hpp"
#include <string>

namespace NSWF::tags
{
    class FrameLabelTag : public SwfTag
    {
    public:
        FrameLabelTag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::FrameLabel, size)
        {
            name = reader.readNTString();
        }

        std::string name;
    };
}
