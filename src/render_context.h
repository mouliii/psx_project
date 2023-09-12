#pragma once
#include <cstdint>
#include <cassert>
#include "render_buffer.h"

class RenderContext
{
public:
    RenderContext(size_t otLength = 15, size_t bufferLength = 8192);
    void Setup(int w, int h, int r, int g, int b);
	void Flip();
    template<typename T>
    T* NewPrimitive(uint32_t z = 0);
    void DrawText(uint32_t x, uint32_t y, uint32_t z, const char* text);
private:
    RenderBuffer& GetDrawBuffer(); // DrawBuffer on <psxgpu.h>:ssa
    RenderBuffer& GetDispBuffer();
private:
    RenderBuffer buffers[2];
    uint8_t* nextPacket;
    uint32_t activeBuffer;
};

template <typename T>
inline T *RenderContext::NewPrimitive(uint32_t z)
{
    auto prim = reinterpret_cast<T*>(nextPacket);
    addPrim(GetDrawBuffer().OTEntry(z), prim);
    nextPacket += sizeof(T);

    assert(nextPacket <= GetDrawBuffer().BufferEnd());
    return prim;
}
