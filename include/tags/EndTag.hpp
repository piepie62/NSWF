#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class EndTag : public SwfTag
    {
    public:
        EndTag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::End, size) {}
    };
}
