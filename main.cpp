#include "render_context.h"

static constexpr int SCREEN_XRES = 320;
static constexpr int SCREEN_YRES = 240;

int main(int argc, const char **argv)
{
	// Initialize the GPU and load the default font texture provided by PSn00bSDK at (960, 0) in VRAM.
	ResetGraph(0);
	FntLoad(960, 0);
	RenderContext ctx;
	ctx.Setup(SCREEN_XRES, SCREEN_YRES, 63, 0, 127);

	uint32_t x = SCREEN_XRES >> 1, y = SCREEN_YRES >> 1;
	uint32_t dx = 1, dy = 1;

	while (true)
	{
		if(x < 0 || x > (SCREEN_XRES - 64)){
			dx = -dx;
		}
		if(y < 0 || y > (SCREEN_YRES - 64)){
			dy = -dy;
		}
		x += dy;
		y += dy;

		auto tile = ctx.NewPrimitive<TILE>(1);
		setTile(tile);
		setXY0 (tile, x, y);
		setWH  (tile, 64, 64);
		setRGB0(tile, 255, 255, 0);

		ctx.DrawText(8, 16, 0, "Hello C++!");
		ctx.Flip();
	}
	
	return 0;
}
