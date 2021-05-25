#include "SWF.hpp"
#include "utils/SwfStreamReader.hpp"
#include <stdexcept>
#include <string_view>

unSWF::SWF::SWF(unsigned char* data)
{
    SwfStreamReader reader{data};
    reader.readBytes((unsigned char*)header.signature, 3);
    header.version    = reader.readU8();
    header.fileLength = reader.readU32();
    using namespace std::literals::string_view_literals;
    if (header.signature == "CWS"sv)
    {
        // ZLIB decompress
    }
    else if (header.signature == "ZWS"sv)
    {
        // LZMA decompress
    }
    else if (header.signature != "FWS"sv)
    {
        throw std::invalid_argument("File given is not an SWF");
    }
}
