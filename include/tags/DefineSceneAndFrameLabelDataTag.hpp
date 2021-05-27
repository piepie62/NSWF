#pragma once

#include "tags/abstract/SwfTag.hpp"

namespace NSWF::tags
{
    class DefineSceneAndFrameLabelData : public SwfTag
    {
    public:
        DefineSceneAndFrameLabelData(SwfStreamReader& reader) : SwfTag(reader)
        {
            uint32_t count = reader.readEncodedU32();
            scenes.reserve(count);
            for (uint32_t i = 0; i < count; i++)
            {
                scenes.emplace_back(reader.readEncodedU32(), reader.readNTString());
            }

            count = reader.readEncodedU32();
            frameLabels.reserve(count);
            for (uint32_t i = 0; i < count; i++)
            {
                frameLabels.emplace_back(reader.readEncodedU32(), reader.readNTString());
            }
        }

        struct Scene
        {
            uint32_t frameOffset;
            std::string name;
        };

        struct FrameLabel
        {
            uint32_t frameNum;
            std::string name;
        };

        std::vector<Scene> scenes;
        std::vector<FrameLabel> frameLabels;
    };
}
