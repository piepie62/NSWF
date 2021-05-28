#include "tags/abstract/SwfTag.hpp"
#include "tags/CSMTextSettingsTag.hpp"
#include "tags/DebugIdTag.hpp"
#include "tags/DefineBinaryDataTag.hpp"
#include "tags/DefineBitsJPEG2Tag.hpp"
#include "tags/DefineBitsJPEG3Tag.hpp"
#include "tags/DefineBitsJPEG4Tag.hpp"
#include "tags/DefineBitsLossless2Tag.hpp"
#include "tags/DefineBitsLosslessTag.hpp"
#include "tags/DefineBitsTag.hpp"
#include "tags/DefineButton2Tag.hpp"
#include "tags/DefineButtonCxformTag.hpp"
#include "tags/DefineButtonSoundTag.hpp"
#include "tags/DefineButtonTag.hpp"
#include "tags/DefineEditTextTag.hpp"
#include "tags/DefineFont2Tag.hpp"
#include "tags/DefineFont3Tag.hpp"
#include "tags/DefineFont4Tag.hpp"
#include "tags/DefineFontAlignZonesTag.hpp"
#include "tags/DefineFontInfo2Tag.hpp"
#include "tags/DefineFontInfoTag.hpp"
#include "tags/DefineFontNameTag.hpp"
#include "tags/DefineFontTag.hpp"
#include "tags/DefineMorphShape2Tag.hpp"
#include "tags/DefineMorphShapeTag.hpp"
#include "tags/DefineScalingGridTag.hpp"
#include "tags/DefineSceneAndFrameLabelDataTag.hpp"
#include "tags/DefineShape2Tag.hpp"
#include "tags/DefineShape3Tag.hpp"
#include "tags/DefineShape4Tag.hpp"
#include "tags/DefineShapeTag.hpp"
#include "tags/DefineSoundTag.hpp"
#include "tags/DefineSpriteTag.hpp"
#include "tags/DefineText2Tag.hpp"
#include "tags/DefineTextTag.hpp"
#include "tags/DefineVideoStreamTag.hpp"
#include "tags/DoABC2Tag.hpp"
#include "tags/DoABCTag.hpp"
#include "tags/DoActionTag.hpp"
#include "tags/DoInitActionTag.hpp"
#include "tags/EnableDebugger2Tag.hpp"
#include "tags/EnableDebuggerTag.hpp"
#include "tags/EnableTelemetryTag.hpp"
#include "tags/EndTag.hpp"
#include "tags/ExportAssetsTag.hpp"
#include "tags/FileAttributesTag.hpp"
#include "tags/FrameLabelTag.hpp"
#include "tags/FreeAllTag.hpp"
#include "tags/FreeCharacterTag.hpp"
#include "tags/ImportAssets2Tag.hpp"
#include "tags/ImportAssetsTag.hpp"
#include "tags/JPEGTablesTag.hpp"
#include "tags/MetadataTag.hpp"
#include "tags/NameCharacterTag.hpp"
#include "tags/PathsArePostScriptTag.hpp"
#include "tags/PlaceObject2Tag.hpp"
#include "tags/PlaceObject3Tag.hpp"
#include "tags/PlaceObject4Tag.hpp"
#include "tags/PlaceObjectTag.hpp"
#include "tags/ProductInfoTag.hpp"
#include "tags/ProtectTag.hpp"
#include "tags/RemoveObject2Tag.hpp"
#include "tags/RemoveObjectTag.hpp"
#include "tags/ScriptLimitsTag.hpp"
#include "tags/SetBackgroundColorTag.hpp"
#include "tags/SetTabIndexTag.hpp"
#include "tags/ShowFrameTag.hpp"
#include "tags/SoundStreamBlockTag.hpp"
#include "tags/SoundStreamHead2Tag.hpp"
#include "tags/SoundStreamHeadTag.hpp"
#include "tags/StartSound2Tag.hpp"
#include "tags/StartSoundTag.hpp"
#include "tags/SymbolClassTag.hpp"
#include "tags/SyncFrameTag.hpp"
#include "tags/VideoFrameTag.hpp"
#include <stdexcept>

