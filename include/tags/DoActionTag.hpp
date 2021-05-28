#pragma once

#include "tags/abstract/SwfTag.hpp"
#include "types/ACTIONRECORD.hpp"

namespace NSWF::tags
{
    class DoActionTag : public SwfTag
    {
    public:
        DoActionTag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::DoAction, size)
        {
            while (reader.readU8() != 0)
            {
                reader.backtrack();
                actions.emplace_back(reader.readActionRecord());
            }
        }

        std::vector<ACTIONRECORD> actions;
    };
}
