#include "enemy.h"

Enemy::Enemy()
    :
    CharacterBody(0,0,0,0)
{
}

Enemy::Enemy(int32_t posx, int32_t posy, uint8_t uvx, uint8_t uvy, Texture *tex)
    : CharacterBody(posx * ONE, posy * ONE, 1),
      uvOffs{uvx, uvy}, texture(tex)
{
    alive = true;
}

Enemy::~Enemy()
{
}

void Enemy::Setup()
{
}

void Enemy::Update()
{
    // FSM JOTAI
    Move();
}

void Enemy::Draw(Graphics &gfx)
{
    SPRT_16* sprt = gfx.NewPrimitive<SPRT_16>(1);
    setSprt16(sprt);
    setXY0(sprt, pos[0] >> 12, pos[1] >> 12);
    setUV0(sprt, texture->UVoffs[0] + uvOffs[0], texture->UVoffs[1] + uvOffs[0]);
    setClut(sprt, texture->clutCoords[0], texture->clutCoords[1]);
    setRGB0(sprt, 128, 128, 128);
}

void Enemy::SetTarget(int32_t *pos)
{
    this->targetPos = pos;
}

void Enemy::GetHit(int32_t dmg)
{
    alive = false;
}

void Enemy::Move()
{
    int32_t dx = (targetPos[0] - pos[0]) >> 12;
    int32_t dy = (targetPos[1] - pos[1]) >> 12;

    if ( ((dx*dx) + (dy*dy)) < (20*20) )
    {
        return;
    }

    int32_t length = SquareRoot0( (dx * dx) + (dy * dy) );
    if (length == 0){
        return;
    }
    dx = (dx * ONE) / length;
    dy = (dy * ONE) / length;
    
    pos[0] += dx * speed;
    pos[1] += dy * speed;
}
