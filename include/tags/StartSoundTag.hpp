#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include <string>

namespace NSWF::tags
{
    class StartSoundTag : public SwfTag, public CharacterIdTag
    {
    public:
        StartSoundTag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::StartSound, size)
        {
            soundId = reader.readU16();
            info    = reader.readSoundInfo();
        }

        uint16_t getCharacterId() const override { return soundId; }

        uint16_t soundId;
        SOUNDINFO info;
    };
}
