#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class SyncFrameTag : public SwfTag
    {
    public:
        SyncFrameTag(SwfStreamReader&, size_t size) : SwfTag(SwfTagType::SyncFrame, size) {}
    };
}
