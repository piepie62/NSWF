#pragma once

#include "tags/abstract/SwfTag.hpp"
#include <vector>

namespace unSWF::tags
{
    class DefineBinaryDataTag : public SwfTag
    {
    public:
        DefineBinaryDataTag(SwfStreamReader& reader) : SwfTag(reader)
        {
            tag = reader.readU16();
            // reserved
            reader.readU32();
            data = reader.readBytes(this->dataSize() - 6);
        }

    private:
        int tag;
        std::vector<unsigned char> data;
    };
}
