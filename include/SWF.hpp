#pragma once

#include "tags/abstract/SwfTag.hpp"
#include "types/RECT.hpp"
#include "utils/SwfStreamReader.hpp"
#include <cstdint>
#include <memory>
#include <string_view>
#include <vector>

namespace unSWF
{
    class SWF
    {
    public:
        SWF(unsigned char* data, size_t size);

    private:
        struct SwfHeader
        {
            char signature[3];
            int version;
            uint32_t fileLength;
            RECT frameSize;
            uint16_t frameRate;
            uint16_t frameCount;
        } header;
        std::vector<std::unique_ptr<unSWF::tags::SwfTag>> tags;
    };
}
