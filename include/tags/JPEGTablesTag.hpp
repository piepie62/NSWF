#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace unSWF::tags
{
    class JPEGTablesTag : public SwfTag
    {
        static constexpr unsigned char ERROR_HEADER[] = {0xFF, 0xD9, 0xFF, 0xD8};

    public:
        JPEGTablesTag(SwfStreamReader& reader) : SwfTag(reader)
        {
            jpegData = reader.readBytes(this->dataSize() - 2);
            if (!memcmp(ERROR_HEADER, jpegData.data(), 4))
            {
                jpegData.erase(jpegData.begin(), jpegData.begin() + 4);
            }
        }

    private:
        std::vector<unsigned char> jpegData;
    };
}
