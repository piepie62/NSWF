#pragma once

namespace unSWF::tags
{
    class CharacterIdTag
    {
    public:
        virtual ~CharacterIdTag()          = default;
        virtual int getCharacterId() const = 0;
    };
}
