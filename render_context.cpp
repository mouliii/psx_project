#include "render_context.h"

RenderContext::RenderContext(size_t otLength, size_t bufferLength)
    :
    buffers({
        RenderBuffer(otLength, bufferLength),
        RenderBuffer(otLength, bufferLength)
    })
{
}

void RenderContext::Setup(int w, int h, int r, int g, int b)
{
    buffers[0].Setup(0, 0, w, h, r, g, b);
    buffers[1].Setup(0, h, w, h, r, g, b);
    // init first buffer and its OT
    activeBuffer = 0;
    nextPacket = GetDrawBuffer().BufferStart();
    // Turn on the video output.
	SetDispMask(1);
}

void RenderContext::Flip()
{
    // Wait for the GPU to finish drawing, then wait for vblank
    DrawSync(0);
    VSync(0);
    // Display the framebuffer the GPU has just finished drawing and start
	// rendering the display list that was filled up in the main loop.
    GetDispBuffer().Display();
    GetDrawBuffer().Draw();
    // flip buffers, clear OT
    activeBuffer ^= 1;
    nextPacket = GetDrawBuffer().BufferStart();
    GetDispBuffer().ClearOT();
}

void RenderContext::DrawText(uint32_t x, uint32_t y, uint32_t z, const char* text)
{
    // need to load font to VRAM before calling
    nextPacket = reinterpret_cast<uint8_t*>( FntSort(GetDrawBuffer().OTEntry(z), nextPacket, x, y, text) );
    assert(nextPacket <= GetDrawBuffer().BufferEnd());
}

RenderBuffer &RenderContext::GetDrawBuffer()
{
    return buffers[activeBuffer];
}

RenderBuffer &RenderContext::GetDispBuffer()
{
    return buffers[activeBuffer ^ 1];
}
