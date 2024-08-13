#pragma once
#include <cstdint>
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

class Projectile
{
public:
    Projectile() = default;
    Projectile(ProjData* proj, Texture* tex, int16_t uvx, int16_t uvy)
    {
        std::memcpy(&data, proj, sizeof(ProjData));
        texture = tex;
        this->uvx = uvx;
        this->uvy = uvy;
        alive = true;
        startpos[0] = proj->posx;
        startpos[1] = proj->posy;
    }
    //void Setup(ProjData* proj, Texture* tex, int16_t uvx, int16_t uvy);
    void Update()
    {   // pitäs olla fixed formatissa
        if (alive)
        {
            data.posy += data.diry * data.speed;
            data.posx += data.dirx * data.speed;

            int32_t deltaX = (data.posx - startpos[0] >> 12);
            int32_t deltaY = (data.posy - startpos[1] >> 12);
            if ( ((deltaX*deltaX)+(deltaY*deltaY)) > (maxDist*maxDist) )
            {
                alive = false;
            }
        }
    }
    void Draw(Graphics& gfx)
    {
        SPRT_8* sprt = gfx.NewPrimitive<SPRT_8>(1);
        setSprt8(sprt);
        setXY0(sprt, data.posx >> 12, data.posy >> 12);
        setUV0(sprt, texture->UVoffs[0] + uvx, texture->UVoffs[1] + uvy);
        setClut(sprt, texture->clutCoords[0], texture->clutCoords[1]);
        setRGB0(sprt, 128, 128, 128);
    }
public:
    ProjData data; // memmove
    Texture* texture;
    std::int32_t startpos[2] = {0};
    std::int32_t maxDist = 100;
    std::uint8_t uvx = 0; // texCoord += 
    std::uint8_t uvy = 0; // SIIS UV OFFSET
    bool alive = false;
};