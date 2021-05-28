#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class JPEGTablesTag : public SwfTag
    {
        static constexpr unsigned char ERROR_HEADER[] = {0xFF, 0xD9, 0xFF, 0xD8};

    public:
        JPEGTablesTag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::JPEGTables, size)
        {
            if (size != 0)
            {
                jpegData = reader.readBytes(size);
                if (!memcmp(ERROR_HEADER, jpegData.data(), 4))
                {
                    jpegData.erase(jpegData.begin(), jpegData.begin() + 4);
                }
            }
        }

        std::vector<unsigned char> jpegData;
    };
}
