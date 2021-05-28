#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class VideoFrameTag : public SwfTag, public CharacterIdTag
    {
    public:
        VideoFrameTag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::VideoFrame, size)
        {
            streamId  = reader.readU16();
            frameNum  = reader.readU16();
            videoData = reader.readBytes(size - 4);
        }

        uint16_t getCharacterId() const override { return streamId; }

        uint16_t streamId;
        uint16_t frameNum;
        std::vector<unsigned char> videoData;
    };
}
