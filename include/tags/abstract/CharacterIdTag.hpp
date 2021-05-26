#pragma once

#include <cstdint>

namespace unSWF::tags
{
    class CharacterIdTag
    {
    public:
        virtual ~CharacterIdTag()               = default;
        virtual uint16_t getCharacterId() const = 0;
    };
}
