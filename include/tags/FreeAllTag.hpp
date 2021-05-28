#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class FreeAllTag : public SwfTag
    {
    public:
        FreeAllTag(SwfStreamReader&, size_t size) : SwfTag(SwfTagType::FreeAll, size) {}
    };
}
