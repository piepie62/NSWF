#pragma once

#include "tags/abstract/SwfTag.hpp"
#include <string>

namespace NSWF::tags
{
    class ImportAssets2Tag : public SwfTag
    {
    public:
        ImportAssets2Tag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::ImportAssets, size)
        {
            url = reader.readNTString();
            // reserved
            reader.readU8();
            reader.readU8();

            int count = reader.readU16();
            assets.reserve(count);

            for (int i = 0; i < count; i++)
            {
                assets.emplace_back(reader.readU16(), reader.readNTString());
            }
        }

        std::string url;

        struct ImportedAsset
        {
            uint16_t newCharId;
            std::string name;
        };

        std::vector<ImportedAsset> assets;
    };
}
