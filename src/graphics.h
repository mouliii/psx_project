#pragma once
#include <cstdint>
#include <cassert>
#include "render_buffer.h"
#include "texture.h"


class Graphics
{
public:
	Graphics(std::size_t ot_length, std::size_t buffer_length);
	void Setup(int w, int h, int r, int g, int b);
	void Flip();
	void UploadTexture(std::uint32_t* tim,  Texture* tex);
	inline void DrawText(int x, int y, int z, const char* text){
		nextPacket = reinterpret_cast<uint8_t*>(FntSort(DrawBuffer().OtEntry(z), nextPacket, x, y, text));
		assert(nextPacket <= DrawBuffer().BufferEnd());
	}
	template<typename T> inline T* NewPrimitive(int z = 0);
private:
	inline RenderBuffer& DrawBuffer() {
		return buffers[activeBuffer];
	}
	inline RenderBuffer& DispBuffer() {
		return buffers[activeBuffer ^ 1];
	}
private:
	RenderBuffer buffers[2];
	std::uint8_t* nextPacket;
	int activeBuffer;
};

template<typename T>
inline T* Graphics::NewPrimitive(int z)
{
	// Place the primitive after all previously allocated primitives, then
	// insert it into the OT and bump the allocation pointer.
	auto prim = reinterpret_cast<T*>(nextPacket);

	addPrim(DrawBuffer().OtEntry(z), prim);
	nextPacket += sizeof(T);

	// Make sure we haven't yet run out of space for future primitives.
	assert(nextPacket <= DrawBuffer().BufferEnd());

	return prim;
}
