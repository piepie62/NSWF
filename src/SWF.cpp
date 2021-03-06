#include "SWF.hpp"
#include "lzma.h"
#include "utils/SwfStreamReader.hpp"
#include "zlib.h"
#include <stdexcept>
#include <string_view>

NSWF::SWF::SWF(unsigned char* data, size_t size)
{
    std::vector<unsigned char> possiblyUsedData;
    SwfStreamReader reader{data, size};
    reader.readBytes((unsigned char*)header.signature.data(), 3);
    header.version = reader.readU8();
    assert(header.version > 5);
    header.fileLength = reader.readU32();
    using namespace std::literals::string_view_literals;
    if (header.signature == std::array<char, 3>{'C', 'W', 'S'})
    {
        possiblyUsedData = reader.decompressZlibFromStream(size - 8, header.fileLength);
        reader           = SwfStreamReader{possiblyUsedData.data(), possiblyUsedData.size()};
    }
    else if (header.signature == std::array<char, 3>{'Z', 'W', 'S'})
    {
        possiblyUsedData = reader.decompressLzmaFromStream(size - 8, header.fileLength);
        reader           = SwfStreamReader{possiblyUsedData.data(), possiblyUsedData.size()};
    }
    else if (header.signature != std::array<char, 3>{'F', 'W', 'S'})
    {
        throw std::invalid_argument("File given is not an SWF");
    }

    header.frameSize  = reader.readRect();
    header.frameRate  = reader.readU16();
    header.frameCount = reader.readU16();

    do
    {
        tags.emplace_back(tags::SwfTag::parseTag(reader));
    } while (tags.back()->type() != tags::SwfTagType::End);
}
