#include "game_scene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
    delete texChars;
    delete texProjs;
}

void GameScene::Setup(CdDrive &cd, Graphics &gfx)
{
    texChars = new Texture;
    texProjs = new Texture;
    // LOAD STUFF
    auto* sprtsData = cd.LoadFile("\\SPRTS.TIM;1");
    if (sprtsData)
        gfx.UploadTexture(sprtsData, texChars);
    delete[] sprtsData;
    auto* projData = cd.LoadFile("\\PROJS.TIM;1");
    if (projData)
        gfx.UploadTexture(projData, texProjs);
    delete[] projData;
    // INIT STUFF
    plr1 = new Player();
    plr1->Setup(160-16, 120-16, texChars, texProjs);
    //enemies = new Player[1024];
    //for (size_t i = 0; i < 1024; i++)
    //{
    //    enemies[i].Setup(Random::GetRandomNum<int32_t>(320), Random::GetRandomNum<int32_t>(240), texChars);
    //    enemies[i].uvx = Random::GetRandomNum<uint8_t>(5) * 16;
    //    enemies[i].uvy = Random::GetRandomNum<uint8_t>(4) * 16;
    //}
    // same spritesheet(tpage-vram)
}

void GameScene::Update(Controller* controller)
{
    plr1->Update(controller[0]);
}

void GameScene::Draw(Graphics& gfx)
{
    plr1->Draw(gfx);
    //for (size_t i = 0; i < 1024; i++)
    //{
    //    enemies[i].Draw(gfx);
    //}
    DR_TPAGE* tpage = gfx.NewPrimitive<DR_TPAGE>(1);
    setDrawTPage(tpage, 0, 1, texChars->tPage);

    DEBUG_MSG::ShowMessages();
}

void GameScene::UpdateScene()
{
    
}
