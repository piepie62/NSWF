#pragma once

#include <cstdint>

namespace NSWF::tags
{
    class CharacterIdTag
    {
    public:
        virtual ~CharacterIdTag()               = default;
        virtual uint16_t getCharacterId() const = 0;
    };
}
