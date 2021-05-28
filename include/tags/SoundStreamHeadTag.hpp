#pragma once

#include "enums/AudioFormat.hpp"
#include "enums/SoundRate.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class SoundStreamHeadTag : public SwfTag
    {
    public:
        SoundStreamHeadTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::SoundStreamHead, size)
        {
            // reserved
            reader.readUnsignedBits(4);
            playbackRate = SoundRate(reader.readUnsignedBits(2));
            // bool 16Bit: always true
            reader.readFlag();
            playbackStereo = reader.readFlag();
            format         = AudioFormat(reader.readUnsignedBits(4));
            streamRate     = SoundRate(reader.readUnsignedBits(2));
            // bool 16Bit: always true
            reader.readFlag();
            streamStereo       = reader.readFlag();
            averageSampleCount = reader.readU16();
            if (format == AudioFormat::MP3)
            {
                latencySeek = reader.readS16();
            }
        }

        SoundRate playbackRate;
        bool playbackStereo;
        AudioFormat format;
        SoundRate streamRate;
        bool streamStereo;
        uint16_t averageSampleCount;
        std::optional<int16_t> latencySeek;
    };
}
