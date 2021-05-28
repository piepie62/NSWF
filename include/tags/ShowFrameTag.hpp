#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class ShowFrameTag : public SwfTag
    {
    public:
        ShowFrameTag(SwfStreamReader&, size_t size) : SwfTag(SwfTagType::ShowFrame, size) {}
    };
}
