#pragma once
#include <cstdint>
#include "character_body.h"
#include "graphics.h"
#include "texture.h"
#include "fixed_math.h"
#include "debug_msg.h"

struct ProjData
{
    std::int32_t posx = 0;
    std::int32_t posy = 0;
    std::int32_t dirx = 0;
    std::int32_t diry = 0;
    std::uint16_t speed = 0;
};

class Projectile: public CharacterBody
{
public:
    Projectile():CharacterBody(0,0,0,0){}
    Projectile(ProjData* proj, Texture* tex, int16_t uvx, int16_t uvy)
        :
        CharacterBody(proj->posx, proj->posy, proj->speed, 8)
    {
        texture = tex;
        this->uvx = uvx;
        this->uvy = uvy;
        alive = true;
        startpos[0] = proj->posx;
        startpos[1] = proj->posy;
        dir[0] = proj->dirx;
        dir[1] = proj->diry;
        alive = true;
        
    }
    ~Projectile(){}
    void GetHit(int32_t dmg){}
    //void Setup(ProjData* proj, Texture* tex, int16_t uvx, int16_t uvy);
    void Update()
    {   // pitäs olla fixed formatissa
        if (alive)
        {
            pos[0] += dir[0] * speed;
            pos[1] += dir[1] * speed;

            int32_t deltaX = (pos[0] - startpos[0] >> 12);
            int32_t deltaY = (pos[1] - startpos[1] >> 12);
            if ( ((deltaX*deltaX)+(deltaY*deltaY)) > (maxDist*maxDist) )
            {
                alive = false;
            }
        }
    }
    void Draw(Graphics& gfx)
    {
        if (alive)
        {
            SPRT_8* sprt = gfx.NewPrimitive<SPRT_8>(1);
            setSprt8(sprt);
            setXY0(sprt, pos[0] >> 12, pos[1] >> 12);
            setUV0(sprt, texture->UVoffs[0] + uvx, texture->UVoffs[1] + uvy);
            setClut(sprt, texture->clutCoords[0], texture->clutCoords[1]);
            setRGB0(sprt, 128, 128, 128);
        }
    }
public:
    int32_t dir[2];
    Texture* texture;
    std::int32_t startpos[2] = {0};
    std::int32_t maxDist = 100;
    std::uint8_t uvx = 0; // texCoord += 
    std::uint8_t uvy = 0; // SIIS UV OFFSET
    bool alive = false;
};