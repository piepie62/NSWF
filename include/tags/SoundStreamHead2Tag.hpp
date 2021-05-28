#pragma once

#include "enums/AudioFormat.hpp"
#include "enums/SoundRate.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class SoundStreamHead2Tag : public SwfTag
    {
    public:
        SoundStreamHead2Tag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::SoundStreamHead2, size)
        {
            // reserved
            reader.readUnsignedBits(4);
            playbackRate       = SoundRate(reader.readUnsignedBits(2));
            playback16Bit      = reader.readFlag();
            playbackStereo     = reader.readFlag();
            format             = AudioFormat(reader.readUnsignedBits(4));
            streamRate         = SoundRate(reader.readUnsignedBits(2));
            stream16Bit        = reader.readFlag();
            streamStereo       = reader.readFlag();
            averageSampleCount = reader.readU16();
            if (format == AudioFormat::MP3)
            {
                latencySeek = reader.readS16();
            }
        }

        SoundRate playbackRate;
        bool playbackStereo;
        bool playback16Bit;
        AudioFormat format;
        SoundRate streamRate;
        bool streamStereo;
        bool stream16Bit;
        uint16_t averageSampleCount;
        std::optional<int16_t> latencySeek;
    };
}
