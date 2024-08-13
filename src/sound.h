#pragma once
#include <psxspu.h>
#include <cstdint>

typedef struct {
	uint32_t magic;			// 0x70474156 ("VAGp") for mono files
	uint32_t version;
	uint32_t interleave;	// Unused in mono files
	uint32_t size;			// Big-endian, in bytes
	uint32_t sample_rate;	// Big-endian, in Hertz
	uint16_t _reserved[5];
	uint16_t channels;		// Unused in mono files
	char     name[16];
} VAG_Header;

typedef struct {
    std::uint16_t address;
    std::uint32_t sampleRate;
}Sound;

// https://github.com/Lameguy64/PSn00bSDK/blob/master/examples/sound/vagsample/main.c
// your sound size needs to be a multiple of 28 samples to avoid padding [28-samples granularity]
// https://psx.arthus.net/sdk/Psy-Q/DOCS/LibOver47.pdf  | pg.271 16-3

class SoundPlayer
{
public:
    SoundPlayer();
    void UploadSound(const void* data, Sound& se);
    void PlaySound(Sound& se);
private:

};