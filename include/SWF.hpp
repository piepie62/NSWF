#pragma once

#include "tags/abstract/SwfTag.hpp"
#include "types/RECT.hpp"
#include "utils/SwfStreamReader.hpp"
#include <cstdint>
#include <memory>
#include <string_view>
#include <vector>

namespace NSWF
{
    class SWF
    {
    public:
        SWF(unsigned char* data, size_t size);

        struct SwfHeader
        {
            char signature[3];
            int version;
            uint32_t fileLength;
            RECT frameSize;
            uint16_t frameRate;
            uint16_t frameCount;
        } header;
        std::vector<std::unique_ptr<NSWF::tags::SwfTag>> tags;
    };
}
