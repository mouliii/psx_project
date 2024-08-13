#pragma once
#include <psxgpu.h>
#include <cstdint>
#include <cstddef>


class RenderBuffer
{
public:
	RenderBuffer(std::size_t otLength, std::size_t bufferLength);
	~RenderBuffer();
	void Setup(int x, int y, int w, int h, int r, int g, int b);
	inline uint8_t* BufferStart() const {
		return buffer;
	}
	inline uint8_t* BufferEnd() const {
		return &buffer[bufferLength];
	}
	inline uint32_t* OtEntry(int z) const {
		return &ot[z];
	}
	inline void OtClear() {
		ClearOTagR(ot, otLength);
	}
	inline void Draw() {
		DrawOTagEnv(&ot[otLength - 1], &drawEnv);
	}
	inline void Display() {
		PutDispEnv(&dispEnv);
	}

private:
	DISPENV dispEnv;
	DRAWENV drawEnv;

	std::uint32_t* ot;
	std::uint8_t* buffer;
	std::size_t  otLength;
	std::size_t bufferLength;
};