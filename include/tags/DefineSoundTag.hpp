#pragma once

#include "enums/AudioFormat.hpp"
#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include <cstdint>
#include <vector>

namespace NSWF::tags
{
    class DefineSoundTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineSoundTag(SwfStreamReader& reader) : SwfTag(reader)
        {
            soundId             = reader.readU16();
            format              = AudioFormat(reader.readUnsignedBits(4));
            rate                = SoundRate(reader.readUnsignedBits(2));
            uncompressedIs16Bit = reader.readFlag();
            stereo              = reader.readFlag();
            sampleCount         = reader.readU32();
            data                = reader.readBytes(this->dataSize() - 7);
        }

        uint16_t getCharacterId() const override { return soundId; }

        uint16_t soundId;
        AudioFormat format;
        enum class SoundRate
        {
            KHz5_5,
            KHz11,
            KHz22,
            KHz44
        } rate;

        bool uncompressedIs16Bit;
        bool stereo;
        uint32_t sampleCount;
        std::vector<unsigned char> data;
    };
}
