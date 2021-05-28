#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class ScriptLimitsTag : public SwfTag
    {
    public:
        ScriptLimitsTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::ScriptLimits, size)
        {
            maxRecursionDepth    = reader.readU16();
            scriptTimeoutSeconds = reader.readU16();
        }

        uint16_t maxRecursionDepth;
        uint16_t scriptTimeoutSeconds;
    };
}
