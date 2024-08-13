#include "graphics.h"
#include <psxgpu.h>


Graphics::Graphics(std::size_t ot_length, std::size_t buffer_length)
	:
	buffers{
		RenderBuffer(ot_length, buffer_length),
		RenderBuffer(ot_length, buffer_length)
	}
{
	ResetGraph(0);
	FntLoad(960,0);
}

void Graphics::Setup(int w, int h, int r, int g, int b)
{
	buffers[0].Setup(0, 0, w, h, r, g, b);
	buffers[1].Setup(0, h, w, h, r, g, b);

	activeBuffer = 0;
	nextPacket = DrawBuffer().BufferStart();
	DrawBuffer().OtClear();
	// Turn on the video output.
	SetDispMask(1);
}

void Graphics::Flip()
{
	// Wait for the GPU to finish drawing, then wait for vblank in order to prevent screen tearing.
	DrawSync(0);
	VSync(0);

	DispBuffer().Display();
	DrawBuffer().Draw();

	activeBuffer ^= 1;
	nextPacket = DrawBuffer().BufferStart();
	DrawBuffer().OtClear();
}

void Graphics::UploadTexture(std::uint32_t *tim, Texture *tex)
{
	TIM_IMAGE timImg;
    GetTimInfo(tim, &timImg);
    // upload pixel data
    LoadImage(timImg.prect, timImg.paddr);
    DrawSync(0); // recommended to wait for upload to complete
	tex->mode = timImg.mode;
    if (timImg.mode & 0x8) // bit 4
    {   // if clut exist
        LoadImage(timImg.crect, timImg.caddr);
        DrawSync(0);
        // vram clut coords
        tex->clutCoords[0] = timImg.crect->x;
        tex->clutCoords[1] = timImg.crect->y;
    }
    // vram tex coords
    tex->texCoords[0] = timImg.prect->x;
    tex->texCoords[1] = timImg.prect->y;
    // vram page aligment UV offset                            v bit depth (0:4; 1:8; 2:16bit)
    tex->UVoffs[0] = (timImg.prect->x % 64) << (2 - (timImg.mode & 0x3));
    tex->UVoffs[1] = (timImg.prect->y & 0xff);

    tex->tPage = getTPage(timImg.mode & 0x3, 0, timImg.prect->x, timImg.prect->y);
}
