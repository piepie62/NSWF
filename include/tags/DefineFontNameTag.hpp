#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include <cstdint>

namespace NSWF::tags
{
    class DefineFontNameTag : public SwfTag, public CharacterIdTag
    {
    public:
        DefineFontNameTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::DefineFontName, size)
        {
            fontId        = reader.readU16();
            fontName      = reader.readNTString();
            fontCopyright = reader.readNTString();
        }

        uint16_t getCharacterId() const override { return fontId; }

        uint16_t fontId;
        std::string fontName;
        std::string fontCopyright;
    };
}
