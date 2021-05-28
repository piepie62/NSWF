#pragma once

#include "tags/abstract/SwfTag.hpp"
#include <string>

namespace NSWF::tags
{
    class StartSound2Tag : public SwfTag
    {
    public:
        StartSound2Tag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::StartSound2, size)
        {
            className = reader.readNTString();
            info      = reader.readSoundInfo();
        }

        std::string className;
        SOUNDINFO info;
    };
}
