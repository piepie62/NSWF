#pragma once

#include "tags/abstract/SwfTag.hpp"
#include <vector>

namespace NSWF::tags
{
    class ExportAssetsTag : public SwfTag
    {
    public:
        ExportAssetsTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::ExportAssets, size)
        {
            int count = reader.readU16();
            assets.reserve(count);

            for (int i = 0; i < count; i++)
            {
                assets.emplace_back(reader.readU16(), reader.readNTString());
            }
        }

        struct ExportedAsset
        {
            ExportedAsset(uint32_t f, std::string&& n) : character(f), name(n) {}
            uint16_t character;
            std::string name;
        };

        std::vector<ExportedAsset> assets;
    };
}
