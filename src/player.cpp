#include "player.h"

Player::Player(int32_t posx, int32_t posy, uint8_t uvx, uint8_t uvy, Texture *tex)
    :
    CharacterBody(posx*ONE,posy*ONE, 2),
    uvOffs{uvx,uvy},texture(tex)
{
    //collider->SetColLayerBits();
}

Player::~Player()
{
    // textures deleted in scene
}

void Player::Setup(Texture* texProj)
{
    this->texProj = texProj;
    //projArr = (Projectile*)malloc(sizeof(Projectile) * MAX_BULLETS);
    projectiles.Reserve(MAX_BULLETS);
    //for (size_t i = 0; i < MAX_BULLETS; i++)
    //{
    //    projArr[i].alive = false;
    //}
    
}

void Player::Update(Controller &controller)
{
    Shoot(controller);
    Move(controller);
    ProcessBullets();
}

// multiplicand    = 2048;                             // multiplicand = 0.5;
// fixed_value     = (fixed_value*multiplicand)>>12;   // fixed_value *= multiplicand;

// dividend        = 2048;                             // dividend = 0.5;
// fixed_value     = (fixed_value*4096)/dividend;      // fixed_value /= dividend;

void Player::GetHit(int32_t dmg)
{
    
}

void Player::Draw(Graphics &gfx)
{
    SPRT_16* sprt = gfx.NewPrimitive<SPRT_16>(1);
    setSprt16(sprt);
    setXY0(sprt, pos[0] >> 12, pos[1] >> 12);
    setUV0(sprt, texture->UVoffs[0] + uvOffs[0], texture->UVoffs[1] + uvOffs[0]);
    setClut(sprt, texture->clutCoords[0], texture->clutCoords[1]);
    setRGB0(sprt, 128, 128, 128);

    DrawBullets(gfx);
    DrawReticle(gfx);

    //DR_TPAGE* tpage = gfx.NewPrimitive<DR_TPAGE>(1);
    //setDrawTPage(tpage, 0, 1, texture->tPage);
}

void Player::Move(Controller &controller)
{
    int32_t dirx = controller.GetLeftAnalogX();
    int32_t diry = controller.GetLeftAnalogY();

#pragma region DPAD
    if (controller.IsButtonPressed(PAD_UP))
    {
        diry -= ONE;
    }
    if (controller.IsButtonPressed(PAD_DOWN))
    {
        diry += ONE;
    }
    if (controller.IsButtonPressed(PAD_LEFT))
    {
        dirx -= ONE;
    }
    if (controller.IsButtonPressed(PAD_RIGHT))
    {
        dirx += ONE;
    }
    // dir length DPAD
    //int32_t length = SquareRoot12( ((dirx * dirx) >> 12) + ((diry * diry) >> 12) );
    //if (length == 0){
    //    return;
    //}
    //diry = (diry * ONE) / lengthc; // 2896
    //dirx = (dirx * ONE) / lengthc;
    //int32_t vely = diry * speed; // timer dt mahdollinen
    //int32_t velx = dirx * speed; // v-sync on deltaT
#pragma endregion

    // dir length CONTROLLER
    int32_t lengthc = SquareRoot0( ((dirx * dirx)) + ((diry * diry)) );
    if (lengthc == 0){
        return;
    }

    // normalize // TESTAA normi vs inverse sqrt
    dirx = (dirx * ONE) / lengthc;
    diry = (diry * ONE) / lengthc;

    pos[0] += dirx * speed; // v-sync on deltaT
    pos[1] += diry * speed; // timer dt mahdollinen
}

void Player::Shoot(Controller &controller)
{
    int32_t dxc = controller.GetRightAnalogX();
    int32_t dyc = controller.GetRightAnalogY();

    int32_t lengthc = SquareRoot0( ((dxc * dxc)) + ((dyc * dyc)) );
    if (lengthc == 0)
    {
        drawRet = false;
        return;
    }

    dxc = (dxc * ONE) / lengthc;
    dyc = (dyc * ONE) / lengthc;
    // cache right stick vec normalized
    reticleDir[0] = dxc;
    reticleDir[1] = dyc;
    drawRet = true;

    if (curshootCd > 0){
        curshootCd--;
        return;
    }
    curshootCd = shootCd;
    int32_t dposcache = 4 * ONE;

    ProjData pj{
        .posx = pos[0] + dposcache, 
        .posy = pos[1] + dposcache,
        .dirx = dxc,
        .diry = dyc,
        .speed = projSpeed
    };
    Projectile p(&pj, texProj,0,0);
    projectiles.PushBack(p);

    //char str[50];
    //sprintf(str, "%d", p.GetRadius());
    //DEBUG_MSG::CreateMsg(0, str);

}

void Player::ProcessBullets()
{
    for (size_t i = 0; i < projectiles.Length(); i++)
    {
        projectiles[i].Update();
        if (!projectiles[i].alive)
        {
            projectiles.SwapBackAndPop(i);
        }
    }
}

void Player::DrawBullets(Graphics& gfx)
{
    for (size_t i = 0; i < projectiles.Length(); i++)
    {
       projectiles[i].Draw(gfx);
    }
}

void Player::DrawReticle(Graphics &gfx)
{
    static int asd = 0;
    if (drawRet)
    {   
        int32_t roatedX = ( (reticleDir[0] * retPosOffs[0]) >> 12 );
        int32_t roatedY = ( (reticleDir[1] * retPosOffs[1]) >> 12 );
        SPRT_16* sprt = gfx.NewPrimitive<SPRT_16>(1);
        setSprt16(sprt);
        setXY0(sprt, (pos[0] >> 12) + roatedX, (pos[1] >> 12) + roatedY);
        setUV0(sprt, texture->UVoffs[0] + uvRetOffs[0], texture->UVoffs[1] + uvRetOffs[1]);
        setClut(sprt, texture->clutCoords[0], texture->clutCoords[1]);
        setRGB0(sprt, 128, 128, 128);
    }
}
