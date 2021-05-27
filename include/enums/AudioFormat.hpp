#pragma once

namespace NSWF
{
    enum class AudioFormat
    {
        UncompressedNativeEndian,
        ADPCM,
        MP3,
        UncompressedLittleEndian,
        NellyMoser16KHz,
        NellyMoser8KHz,
        NellyMoser,
        Speex
    };
}
