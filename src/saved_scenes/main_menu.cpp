#include "main_menu.h"
#include "hwregs_c.h"
#include "random.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
    delete texMenu;
}

void MainMenu::Setup(CdDrive &cd, Graphics &gfx)
{
    texMenu = new Texture;
    auto* data = cd.LoadFile("\\MMENU.TIM;1");
    if (data)
        gfx.UploadTexture(data, texMenu);
    delete[] data;
}

void MainMenu::Update(Controller *controller)
{
    if (controller[0].IsButtonJustPressed(PAD_UP))
    {
        if (--selection < 0)
            selection = 2;
    }
    if (controller[0].IsButtonJustPressed(PAD_DOWN))
    {
        selection = (selection + 1) % 3;
    }
    if (controller[0].IsButtonJustPressed(PAD_CROSS))
    {
        // CHANGE SCENE
        if ( selection == 0)
        {
            uint16_t timer = TIMER_VALUE(0);
	        Random::Seed(timer);
        }
    }
}

void MainMenu::Draw(Graphics &gfx)
{
    int8_t bgPosx = 72;
    int8_t bgPosy = 23;
    int8_t retPosX = 24;
    int8_t retPosY = 50;
// reticle
    SPRT_16* sprt = gfx.NewPrimitive<SPRT_8>(1);
    setSprt16(sprt);
    setXY0(sprt, bgPosx + retPosX, bgPosy + retPosY + selection*27);
    setUV0(sprt, texMenu->UVoffs[0] + uvRetOffs[0], texMenu->UVoffs[1] + uvRetOffs[1]);
    setClut(sprt, texMenu->clutCoords[0], texMenu->clutCoords[1]);
    setRGB0(sprt, 128, 128, 128);
// BG
    for (size_t x = 0; x < 10; x++)
    {
        for (size_t y = 0; y < 11; y++)
        {
            SPRT_16* sprt = gfx.NewPrimitive<SPRT_8>(1);
            setSprt16(sprt);
            setXY0(sprt, bgPosx + x*16, bgPosy + y*16);
            setUV0(sprt, texMenu->UVoffs[0] + x*16, texMenu->UVoffs[1] + y*16);
            setClut(sprt, texMenu->clutCoords[0], texMenu->clutCoords[1]);
            setRGB0(sprt, 128, 128, 128);
        }
    }
    DR_TPAGE* tpage = gfx.NewPrimitive<DR_TPAGE>(1);
    setDrawTPage(tpage, 0, 1, texMenu->tPage);
}

void MainMenu::DrawSelector(Graphics &gfx)
{
}