std::unique_ptr<NSWF::tags::SwfTag> NSWF::tags::SwfTag::parseTag(SwfStreamReader& _reader)
{
    SwfTagType type = SwfTagType(_reader.readUnsignedBits(10));
    size_t size     = (size_t)_reader.readUnsignedBits(6);
    if (size == 0x3F)
    {
        size = _reader.readU32();
    }

    SwfStreamReader reader = _reader.subStream(size, true);

    switch (type)
    {
        case SwfTagType::CSMTextSettings:
            return std::make_unique<CSMTextSettingsTag>(reader, size);
        case SwfTagType::DebugID:
            return std::make_unique<DebugIdTag>(reader, size);
        case SwfTagType::DefineBinaryData:
            return std::make_unique<DefineBinaryDataTag>(reader, size);
        case SwfTagType::DefineBitsJPEG2:
            return std::make_unique<DefineBitsJPEG2Tag>(reader, size);
        case SwfTagType::DefineBitsJPEG3:
            return std::make_unique<DefineBitsJPEG3Tag>(reader, size);
        case SwfTagType::DefineBitsJPEG4:
            return std::make_unique<DefineBitsJPEG4Tag>(reader, size);
        case SwfTagType::DefineBitsLossless2:
            return std::make_unique<DefineBitsLossless2Tag>(reader, size);
        case SwfTagType::DefineBitsLossless:
            return std::make_unique<DefineBitsLosslessTag>(reader, size);
        case SwfTagType::DefineBits:
            return std::make_unique<DefineBitsTag>(reader, size);
        case SwfTagType::DefineButton2:
            return std::make_unique<DefineButton2Tag>(reader, size);
        case SwfTagType::DefineButtonCxform:
            return std::make_unique<DefineButtonCxformTag>(reader, size);
        case SwfTagType::DefineButtonSound:
            return std::make_unique<DefineButtonSoundTag>(reader, size);
        case SwfTagType::DefineButton:
            return std::make_unique<DefineButtonTag>(reader, size);
        case SwfTagType::DefineEditText:
            return std::make_unique<DefineEditTextTag>(reader, size);
        case SwfTagType::DefineFont2:
            return std::make_unique<DefineFont2Tag>(reader, size);
        case SwfTagType::DefineFont3:
            return std::make_unique<DefineFont3Tag>(reader, size);
        case SwfTagType::DefineFont4:
            return std::make_unique<DefineFont4Tag>(reader, size);
        case SwfTagType::DefineFontAlignZones:
            return std::make_unique<DefineFontAlignZonesTag>(reader, size);
        case SwfTagType::DefineFontInfo2:
            return std::make_unique<DefineFontInfo2Tag>(reader, size);
        case SwfTagType::DefineFontInfo:
            return std::make_unique<DefineFontInfoTag>(reader, size);
        case SwfTagType::DefineFontName:
            return std::make_unique<DefineFontNameTag>(reader, size);
        case SwfTagType::DefineFont:
            return std::make_unique<DefineFontTag>(reader, size);
        case SwfTagType::DefineMorphShape2:
            return std::make_unique<DefineMorphShape2Tag>(reader, size);
        case SwfTagType::DefineMorphShape:
            return std::make_unique<DefineMorphShapeTag>(reader, size);
        case SwfTagType::DefineScalingGrid:
            return std::make_unique<DefineScalingGridTag>(reader, size);
        case SwfTagType::DefineSceneAndFrameLabelData:
            return std::make_unique<DefineSceneAndFrameLabelDataTag>(reader, size);
        case SwfTagType::DefineShape2:
            return std::make_unique<DefineShape2Tag>(reader, size);
        case SwfTagType::DefineShape3:
            return std::make_unique<DefineShape3Tag>(reader, size);
        case SwfTagType::DefineShape4:
            return std::make_unique<DefineShape4Tag>(reader, size);
        case SwfTagType::DefineShape:
            return std::make_unique<DefineShapeTag>(reader, size);
        case SwfTagType::DefineSound:
            return std::make_unique<DefineSoundTag>(reader, size);
        case SwfTagType::DefineSprite:
            return std::make_unique<DefineSpriteTag>(reader, size);
        case SwfTagType::DefineText2:
            return std::make_unique<DefineText2Tag>(reader, size);
        case SwfTagType::DefineText:
            return std::make_unique<DefineTextTag>(reader, size);
        case SwfTagType::DefineVideoStream:
            return std::make_unique<DefineVideoStreamTag>(reader, size);
        case SwfTagType::DoABC:
            return std::make_unique<DoABCTag>(reader, size);
        case SwfTagType::DoABC2:
            return std::make_unique<DoABC2Tag>(reader, size);
        case SwfTagType::DoAction:
            return std::make_unique<DoActionTag>(reader, size);
        case SwfTagType::DoInitAction:
            return std::make_unique<DoInitActionTag>(reader, size);
        case SwfTagType::EnableDebugger2:
            return std::make_unique<EnableDebugger2Tag>(reader, size);
        case SwfTagType::EnableDebugger:
            return std::make_unique<EnableDebuggerTag>(reader, size);
        case SwfTagType::EnableTelemetry:
            return std::make_unique<EnableTelemetryTag>(reader, size);
        case SwfTagType::End:
            return std::make_unique<EndTag>(reader, size);
        case SwfTagType::ExportAssets:
            return std::make_unique<ExportAssetsTag>(reader, size);
        case SwfTagType::FileAttributes:
            return std::make_unique<FileAttributesTag>(reader, size);
        case SwfTagType::FrameLabel:
            return std::make_unique<FrameLabelTag>(reader, size);
        case SwfTagType::FreeAll:
            return std::make_unique<FreeAllTag>(reader, size);
        case SwfTagType::FreeCharacter:
            return std::make_unique<FreeCharacterTag>(reader, size);
        case SwfTagType::ImportAssets2:
            return std::make_unique<ImportAssets2Tag>(reader, size);
        case SwfTagType::ImportAssets:
            return std::make_unique<ImportAssetsTag>(reader, size);
        case SwfTagType::JPEGTables:
            return std::make_unique<JPEGTablesTag>(reader, size);
        case SwfTagType::Metadata:
            return std::make_unique<MetadataTag>(reader, size);
        case SwfTagType::NameCharacter:
            return std::make_unique<NameCharacterTag>(reader, size);
        case SwfTagType::PathsArePostScript:
            return std::make_unique<PathsArePostScriptTag>(reader, size);
        case SwfTagType::PlaceObject2:
            return std::make_unique<PlaceObject2Tag>(reader, size);
        case SwfTagType::PlaceObject3:
            return std::make_unique<PlaceObject3Tag>(reader, size);
        case SwfTagType::PlaceObject4:
            return std::make_unique<PlaceObject4Tag>(reader, size);
        case SwfTagType::PlaceObject:
            return std::make_unique<PlaceObjectTag>(reader, size);
        case SwfTagType::ProductInfo:
            return std::make_unique<ProductInfoTag>(reader, size);
        case SwfTagType::Protect:
            return std::make_unique<ProtectTag>(reader, size);
        case SwfTagType::RemoveObject2:
            return std::make_unique<RemoveObject2Tag>(reader, size);
        case SwfTagType::RemoveObject:
            return std::make_unique<RemoveObjectTag>(reader, size);
        case SwfTagType::ScriptLimits:
            return std::make_unique<ScriptLimitsTag>(reader, size);
        case SwfTagType::SetBackgroundColor:
            return std::make_unique<SetBackgroundColorTag>(reader, size);
        case SwfTagType::SetTabIndex:
            return std::make_unique<SetTabIndexTag>(reader, size);
        case SwfTagType::ShowFrame:
            return std::make_unique<ShowFrameTag>(reader, size);
        case SwfTagType::SoundStreamBlock:
            return std::make_unique<SoundStreamBlockTag>(reader, size);
        case SwfTagType::SoundStreamHead2:
            return std::make_unique<SoundStreamHead2Tag>(reader, size);
        case SwfTagType::SoundStreamHead:
            return std::make_unique<SoundStreamHeadTag>(reader, size);
        case SwfTagType::StartSound2:
            return std::make_unique<StartSound2Tag>(reader, size);
        case SwfTagType::StartSound:
            return std::make_unique<StartSoundTag>(reader, size);
        case SwfTagType::SymbolClass:
            return std::make_unique<SymbolClassTag>(reader, size);
        case SwfTagType::SyncFrame:
            return std::make_unique<SyncFrameTag>(reader, size);
        case SwfTagType::VideoFrame:
            return std::make_unique<VideoFrameTag>(reader, size);
        default:
            throw std::invalid_argument("Unrecognized SWF tag type");
    }
}
