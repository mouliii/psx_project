#include "render_buffer.h"

RenderBuffer::RenderBuffer(std::size_t otLength, std::size_t bufferLength)
	:
	otLength(otLength), bufferLength(bufferLength)
	// https://github.com/Lameguy64/PSn00bSDK/blob/00abe5963fbead092f91935b90390aa5a9111c43/examples/beginner/hellocpp/main.cpp#L63
	// Initializing the OT in a constructor is unsafe, since ClearOTagR()
	// requires DMA to be enabled and may fail if called before ResetGraph() or
	// ResetCallback() (which can easily happen as constructors can run before
	// main()). Thus, this constructor is only going to allocate the buffers and
	// clearing is deferred to RenderContext::setup().
{
	ot = new uint32_t[otLength];
	buffer = new uint8_t[bufferLength];
}

RenderBuffer::~RenderBuffer()
{
	delete[] ot;
	delete[] buffer;
}

void RenderBuffer::Setup(int x, int y, int w, int h, int r, int g, int b)
{
	// Set the framebuffer's VRAM coordinates.
	SetDefDrawEnv(&drawEnv, x, y, w, h);
	SetDefDispEnv(&dispEnv, x, y, w, h);
	// Set the default background color and enable auto-clearing.
	setRGB0(&drawEnv, r, g, b);
	drawEnv.isbg = 1;
}
