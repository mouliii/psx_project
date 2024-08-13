#pragma once
#include <cstdint>
#include <psxgpu.h>
#include <psxgte.h>
#include "character_body.h"
#include "graphics.h"
#include "controller.h"
#include "texture.h"

enum ENEMY_FSM
{
    CHASE = 0,
    ATTACK
};

class Enemy: public CharacterBody
{
public:
    Enemy();
    Enemy(int32_t posx, int32_t posy, uint8_t uvx, uint8_t uvy, Texture* tex);
    ~Enemy();
    void Setup();
    void Update();
    void Draw(Graphics& gfx);
    void SetTarget(int32_t* pos);
    //virtual void GetHit(int32_t dmg) override;
    void GetHit(int32_t dmg);
    bool IsAlive(){return alive;}
private:
    void Move();
public:
    //int32_t pos[2];
    //std::int16_t speed = 1;
    uint8_t uvOffs[2];
    Texture* texture;
    bool alive = false;
    int32_t* targetPos;
    ENEMY_FSM fsm = ENEMY_FSM::CHASE;
};