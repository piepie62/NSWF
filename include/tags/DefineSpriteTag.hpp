#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class DefineSpriteTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineSpriteTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::DefineSprite, size)
        {
            spriteId   = reader.readU16();
            frameCount = reader.readU16();

            do
            {
                controlTags.emplace_back(SwfTag::parseTag(reader));
            } while (controlTags.back()->type() != SwfTagType::End);
        }

        uint16_t getCharacterId() const override { return spriteId; }

        uint16_t spriteId;
        uint16_t frameCount;
        std::vector<std::unique_ptr<SwfTag>> controlTags;
    };
}
