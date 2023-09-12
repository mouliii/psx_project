
#include <cstring>
#include "render_context.h"
#include "game_pad.h"

static constexpr int SCREEN_XRES = 320;
static constexpr int SCREEN_YRES = 240;

uint32_t frameCounter = 0;

int main(int argc, const char **argv)
{
	// Initialize the GPU and load the default font texture provided by PSn00bSDK at (960, 0) in VRAM.
	ResetGraph(0);
	FntLoad(960, 0);
	RenderContext ctx;
	ctx.Setup(SCREEN_XRES, SCREEN_YRES, 63, 0, 127);

	GamePad pad;

	uint32_t x = SCREEN_XRES >> 2, y = SCREEN_YRES >> 1;

	while (true)
	{
		frameCounter++;

		if(pad.GetPad(0)->stat == 0)
		{
			if(!(pad.GetPad(0)->btn & PadButton::PAD_UP))
				y -= 1;
			if(!(pad.GetPad(0)->btn & PadButton::PAD_DOWN))
				y += 1;
			if(!(pad.GetPad(0)->btn & PadButton::PAD_LEFT))
				x -= 1;
			if(!(pad.GetPad(0)->btn & PadButton::PAD_RIGHT))
				x += 1;
		}
		//printf("posX:%d", x);

		auto tile = ctx.NewPrimitive<TILE>(1);
		setTile(tile);
		setXY0 (tile, x, y);
		setWH  (tile, 64, 64);
		setRGB0(tile, 255, 255, 0);
		char str[50];
		sprintf(str, "%s %d", "frames:", frameCounter);
		ctx.DrawText(8, 16, 0, "Hello C++!");
		ctx.DrawText(8, 32, 0, str);
		ctx.Flip();
	}
	
	return 0;
}
