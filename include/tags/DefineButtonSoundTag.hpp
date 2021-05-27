#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/SOUNDINFO.hpp"
#include <vector>

#define READSOUNDINFO(n)                                                                           \
    soundChar##n = reader.readU8();                                                                \
    if (soundChar##n)                                                                              \
    soundInfo##n = reader.readSoundInfo()

namespace NSWF::tags
{
    class DefineButtonSoundTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineButtonSoundTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::DefineButtonSound, size)
        {
            buttonId = reader.readU16();

            READSOUNDINFO(0);
            READSOUNDINFO(1);
            READSOUNDINFO(2);
            READSOUNDINFO(3);
        }

        uint16_t getCharacterId() const override { return buttonId; }

        uint16_t buttonId;
        uint16_t soundChar0;
        uint16_t soundChar1;
        uint16_t soundChar2;
        uint16_t soundChar3;
        SOUNDINFO soundInfo0;
        SOUNDINFO soundInfo1;
        SOUNDINFO soundInfo2;
        SOUNDINFO soundInfo3;
    };
}

#undef READSOUNDINFO
