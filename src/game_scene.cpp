#include "game_scene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
    delete plr1;
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
    plr1 = new Player(160-16, 120-16, 0, 0, texChars);
    plr1->Setup(texProjs);

    enemies.Reserve(MAX_ENEMIES);
    enemies.PushBack(Enemy(120,200, 16,16,texChars));
    enemies[0].SetTarget(&plr1->GetPos());

    // same spritesheet(tpage-vram)
}

void GameScene::Update(Controller* controller)
{

    plr1->Update(controller[0]);

    //char str[50];
    //int32_t el = enemies.Length();
    //sprintf(str, "%d", el);
    //DEBUG_MSG::CreateMsg(0, str);
    for (size_t i = 0; i < enemies.Length(); i++)
    {
        if (enemies[i].IsAlive())
        {
            enemies[i].Update();
        }
    }
    UpdateScene();
}

void GameScene::Draw(Graphics& gfx)
{
    plr1->Draw(gfx);
    for (size_t i = 0; i < enemies.Length(); i++)
    {
        if (enemies[i].IsAlive())
        {
            enemies[i].Draw(gfx);
        }
    }
    DR_TPAGE* tpage = gfx.NewPrimitive<DR_TPAGE>(1);
    setDrawTPage(tpage, 0, 1, texChars->tPage);

    DEBUG_MSG::ShowMessages();
}

void GameScene::UpdateScene()
{
    //char str[50];
    //sprintf(str, "%d", nCurEnemies);
    //DEBUG_MSG::CreateMsg(0, str);

    // "PHYSICS PROCESS"
    //int32_t hitCount = 0;
    char str[50];
    
    for (size_t i = 0; i < plr1->GetProjectiles().Length(); i++) // !!!!!!!!!!!!!!!!!!!!!!!!!!!!
    {
        //sprintf(str, "pos: %d %d", plr1->GetProjectiles()[i].collider->owner->pos[0] >> 12, plr1->GetProjectiles()[i].collider->owner->pos[1] >> 12);
        for (size_t j = 0; j < enemies.Length(); j++)
        {
            if (collision.IsColliding(&plr1->GetProjectiles()[i], &enemies[j]))
            {
                enemies[j].GetHit(666);
                if (!enemies[j].alive)
                {   // TODO
                    enemies.SwapBackAndPop(j);
                }
                break;
            }
        }
    }
    //sprintf(str, "hits: %d %d", hitCount, enemies.Length());
    //DEBUG_MSG::CreateMsg(0, str);
    //char str[50];
    //sprintf(str, "l %d", plr1->GetProjectiles().Length());
    //DEBUG_MSG::CreateMsg(0, str);

    //// ENEMY SPAWNER
    if (++counter % 60 == 0)
    {
        for (int16_t i = 0; i < 10; i++)
        {
            // TODO FIXED WIDTH
            int16_t randX = Random::GetRandomNum<int16_t>(320);
            randX += Random::GetRandomNum<int16_t>(240) - 120;
            int16_t randY;
            if ( (randX > 0) && (randX < 320) )
            {
                randY = Random::GetRandomNum<int16_t>(120) + 240;
                uint16_t flipY = Random::GetRandomNum<uint16_t>(100);
                if (flipY > 50)
                    randY *= -1;
            }
            else
            {
                randY = Random::GetRandomNum<int16_t>(240);
            }
            Enemy e = Enemy(randX, randY, 16,16,texChars);
            e.SetTarget(&plr1->GetPos());
            enemies.PushBack(e);
        }
    }
}