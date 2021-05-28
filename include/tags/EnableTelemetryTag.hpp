#pragma once

#include "tags/abstract/SwfTag.hpp"
#include <array>
#include <optional>

namespace NSWF::tags
{
    class EnableTelemetryTag : public SwfTag
    {
    public:
        EnableTelemetryTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::EnableTelemetry, size)
        {
            // reserved
            // No idea why this isn't listed as a u16, but... whatever
            reader.readUnsignedBits(16);

            if (size > 2)
            {
                sha256Hash = std::array<unsigned char, 32>();
                reader.readBytes(sha256Hash->data(), 32);
            }
        }

        std::optional<std::array<unsigned char, 32>> sha256Hash;
    };
}
