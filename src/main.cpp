#include <stdlib.h>
#include <cstring>
#include <psxgpu.h>
#include <psxgte.h>
#include <inline_c.h>
#include <hwregs_c.h>
#include "fixed_math.h"
#include "graphics.h"
#include "controller.h"
#include "cd_drive.h"
#include "texture.h"
#include "sound.h"
#include "random.h"
#include "debug_msg.h"
#include "scene_manager.h"

#include "quad.h"

// links
// https://psx.arthus.net/sdk/Psy-Q/DOCS/FileFormat47.pdf
// https://psx.arthus.net/sdk/Psy-Q/DOCS/LibOver47.pdf
// https://psx.arthus.net/sdk/Psy-Q/DOCS/LibRef47.pdf
// https://github.com/ABelliqueux/nolibgs_hello_worlds
// TODO
// debuf_msg Variadic functions https://en.cppreference.com/w/cpp/utility/variadic

static constexpr int SCREEN_XRES = 320;
static constexpr int SCREEN_YRES = 240;
// custom ot? [0] ui, [1] sprites, [2] projs?
static constexpr size_t DEFAULT_OT_LENGTH = 3;
static constexpr size_t DEFAULT_BUFFER_LENGTH = 32768;


int main(int argc, const char** argv)
{
	// init systems
	Graphics gfx(DEFAULT_OT_LENGTH, DEFAULT_BUFFER_LENGTH);
	gfx.Setup(SCREEN_XRES, SCREEN_YRES, 58, 123, 176);
	SoundPlayer soundPlayer; // init before cd-drive
	CdDrive cd;
	Controller controllers[2];
    InitPAD(controllers[0].padBuffer, 34, controllers[1].padBuffer, 34);
    StartPAD(); // start polling (TODO[SPI])
    ChangeClearPAD(0);
	InitGeom(); // todo: research these vv
	gte_SetGeomOffset( SCREEN_XRES >> 1, SCREEN_YRES >> 1 );
	gte_SetGeomScreen( SCREEN_XRES >> 1 );
	uint16_t timer = TIMER_VALUE(0);
	Random::Seed(timer);
	DEBUG_MSG::Setup(&gfx, 5);

	Scene* scene;
	scene = new MainMenu();
	scene->Setup(cd, gfx);
	// scene changer atm
	SceneManager::Setup(scene, &gfx, &cd);

	auto* data = cd.LoadFile("\\AWESOME.TIM;1");
	Texture* tex = new Texture;
	gfx.UploadTexture(data, tex);
	delete[] data;

	char str[50];
	sprintf(str, "%d %d", tex->UVoffs[0], tex->UVoffs[1]);
	DEBUG_MSG::CreateMsg(0, str);

	QuadF qf(40,152-50,25,25,Color(255,0,0));
	QuadFT qft(40,152,32,32,tex);
	QuadG qg(40,50,32,32);
	QuadGT qgt(100,152,32,32, tex);
	qgt.SetUV(0, 0,0);
	qgt.SetUV(1, 64,0);
	qgt.SetUV(2, 0,64);
	qgt.SetUV(3, 64,64);
	qft.SetUV(0, 0,0);
	qft.SetUV(1, 64,0);
	qft.SetUV(2, 0,64);
	qft.SetUV(3, 64,64);
	qft.SetBrightness(80);
	qg.SetColor(3, Color(255,255,255));
	qgt.SetColor(3, Color(0,0,255));

	while(true)
	{
		scene->Update(controllers);
		scene->Draw(gfx);

		qf.color.g = ++qf.color.g % 255;
		qf.color.b = ++qf.color.b % 128;
		qf.Rotate(5);
		qft.Scale(1.001f);
		qft.Rotate(-2);

		qf.Draw(gfx,0);
		qft.Draw(gfx,0);
		qg.Draw(gfx,0);
		qgt.Draw(gfx, 0);

		sprintf(str, "%d", qgt.uv.Length());
		DEBUG_MSG::CreateMsg(0, str);
		DEBUG_MSG::ShowMessages();
		// end frame
		for (std::uint8_t i = 0; i < 2; i++)
		{
			controllers[i].UpdateBuffer();
		}
		gfx.Flip();
	}

	return 0;
}