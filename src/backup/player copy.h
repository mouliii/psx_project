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
    Player(int32_t posx, int32_t posy, uint8_t uvx, uint8_t uvy, Texture* tex);
    ~Player();
    void Setup(Texture* texProj);
    void Update(Controller& controller);
    void Draw(Graphics& gfx);
    int32_t& GetPos(){return *pos;}
private:
// PLAYER
    void Move(Controller& controller);
    void Shoot(Controller& controller);
// PORJECTILES
    void ProcessBullets();
    void DrawBullets(Graphics& gfx);
// RETICLE
    void DrawReticle(Graphics& gfx);
private:
// PLAYER
    int32_t pos[2];
    uint8_t uvOffs[2];
    Texture* texture;
    std::int16_t speed = 2;
    // weapon* (<-projectile )
    // stats*
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