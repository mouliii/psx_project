#pragma once
#include <cstdint>
#include <psxgpu.h>
#include <psxgte.h> // sqrt12
#include "graphics.h"
#include "controller.h"
#include "texture.h"
#include "fixed_math.h"
#include "debug_msg.h"
#include "projectile.h"


class Player
{
public:
    Player();
    ~Player();
    void Setup(int32_t posx, int32_t posy, Texture* tex, Texture* texProj);
    void Update(Controller& controller);
    void Draw(Graphics& gfx);
private:
// PLAYER
    void Move(Controller& controller);
    void Shoot(Controller& controller);
// PORJECTILES
    void ProcessBullets();
    void DrawBullets(Graphics& gfx);
// RETICLE
    void DrawReticle(Graphics& gfx);
public:
// PLAYER
    std::int32_t pos[2];
    std::int16_t speed = 2;
    std::uint8_t uvx = 0; // texCoord += 
    std::uint8_t uvy = 0;
    Texture* texture;
// PROJETILES
    Texture* texProj;
    static constexpr uint16_t MAX_BULLETS = 50;
    uint16_t shootCd = 1 * 60;
    uint16_t curshootCd = 0;
    Projectile* projArr;
    uint16_t projSpeed = 5;
// RETICLE
    int32_t retPosOffs[2] = {35,35};
    uint8_t uvRetOffs[2] = {16*6, 16};
    int32_t reticleDir[2] = {0};
    bool drawRet = false;
};


/*
SPRT* sprite = gfx.NewPrimitive<SPRT>(1);
setSprt(sprite);
setXY0(sprite, 220, 120);
setWH(sprite, 64, 64);
setUV0(sprite, tex.UVoffs[0], tex.UVoffs[1]);
setClut(sprite, tex.clutCoords[0], tex.clutCoords[1]);
setRGB0(sprite, 128, 128, 128);
// DR_TPAGE
DR_TPAGE* tpage = gfx.NewPrimitive<DR_TPAGE>(1);
setDrawTPage(tpage, 0, 1, tex.tPage);

SPRT_16* sprt = gfx.NewPrimitive<SPRT_16>(1);
//setSprt(sprt);
setSprt16(sprt);
setXY0(sprt, 160, 120);
//setWH(sprt, 16, 16);
setUV0(sprt, tex2.UVoffs[0], tex2.UVoffs[1]);
setClut(sprt, tex2.clutCoords[0], tex2.clutCoords[1]);
setRGB0(sprt, 128, 128, 128);

DR_TPAGE* tpage2 = gfx.NewPrimitive<DR_TPAGE>(1);
setDrawTPage(tpage2, 0, 1, tex2.tPage);

*/