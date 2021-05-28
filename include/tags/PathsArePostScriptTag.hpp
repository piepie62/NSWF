#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class PathsArePostScriptTag : public SwfTag
    {
    public:
        PathsArePostScriptTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::PathsArePostScript, size)
        {
        }
    };
}
