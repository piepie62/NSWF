#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class DefineSceneAndFrameLabelDataTag : public SwfTag
    {
    public:
        DefineSceneAndFrameLabelDataTag(SwfStreamReader& reader, size_t size)
            : SwfTag(SwfTagType::DefineSceneAndFrameLabelData, size)
        {
            uint32_t count = reader.readEncodedU32();
            scenes.reserve(count);
            for (uint32_t i = 0; i < count; i++)
            {
                uint32_t x = reader.readEncodedU32();
                scenes.emplace_back(x, reader.readNTString());
            }

            count = reader.readEncodedU32();
            frameLabels.reserve(count);
            for (uint32_t i = 0; i < count; i++)
            {
                uint32_t x = reader.readEncodedU32();
                frameLabels.emplace_back(x, reader.readNTString());
            }
        }

        struct Scene
        {
            Scene(uint32_t f, std::string&& n) : frameOffset(f), name(n) {}
            uint32_t frameOffset;
            std::string name;
        };

        struct FrameLabel
        {
            FrameLabel(uint32_t f, std::string&& n) : frameNum(f), name(n) {}
            uint32_t frameNum;
            std::string name;
        };

        std::vector<Scene> scenes;
        std::vector<FrameLabel> frameLabels;
    };
}
