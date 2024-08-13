#pragma once
#include <cstdint>
#include <psxgte.h>
#include "collider.h"
#include "health_component.h"
#include "stats_component.h"

class Collider;

class CharacterBody
{
public:
    CharacterBody(int32_t posx, int32_t posy,int16_t speed, int16_t width = 16)
        :
        pos{posx,posy}, speed(speed), width(width)
    {
    }
    virtual ~CharacterBody(){}
    const int16_t GetRadius(){return width >> 1;}
    //virtual void GetHit(int32_t dmg) = 0; // todo: component // CRASHES
public:
    int32_t pos[2];
    int16_t speed = 1;
    int16_t width; // "physics"
    // weapon*
    
};