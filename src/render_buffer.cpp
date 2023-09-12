#include "render_buffer.h"
#include <cassert>

RenderBuffer::RenderBuffer(size_t ot_length, size_t buffer_length)
    :
    otLength(ot_length), bufferLength(buffer_length)
{
    // Initializing the OT in a constructor is unsafe, since ClearOTagR()
	// requires DMA to be enabled and may fail if called before ResetGraph() or ResetCallback()
    ot = new uint32_t[otLength];
    buffer = new uint8_t[bufferLength];
    assert(ot && buffer);
}

RenderBuffer::~RenderBuffer()
{
    delete[]ot;
    delete[]buffer;
}

void RenderBuffer::Setup(int x, int y, int w, int h, int r, int g, int b)
{
    // vram coords
    SetDefDrawEnv(&drawEnv, x, y, w, h);
    SetDefDispEnv(&dispEnv, x, y, w, h);
    // clear color
    setRGB0(&drawEnv, r, g, b);
    // enable auto clear
    drawEnv.isbg = 1;
}

uint8_t *RenderBuffer::BufferStart()
{
    return buffer;
}

uint8_t *RenderBuffer::BufferEnd()
{
    return &buffer[bufferLength];
}

uint32_t* RenderBuffer::OTEntry(int z)
{
    return &ot[z];
}

void RenderBuffer::ClearOT()
{
    ClearOTagR(ot, otLength);
}

void RenderBuffer::Draw()
{
    DrawOTagEnv(&ot[otLength-1], &drawEnv);
}

void RenderBuffer::Display()
{
    PutDispEnv(&dispEnv);
}
