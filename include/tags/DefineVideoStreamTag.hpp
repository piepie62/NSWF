#pragma once

#include "enums/VideoFormat.hpp"
#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class DefineVideoStreamTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineVideoStreamTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::DefineVideoStream, size)
        {
            characterId = reader.readU16();
            numFrames   = reader.readU16();
            width       = reader.readU16();
            height      = reader.readU16();
            // reserved
            reader.readUnsignedBits(4);
            deblockingMode = DeblockingMode(reader.readUnsignedBits(3));
            smoothing      = reader.readFlag();
            codec          = VideoFormat(reader.readU8());
        }

        uint16_t getCharacterId() const override { return characterId; }

        uint16_t characterId;
        uint16_t numFrames;
        uint16_t width;
        uint16_t height;
        enum class DeblockingMode
        {
            VideoPacket,
            Off,
            Level1,
            Level2, // VP6 only
            Level3, // VP6 only
            Level4  // VP6 only
        } deblockingMode;
        bool smoothing;
        VideoFormat codec;
    };
}
