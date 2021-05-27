#pragma once

#include "tags/abstract/CharacterIdTag.hpp"
#include "tags/abstract/SwfTag.hpp"
#include "types/RGBA.hpp"
#include <optional>
#include <string>

namespace NSWF::tags
{
    class DefineEditTextTag : public SwfTag, public CharacterIdTag
    {
    public:
        enum Align
        {
            Left,
            Right,
            Center,
            Justify
        };

        DefineEditTextTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::DefineEditText, size)
        {
            characterId       = reader.readU16();
            bounds            = reader.readRect();
            bool hasText      = reader.readFlag();
            wordWrap          = reader.readFlag();
            multiLine         = reader.readFlag();
            isPassword        = reader.readFlag();
            readOnly          = reader.readFlag();
            bool hasTextColor = reader.readFlag();
            bool hasMaxLength = reader.readFlag();
            bool hasFont      = reader.readFlag();
            bool hasFontClass = reader.readFlag();
            autoSize          = reader.readFlag();
            bool hasLayout    = reader.readFlag();
            noSelect          = reader.readFlag();
            border            = reader.readFlag();
            wasStatic         = reader.readFlag();
            html              = reader.readFlag();
            useOutlines       = reader.readFlag();

            if (hasFont)
            {
                fontId = reader.readU16();
            }
            if (hasFontClass)
            {
                fontClass = reader.readNTString();
            }
            if (hasFont)
            {
                fontHeight = reader.readU16();
            }
            if (hasTextColor)
            {
                textColor = reader.readRGBA();
            }
            if (hasMaxLength)
            {
                maxLength = reader.readU16();
            }
            if (hasLayout)
            {
                align       = Align(reader.readU8());
                leftMargin  = reader.readU16();
                rightMargin = reader.readU16();
                indent      = reader.readU16();
                leading     = reader.readS16();
            }
            variableName = reader.readNTString();
            if (hasText)
            {
                initialText = reader.readNTString();
            }
        }

        uint16_t getCharacterId() const override { return characterId; }

        uint16_t characterId;
        RECT bounds;
        bool wordWrap;
        bool multiLine;
        bool isPassword;
        bool readOnly;
        bool autoSize;
        bool noSelect;
        bool border;
        bool wasStatic;
        bool html;
        bool useOutlines;
        std::optional<uint16_t> fontId;
        std::optional<std::string> fontClass;
        std::optional<uint16_t> fontHeight;
        std::optional<RGBA> textColor;
        std::optional<uint16_t> maxLength;
        std::optional<Align> align;
        std::optional<uint16_t> leftMargin;
        std::optional<uint16_t> rightMargin;
        std::optional<uint16_t> indent;
        std::optional<int16_t> leading;
        std::string variableName;
        std::optional<std::string> initialText;
    };
}
