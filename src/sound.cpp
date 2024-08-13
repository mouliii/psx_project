#include "sound.h"

#define getADSR1(attackMode, attackShift, attackStep, decayShift, sustainLevel) \
	(((attackMode) << 15) | ((attackShift) << 10) | ((attackStep) << 8) | ((decayShift) << 4) | (sustainLevel))
#define getADSR2(sustainMode, sustainDir, sustainShift, sustainStep, releaseMode, releaseShift) \
	(((sustainMode) << 15) | ((sustainDir) << 14) | ((sustainShift) << 8) | ((sustainStep) << 6) | ((releaseMode) << 5) | (releaseShift))

#define ALLOC_START_ADDR 0x1010
static std::uint16_t next_sample_addr = ALLOC_START_ADDR;
static std::uint8_t next_channel = 0;

SoundPlayer::SoundPlayer()
{
    SpuInit();
}

void SoundPlayer::UploadSound(const void* data, Sound& se)
{
    VAG_Header* vagHeader = (VAG_Header*)data;
    std::uint32_t size = __builtin_bswap32(vagHeader->size);
    se.sampleRate = __builtin_bswap32(vagHeader->sample_rate); // bswap -> change freq
    se.address = next_sample_addr;

	std::uint32_t _size = (size + 63) & ~63;

    SpuSetTransferMode(SPU_TRANSFER_BY_DMA);
    SpuSetTransferStartAddr(se.address);
    SpuWrite((const std::uint32_t*)(vagHeader+1), size);
    SpuIsTransferCompleted(SPU_TRANSFER_WAIT);

    next_sample_addr = se.address + _size;
}

void SoundPlayer::PlaySound(Sound& se)
{
    std::uint8_t ch = next_channel;
    // Make sure the channel is stopped.
	SpuSetKey(0, 1 << ch);
    // Set the channel's sample rate and start address. Note that the SPU
	// expects the sample rate to be in 4.12 fixed point format (with
	// 1.0 = 44100 Hz) and the address in 8-byte units; psxspu.h provides the
	// getSPUSampleRate() and getSPUAddr() macros to convert values to these
	// units.
	SPU_CH_FREQ(ch) = getSPUSampleRate(se.sampleRate);
	SPU_CH_ADDR(ch) = getSPUAddr(se.address);
    // Set the channel's volume and ADSR parameters (0x80ff and 0x1fee are
	// dummy values that disable the ADSR envelope entirely).
    SPU_CH_VOL_L(ch) = 0x3fff;
	SPU_CH_VOL_R(ch) = 0x3fff;
    SPU_CH_ADSR1(ch) = 0x00ff; // ??
	SPU_CH_ADSR2(ch) = 0x0000; 
    // Start the channel.
	SpuSetKey(1, 1 << ch);
    next_channel = (ch + 1) % 24;
}
