#pragma once

#include "tags/abstract/SwfTag.hpp"
#include <vector>

namespace NSWF::tags
{
    class SymbolClassTag : public SwfTag
    {
    public:
        SymbolClassTag(SwfStreamReader& reader, size_t size) : SwfTag(SwfTagType::SymbolClass, size)
        {
            int count = reader.readU16();
            assets.reserve(count);

            for (int i = 0; i < count; i++)
            {
                assets.emplace_back(reader.readU16(), reader.readNTString());
            }
        }

        struct Symbol
        {
            Symbol(uint32_t f, std::string&& n) : character(f), className(n) {}
            uint16_t character;
            std::string className;
        };

        std::vector<Symbol> assets;
    };
}
