#include "utils/SwfStreamReader.hpp"
#include "lzma.h"
#include "zlib.h"
#include <stdexcept>

std::vector<unsigned char> unSWF::SwfStreamReader::decompressZlibFromStream(
    size_t compressedBytes, size_t startingAlloc)
{
    alignToByte();

    std::vector<unsigned char> ret(startingAlloc ? startingAlloc : DECOMPRESS_BLOCK);

    z_stream stream;
    stream.next_in   = const_cast<unsigned char*>(mData + mCurrentByte);
    stream.avail_in  = compressedBytes;
    stream.next_out  = ret.data();
    stream.avail_out = ret.size();

    int code = inflateInit(&stream);
    if (code != Z_OK)
    {
        throw std::invalid_argument("Could not initialize ZLIB decompressor");
    }

    code = inflate(&stream, Z_SYNC_FLUSH);
    while (code != Z_STREAM_END)
    {
        if (code != Z_OK)
        {
            throw std::invalid_argument("Could not decompress data");
        }

        size_t leftoverSpace = stream.avail_out;
        ret.resize(ret.size() + DECOMPRESS_BLOCK);
        stream.avail_out += DECOMPRESS_BLOCK;
        stream.next_out = ret.data() + ret.size() - stream.avail_out;

        code = inflate(&stream, Z_SYNC_FLUSH);
    }

    ret.resize(ret.size() - stream.avail_out);

    inflateEnd(&stream);

    return ret;
}

std::vector<unsigned char> unSWF::SwfStreamReader::decompressLzmaFromStream(
    size_t compressedSize, size_t startingAlloc)
{
    alignToByte();

    std::vector<unsigned char> ret(startingAlloc ? startingAlloc : DECOMPRESS_BLOCK);

    lzma_stream stream;
    stream.next_in   = const_cast<unsigned char*>(mData + mCurrentByte);
    stream.avail_in  = compressedSize;
    stream.next_out  = ret.data();
    stream.avail_out = ret.size();

    lzma_ret code = lzma_auto_decoder(&stream, UINT64_MAX, 0);
    if (code != LZMA_OK)
    {
        throw std::invalid_argument("Could not initialize decompressor stream");
    }

    code = lzma_code(&stream, LZMA_SYNC_FLUSH);
    while (code != LZMA_STREAM_END)
    {
        if (code != LZMA_OK)
        {
            throw std::invalid_argument("Could not finish decoding");
        }

        size_t leftoverSpace = stream.avail_out;
        ret.resize(ret.size() + DECOMPRESS_BLOCK);
        stream.avail_out += DECOMPRESS_BLOCK;
        stream.next_out = ret.data() + ret.size() - stream.avail_out;

        code = lzma_code(&stream, LZMA_SYNC_FLUSH);
    }

    ret.resize(ret.size() - stream.avail_out);

    lzma_end(&stream);

    return ret;
}
